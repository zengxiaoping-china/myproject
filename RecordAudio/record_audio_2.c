#define UNICODE
#define _UNICODE

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define DEFAULT_SAMPLE_RATE     44100
#define DEFAULT_CHANNELS        1
#define DEFAULT_BITS_PER_SAMPLE 16
#define MAX_DEVICE_NAME         256

void listAudioDevices();
UINT selectRecordingDevice(); // ← 新增：返回用户选择的设备ID
BOOL recordAudio(int seconds, const char* filename, UINT deviceId); // ← 新增 deviceId 参数

int main() {
    printf("=== Windows 录音程序（v2.0） ===\n\n");

    // 1. 列出并选择设备
    listAudioDevices();
    UINT deviceId = selectRecordingDevice();

    // 2. 获取录音时长
    int seconds;
    printf("\n请输入录音时长（秒，1-60）: ");
    if (scanf("%d", &seconds) != 1 || seconds < 1 || seconds > 60) {
        printf("输入无效，使用默认 5 秒。\n");
        seconds = 5;
    }
    while (getchar() != '\n');

    // 3. 生成文件名
    char filename[256];
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    snprintf(filename, sizeof(filename), 
             "recording_%04d%02d%02d_%02d%02d%02d.wav",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);

    // 4. 确认并录音
    printf("\n即将使用设备 [%u] 录制 %d 秒到:\n  %s\n", deviceId, seconds, filename);
    printf("按回车键开始...\n");
    getchar();

    if (recordAudio(seconds, filename, deviceId)) {
        printf("\n✅ 录音成功！\n");
    } else {
        printf("\n❌ 录音失败！\n");
    }

    printf("\n按回车退出...");
    getchar();
    return 0;
}

// 列出设备（不变）
void listAudioDevices() {
    UINT numDevices = waveInGetNumDevs();
    printf("检测到 %u 个录音设备:\n", numDevices);
    if (numDevices == 0) {
        printf("  [无可用设备]\n");
        return;
    }
    for (UINT i = 0; i < numDevices; i++) {
        WAVEINCAPSW caps;
        if (waveInGetDevCapsW(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
            char deviceName[MAX_DEVICE_NAME];
            WideCharToMultiByte(CP_UTF8, 0, caps.szPname, -1, deviceName, MAX_DEVICE_NAME, NULL, NULL);
            printf("  [%u] %s\n", i, deviceName);
        }
    }
}

// ✨ 新增：让用户选择设备
UINT selectRecordingDevice() {
    UINT numDevices = waveInGetNumDevs();
    if (numDevices == 0) {
        printf("无可用录音设备，将尝试使用默认设备。\n");
        return WAVE_MAPPER; // WAVE_MAPPER = (UINT)-1
    }

    UINT choice;
    printf("\n请选择录音设备编号（0-%u）: ", numDevices - 1);
    if (scanf("%u", &choice) != 1 || choice >= numDevices) {
        printf("输入无效，使用默认设备。\n");
        return WAVE_MAPPER;
    }
    return choice;
}

// ✨ 修改：接受 deviceId 参数
BOOL recordAudio(int seconds, const char* filename, UINT deviceId) {
    HWAVEIN hWaveIn = NULL;
    WAVEHDR wh = {0};
    WAVEFORMATEX wfx = {0};
    BYTE* buffer = NULL;
    FILE* fp = NULL;
    BOOL success = FALSE;

    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = DEFAULT_CHANNELS;
    wfx.nSamplesPerSec = DEFAULT_SAMPLE_RATE;
    wfx.wBitsPerSample = DEFAULT_BITS_PER_SAMPLE;
    wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    // 👇 关键修改：传入 deviceId 而不是 WAVE_MAPPER
    if (waveInOpen(&hWaveIn, deviceId, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        printf("  错误：无法打开设备 %u。\n", deviceId);
        goto cleanup;
    }

    // ...（其余代码完全不变，直到 cleanup）
    
    DWORD bufferSize = wfx.nAvgBytesPerSec * seconds;
    buffer = (BYTE*)malloc(bufferSize);
    if (!buffer) {
        printf("  错误：内存不足。\n");
        goto cleanup;
    }

    wh.lpData = (LPSTR)buffer;
    wh.dwBufferLength = bufferSize;
    if (waveInPrepareHeader(hWaveIn, &wh, sizeof(WAVEHDR)) != MMSYSERR_NOERROR ||
        waveInAddBuffer(hWaveIn, &wh, sizeof(WAVEHDR)) != MMSYSERR_NOERROR ||
        waveInStart(hWaveIn) != MMSYSERR_NOERROR) {
        printf("  错误：录音初始化失败。\n");
        goto cleanup;
    }

    printf("  正在录音");
    for (int i = seconds; i > 0; i--) {
        printf("\r  正在录音... 剩余 %2d 秒", i);
        fflush(stdout);
        Sleep(1000);
    }
    printf("\r  录音完成！                \n");

    waveInStop(hWaveIn);
    waveInReset(hWaveIn);

    fp = fopen(filename, "wb");
    if (!fp) {
        printf("  错误：无法创建文件。\n");
        goto cleanup;
    }

    // 写入 WAV 头（不变）
    DWORD chunkSize = 36 + wh.dwBytesRecorded;
    DWORD subchunk1Size = 16;
    WORD audioFormat = 1;

    fwrite("RIFF", 1, 4, fp);
    fwrite(&chunkSize, 1, 4, fp);
    fwrite("WAVEfmt ", 1, 8, fp);
    fwrite(&subchunk1Size, 1, 4, fp);
    fwrite(&audioFormat, 1, 2, fp);
    fwrite(&wfx.nChannels, 1, 2, fp);
    fwrite(&wfx.nSamplesPerSec, 1, 4, fp);
    fwrite(&wfx.nAvgBytesPerSec, 1, 4, fp);
    fwrite(&wfx.nBlockAlign, 1, 2, fp);
    fwrite(&wfx.wBitsPerSample, 1, 2, fp);
    fwrite("data", 1, 4, fp);
    fwrite(&wh.dwBytesRecorded, 1, 4, fp);
    fwrite(buffer, 1, wh.dwBytesRecorded, fp);
    fclose(fp);

    success = TRUE;

cleanup:
    if (buffer) {
        if (hWaveIn) waveInUnprepareHeader(hWaveIn, &wh, sizeof(WAVEHDR));
        free(buffer);
    }
    if (hWaveIn) waveInClose(hWaveIn);
    return success;
}