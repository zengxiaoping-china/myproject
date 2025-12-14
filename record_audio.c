/*
 * Windows 简单录音程序（使用 Win32 Wave API）
 * 功能：录制指定秒数的音频，并保存为标准 WAV 文件
 * 编译命令：gcc record_audio.c -o record_audio.exe -lwinmm
 */

// 包含 Windows 核心 API 头文件（如 HANDLE、DWORD 等类型定义）
#include <windows.h>

// 包含多媒体系统头文件（waveInXXX 函数声明在此）
#include <mmsystem.h>

// 包含标准输入输出库（printf、FILE 操作等）
#include <stdio.h>

// 定义录音参数（宏常量，编译时替换）
#define SAMPLE_RATE     44100    // 采样率：每秒采样 44100 次（CD 音质）
#define CHANNELS        2        // 声道数：1 = 单声道，2 = 立体声
#define BITS_PER_SAMPLE 16       // 位深度：每个采样点用 16 位（2 字节）存储
#define RECORD_SECONDS  30        // 录音时长：5 秒

// 主函数：程序入口
int main() {
    // 声明录音设备句柄（用于操作麦克风）
    HWAVEIN hWaveIn;

    // 声明音频数据块头（描述缓冲区信息）
    WAVEHDR wh;

    // 声明并初始化音频格式结构体（全零）
    WAVEFORMATEX wfx = {0};

    // 声明指向录音数据的缓冲区指针
    BYTE* buffer = NULL;

    // 声明文件指针，用于写入 WAV 文件
    FILE* fp = NULL;

    // 打印提示信息
    printf("正在初始化录音...\n");

    // ========== 第一步：配置音频格式 ==========
    
    // 设置音频格式为 PCM（无压缩原始音频）
    wfx.wFormatTag = WAVE_FORMAT_PCM;

    // 设置声道数（1=单声道）
    wfx.nChannels = CHANNELS;

    // 设置采样率（如 44100 Hz）
    wfx.nSamplesPerSec = SAMPLE_RATE;

    // 设置每个采样的位数（16 位）
    wfx.wBitsPerSample = BITS_PER_SAMPLE;

    // 计算每帧（一个采样点所有声道）的字节数
    // 公式：声道数 × 位深 / 8（转为字节）
    wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;

    // 计算每秒音频数据的字节数（用于分配缓冲区）
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    // ========== 第二步：打开默认录音设备 ==========
    
    // 打开系统默认录音设备（WAVE_MAPPER 表示自动选择）
    // 参数说明：
    //   &hWaveIn         → 接收设备句柄的指针
    //   WAVE_MAPPER      → 使用默认录音设备
    //   &wfx             → 指向音频格式结构体
    //   0, 0, CALLBACK_NULL → 不使用回调函数（同步模式）
    MMRESULT result = waveInOpen(&hWaveIn, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    
    // 检查是否打开成功（MMSYSERR_NOERROR = 0 表示成功）
    if (result != MMSYSERR_NOERROR) {
        printf("错误：无法打开录音设备！\n");
        return 1; // 返回非0表示程序异常退出
    }

    // ========== 第三步：分配录音缓冲区 ==========
    
    // 计算总需要的缓冲区大小（字节）= 每秒字节数 × 录音秒数
    DWORD bufferSize = wfx.nAvgBytesPerSec * RECORD_SECONDS;

    // 动态分配内存（堆上）
    buffer = (BYTE*)malloc(bufferSize);
    
    // 检查内存是否分配成功
    if (!buffer) {
        printf("错误：内存分配失败！\n");
        waveInClose(hWaveIn); // 关闭设备（释放资源）
        return 1;
    }

    // ========== 第四步：准备并提交缓冲区给录音系统 ==========
    
    // 将 WAVEHDR 结构体清零（安全初始化）
    ZeroMemory(&wh, sizeof(WAVEHDR));

    // 指向我们分配的缓冲区
    wh.lpData = (LPSTR)buffer;

    // 设置缓冲区总长度（字节）
    wh.dwBufferLength = bufferSize;

    // 通知系统：这个缓冲区已准备好用于录音
    waveInPrepareHeader(hWaveIn, &wh, sizeof(WAVEHDR));

    // 将缓冲区加入录音队列（系统会往里写数据）
    waveInAddBuffer(hWaveIn, &wh, sizeof(WAVEHDR));

    // ========== 第五步：开始录音 ==========
    
    printf("开始录音 %d 秒... 请说话\n", RECORD_SECONDS);

    // 启动录音（系统开始填充缓冲区）
    waveInStart(hWaveIn);

    // ========== 第六步：等待录音完成 ==========
    
    // 简单阻塞等待（Sleep 单位是毫秒）
    Sleep(RECORD_SECONDS * 1000);

    // ========== 第七步：停止并清理录音资源 ==========
    
    // 停止录音（不再接收新数据）
    waveInStop(hWaveIn);

    // 重置设备状态（确保所有缓冲区可回收）
    waveInReset(hWaveIn);

    // 通知系统：我们不再使用这个缓冲区
    waveInUnprepareHeader(hWaveIn, &wh, sizeof(WAVEHDR));

    // 关闭录音设备（释放系统资源）
    waveInClose(hWaveIn);

    // ========== 第八步：将录音数据写入 WAV 文件 ==========
    
    printf("录音完成，正在保存为 recording.wav...\n");

    // 以二进制写入模式打开文件
    fp = fopen("recording.wav", "wb");
    
    // 检查文件是否成功创建
    if (!fp) {
        printf("错误：无法创建 WAV 文件！\n");
        free(buffer); // 释放内存
        return 1;
    }

    // ---------- 写入 WAV 文件头（RIFF 标准格式）----------
    
    // RIFF 文件标识（4字节）
    fwrite("RIFF", 1, 4, fp);

    // 整个文件大小减去前8字节（chunkSize）
    DWORD chunkSize = 36 + wh.dwBytesRecorded;
    fwrite(&chunkSize, 1, 4, fp);

    // 文件格式标识（"WAVE" + "fmt "）
    fwrite("WAVEfmt ", 1, 8, fp);

    // fmt 子块大小（固定为16，表示PCM）
    DWORD subchunk1Size = 16;
    fwrite(&subchunk1Size, 1, 4, fp);

    // 音频格式（1 = PCM）
    WORD audioFormat = 1;
    fwrite(&audioFormat, 1, 2, fp);

    // 声道数（从 wfx 中取，避免宏取地址问题）
    fwrite(&wfx.nChannels, 1, 2, fp);

    // 采样率
    fwrite(&wfx.nSamplesPerSec, 1, 4, fp);

    // 每秒字节数
    fwrite(&wfx.nAvgBytesPerSec, 1, 4, fp);

    // 每帧字节数
    fwrite(&wfx.nBlockAlign, 1, 2, fp);

    // 位深度
    fwrite(&wfx.wBitsPerSample, 1, 2, fp);

    // data 块标识
    fwrite("data", 1, 4, fp);

    // 实际录音数据的字节数（可能小于 bufferSize）
    fwrite(&wh.dwBytesRecorded, 1, 4, fp);

    // 写入真正的音频数据
    fwrite(buffer, 1, wh.dwBytesRecorded, fp);

    // ========== 第九步：清理资源并退出 ==========
    
    // 关闭文件
    fclose(fp);

    // 释放动态分配的内存
    free(buffer);

    // 打印成功信息
    printf("✅ 录音已保存为 'recording.wav'\n");
    printf("请用媒体播放器打开测试！\n");

    // 返回 0 表示程序正常结束
    return 0;
}