// 启用 Unicode 支持（Windows API 使用宽字符）
#define UNICODE
#define _UNICODE

// 禁用 Visual Studio 对某些 C 运行时函数（如 fopen）的安全警告
#define _CRT_SECURE_NO_WARNINGS

// 引入必要的 Windows 和标准库头文件
#include <windows.h>        // Windows 核心 API（如控制台、线程、消息）
#include <mmsystem.h>       // 多媒体系统 API（waveIn 录音功能）
#include <stdio.h>          // 标准输入输出（printf, fopen 等）
#include <stdlib.h>         // 通用工具（malloc, exit 等）
#include <string.h>         // 字符串操作（strcpy, memset 等）
#include <time.h>           // 时间函数（time, localtime）
#include <conio.h>          // 控制台输入（_kbhit, _getch）

// 默认录音设备：WAVE_MAPPER 表示让系统自动选择默认录音设备
#define DEFAULT_DEVICE      WAVE_MAPPER

// 默认录音时长（秒），5 秒
#define DEFAULT_DURATION    5

// 音频采样率：44100 Hz（CD 质量）
#define SAMPLE_RATE         44100

// 声道数：1 = 单声道（mono），2 = 立体声（stereo）
#define CHANNELS            1

// 每个采样点的位数：16 位（即 short 类型，范围 -32768 ~ +32767）
#define BITS_PER_SAMPLE     16

// 每个音频缓冲区的时长（毫秒），影响实时性和延迟
#define BUFFER_SIZE_MS      200

// 全局状态变量（用于跨线程/回调通信，volatile 防止编译器优化）
volatile BOOL g_recording = FALSE;          // 是否正在录音
volatile BOOL g_stop_requested = FALSE;     // 用户是否请求停止
HWAVEIN g_hWaveIn = NULL;                   // 录音设备句柄
FILE* g_fp = NULL;                          // 输出 WAV 文件指针
WAVEFORMATEX g_wfx = {0};                   // 音频格式描述结构体（初始化为 0）
char g_output_file[MAX_PATH] = {0};         // 输出文件路径（UTF-8 编码）

// 函数声明（前置声明，供 main 和其他函数调用）
void showHelp();                            // 显示帮助信息
void listDevices();                         // 列出所有可用录音设备
BOOL writeWavHeader(FILE* fp, const WAVEFORMATEX* pwfx, DWORD dataSize); // 写入 WAV 文件头
void showVolumeBar(float volume);           // 在控制台显示实时音量条
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2); // 音频回调函数

// 控制台信号处理函数（处理 Ctrl+C / Ctrl+Break）
BOOL WINAPI consoleHandler(DWORD signal) {
    // 如果收到 Ctrl+C 或 Ctrl+Break 信号
    if (signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT) {
        // 且当前正在录音、尚未请求停止
        if (g_recording && !g_stop_requested) {
            printf("\n\n🛑 收到停止信号，正在保存录音...\n");
            g_stop_requested = TRUE;        // 设置停止标志
            return TRUE;                    // 告诉系统我们已处理该信号
        }
    }
    return FALSE; // 未处理，交由系统默认处理
}

// 主函数入口（使用标准 main，避免 WinMain 链接问题）
int main(void) {
    // 设置控制台输出编码为 UTF-8，支持中文等 Unicode 字符正确显示
    SetConsoleOutputCP(CP_UTF8);

    // 获取命令行参数（Unicode 版本）
    int argc;
    LPWSTR* wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!wargv) {
        printf("❌ 无法获取命令行参数\n");
        return 1; // 内存分配失败，退出
    }

    // 🌟 如果用户没有输入任何参数（仅运行程序名），则显示引导信息
    if (argc == 1) {
        printf("🎙️  Windows 录音工具 v3.0\n");
        printf("============================\n\n");

        showHelp(); // 显示帮助

        printf("\n🔍 可用录音设备：\n");
        listDevices(); // 列出设备

        // 提供常用示例，降低使用门槛
        printf("\n💡 快速开始示例：\n");
        printf("  record_audio_3.exe -t 0             # 无限录音（按 Q 停止）\n");
        printf("  record_audio_3.exe -t 15            # 录制 15 秒\n");
        printf("  record_audio_3.exe -d 1 -t 0        # 使用设备 1（如立体声混音）\n");
        printf("  record_audio_3.exe -t 30 -o test.wav # 录 30 秒到 test.wav\n");

        LocalFree(wargv); // 释放 CommandLineToArgvW 分配的内存
        return 0;         // 正常退出（仅显示帮助）
    }

    // 初始化配置变量
    UINT deviceId = DEFAULT_DEVICE;     // 设备 ID，默认为系统默认
    int duration = DEFAULT_DURATION;    // 录音时长，默认 5 秒
    char outputFile[MAX_PATH] = {0};    // 输出文件名，初始为空

    // 参数解析成功标志
    BOOL ok = TRUE;

    // 从第 1 个参数开始解析（跳过程序名）
    for (int i = 1; i < argc; i++) {
        // -h 或 --help：显示帮助
        if (wcscmp(wargv[i], L"-h") == 0 || wcscmp(wargv[i], L"--help") == 0) {
            showHelp();
            ok = FALSE;
            break;
        }
        // -l：列出设备
        if (wcscmp(wargv[i], L"-l") == 0) {
            listDevices();
            ok = FALSE;
            break;
        }
        // -d ID：指定设备 ID
        if (wcscmp(wargv[i], L"-d") == 0 && i + 1 < argc) {
            deviceId = (UINT)_wtoi(wargv[++i]); // 转换下一个参数为整数
        }
        // -t SEC：指定录音时长（0 表示无限）
        else if (wcscmp(wargv[i], L"-t") == 0 && i + 1 < argc) {
            duration = _wtoi(wargv[++i]);
            if (duration < 0) duration = 0; // 负数视为无限
        }
        // -o FILE：指定输出文件名
        else if (wcscmp(wargv[i], L"-o") == 0 && i + 1 < argc) {
            // 将宽字符文件名转换为 UTF-8 多字节字符串
            WideCharToMultiByte(CP_UTF8, 0, wargv[++i], -1, outputFile, MAX_PATH, NULL, NULL);
        }
        // 未知选项
        else if (wargv[i][0] == L'-') {
            printf("未知选项: %ls\n", wargv[i]);
            ok = FALSE;
            break;
        }
    }

    // 释放命令行参数内存
    LocalFree(wargv);
    if (!ok) return 1; // 参数错误，退出

    // 如果未指定输出文件名，则自动生成带时间戳的文件名
    if (outputFile[0] == '\0') {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        snprintf(outputFile, sizeof(outputFile),
                 "recording_%04d%02d%02d_%02d%02d%02d.wav",
                 t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                 t->tm_hour, t->tm_min, t->tm_sec);
    }

    // 重置全局状态
    g_recording = FALSE;
    g_stop_requested = FALSE;

    // 配置音频格式（PCM 格式）
    g_wfx.wFormatTag = WAVE_FORMAT_PCM;                     // PCM 编码
    g_wfx.nChannels = CHANNELS;                             // 声道数
    g_wfx.nSamplesPerSec = SAMPLE_RATE;                     // 采样率
    g_wfx.wBitsPerSample = BITS_PER_SAMPLE;                 // 位深度
    g_wfx.nBlockAlign = g_wfx.nChannels * g_wfx.wBitsPerSample / 8; // 每帧字节数
    g_wfx.nAvgBytesPerSec = g_wfx.nSamplesPerSec * g_wfx.nBlockAlign; // 每秒字节数

    // 打开录音设备（使用回调模式）
    if (waveInOpen(&g_hWaveIn, deviceId, &g_wfx, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
        printf("❌ 无法打开录音设备 %u\n", deviceId);
        return 1;
    }

    // 保存输出文件路径，并打开文件用于写入（二进制模式）
    strcpy(g_output_file, outputFile);
    g_fp = fopen(outputFile, "wb");
    if (!g_fp) {
        printf("❌ 无法创建文件: %s\n", outputFile);
        waveInClose(g_hWaveIn); // 关闭设备
        return 1;
    }

    // 写入 WAV 文件头（dataSize 暂设为最大值，后续可修正）
    if (!writeWavHeader(g_fp, &g_wfx, 0xFFFFFFFF)) {
        fclose(g_fp);
        waveInClose(g_hWaveIn);
        return 1;
    }

    // 准备多个音频缓冲区（环形缓冲，提高稳定性）
    const int NUM_BUFFERS = 4; // 缓冲区数量
    // 计算每个缓冲区的字节数（基于 BUFFER_SIZE_MS）
    DWORD bufferSize = (g_wfx.nAvgBytesPerSec * BUFFER_SIZE_MS) / 1000;
    // 分配 WAVEHDR 数组（描述缓冲区的元数据）
    WAVEHDR* headers = (WAVEHDR*)calloc(NUM_BUFFERS, sizeof(WAVEHDR));
    // 分配实际音频数据缓冲区指针数组
    BYTE** buffers = (BYTE**)calloc(NUM_BUFFERS, sizeof(BYTE*));

    // 初始化每个缓冲区
    for (int i = 0; i < NUM_BUFFERS; i++) {
        buffers[i] = (BYTE*)malloc(bufferSize); // 分配内存
        headers[i].lpData = (LPSTR)buffers[i];  // 指向数据
        headers[i].dwBufferLength = bufferSize; // 设置长度
        // 通知系统准备使用该缓冲区
        waveInPrepareHeader(g_hWaveIn, &headers[i], sizeof(WAVEHDR));
        // 将缓冲区提交给录音系统
        waveInAddBuffer(g_hWaveIn, &headers[i], sizeof(WAVEHDR));
    }

    // 开始录音
    waveInStart(g_hWaveIn);
    g_recording = TRUE;

    // 注册控制台信号处理器（Ctrl+C）
    SetConsoleCtrlHandler(consoleHandler, TRUE);

    // 根据录音模式进入主循环
    if (duration == 0) {
        // 无限录音模式
        printf("🎤 正在录音... 按 'Q' 或 'Ctrl+C' 停止\n");
        while (g_recording && !g_stop_requested) {
            // 检查是否有按键
            if (_kbhit()) {
                int ch = _getch(); // 读取按键（不回显）
                if (ch == 'q' || ch == 'Q') {
                    printf("\n⌨️  检测到 'Q' 键，停止录音...\n");
                    g_stop_requested = TRUE;
                    break;
                }
            }
            Sleep(50); // 避免 CPU 占用过高
        }
    } else {
        // 定时录音模式
        for (int sec = duration; sec > 0 && g_recording; sec--) {
            printf("\r⏳ 剩余: %2d 秒", sec); // 覆盖上一行
            fflush(stdout); // 强制刷新输出
            Sleep(1000);    // 等待 1 秒
        }
        if (g_recording) {
            printf("\n⏰ 时间到，停止录音...\n");
            g_stop_requested = TRUE;
        }
    }

    // 等待录音完全结束（确保所有回调完成）
    while (g_recording) {
        Sleep(100);
    }

    // 录音完成提示
    printf("✅ 录音已保存到: %s\n", outputFile);
    return 0;
}

// 音频回调函数（由系统在线程中调用，不可阻塞）
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    // 仅处理音频数据到达事件
    if (uMsg == WIM_DATA && g_fp) {
        WAVEHDR* pwh = (WAVEHDR*)dwParam1; // 获取缓冲区描述

        if (!g_stop_requested) {
            // 将原始 PCM 数据解释为 16 位有符号整数数组
            short* samples = (short*)pwh->lpData;
            DWORD numSamples = pwh->dwBytesRecorded / sizeof(short);

            // === 软件增益放大（提升音量）===
            const float GAIN = 2.0f; // 放大 2 倍
            for (DWORD i = 0; i < numSamples; i++) {
                int amplified = (int)(samples[i] * GAIN);
                // 防止溢出（16-bit 有符号整数范围）
                if (amplified > 32767) amplified = 32767;
                else if (amplified < -32768) amplified = -32768;
                samples[i] = (short)amplified;
            }

            // 计算当前缓冲区的最大振幅（用于音量条）
            short maxAmp = 0;
            for (DWORD i = 0; i < numSamples; i++) {
                short amp = abs(samples[i]); // 取绝对值
                if (amp > maxAmp) maxAmp = amp;
            }
            float volume = (float)maxAmp / 32768.0f; // 归一化到 [0, 1]
            showVolumeBar(volume); // 显示音量条
        }

        // 将处理后的音频数据写入文件
        fwrite(pwh->lpData, 1, pwh->dwBytesRecorded, g_fp);

        // 如果未请求停止，则重新提交该缓冲区以继续录音
        if (!g_stop_requested) {
            waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));
        } else {
            // 否则标记录音结束
            g_recording = FALSE;
        }
    }
}

// 显示实时音量条（带刷新频率限制，避免闪烁）
void showVolumeBar(float volume) {
    static DWORD lastUpdate = 0; // 上次更新时间（静态变量）
    DWORD now = GetTickCount();   // 当前系统滴答数（毫秒）
    if (now - lastUpdate < 200) return; // 每 200ms 最多更新一次
    lastUpdate = now;

    int bars = (int)(volume * 40); // 40 个字符宽度
    printf("\r["); // 回车覆盖上一行
    for (int i = 0; i < 40; i++) {
        putchar(i < bars ? '#' : ' '); // 用 # 表示音量
    }
    printf("] %.0f%%   ", volume * 100); // 显示百分比
    fflush(stdout); // 立即输出
}

// 列出所有可用录音设备
void listDevices() {
    UINT num = waveInGetNumDevs(); // 获取设备数量
    if (num == 0) {
        printf("  [无可用录音设备]\n");
        return;
    }
    for (UINT i = 0; i < num; i++) {
        WAVEINCAPSW caps; // 设备能力结构体（宽字符版）
        if (waveInGetDevCapsW(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
            char name[256];
            // 将设备名（宽字符）转换为 UTF-8
            WideCharToMultiByte(CP_UTF8, 0, caps.szPname, -1, name, sizeof(name), NULL, NULL);
            printf("  [%u] %s\n", i, name);
        }
    }
}

// 写入标准 WAV 文件头（RIFF 格式）
BOOL writeWavHeader(FILE* fp, const WAVEFORMATEX* pwfx, DWORD dataSize) {
    DWORD chunkSize = 36 + dataSize; // RIFF 块总大小（不含 "RIFF" 和 size 本身）
    WORD audioFormat = 1;            // 1 = PCM

    // 写入 RIFF 头
    fwrite("RIFF", 1, 4, fp);
    fwrite(&chunkSize, 1, 4, fp);
    // 写入 WAVE fmt 子块
    fwrite("WAVEfmt ", 1, 8, fp);    // 注意：fmt 后有一个空格（共8字节）
    fwrite(&((DWORD){16}), 1, 4, fp); // fmt 子块大小（16 字节）
    fwrite(&audioFormat, 1, 2, fp);
    fwrite(&pwfx->nChannels, 1, 2, fp);
    fwrite(&pwfx->nSamplesPerSec, 1, 4, fp);
    fwrite(&pwfx->nAvgBytesPerSec, 1, 4, fp);
    fwrite(&pwfx->nBlockAlign, 1, 2, fp);
    fwrite(&pwfx->wBitsPerSample, 1, 2, fp);
    // 写入 data 子块头
    fwrite("data", 1, 4, fp);
    fwrite(&dataSize, 1, 4, fp);
    return TRUE;
}

// 显示帮助信息
void showHelp() {
    printf(
        "用法: record_audio_3.exe [选项]\n"
        "选项:\n"
        "  -d ID    指定录音设备ID（通过 -l 查看）\n"
        "  -t SEC   录音时长（秒），0=无限（默认: 5）\n"
        "  -o FILE  输出文件名（默认: recording_时间戳.wav）\n"
        "  -l       列出所有录音设备\n"
        "  -h       显示此帮助\n"
    );
}