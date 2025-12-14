#define UNICODE
#define _UNICODE
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <commctrl.h>
#include <commdlg.h>

// 自定义消息
#define WM_AUDIO_STOPPED    (WM_USER + 0x100)
#define WM_UPDATE_VOLUME    (WM_USER + 0x101)
#define WM_CLOSE_AUDIO      (WM_USER + 0x102)

// 音频参数
#define SAMPLE_RATE         44100
#define CHANNELS            1
#define BITS_PER_SAMPLE     16
#define BUFFER_SIZE_MS      200
#define NUM_BUFFERS         4

// 控件 ID
#define IDC_DEVICE_COMBO    1001
#define IDC_DURATION_EDIT   1002
#define IDC_OUTPUT_EDIT     1003
#define IDC_BROWSE_BTN      1004
#define IDC_VOLUME_BAR      1005
#define IDC_VOLUME_TEXT     1006
#define IDC_START_BTN       1007
#define IDC_STOP_BTN        1008
#define IDC_STATUS_TEXT     1009

// 全局变量
HWND g_hwnd = NULL;
HWND g_hDeviceCombo = NULL;
HWND g_hDurationEdit = NULL;
HWND g_hOutputEdit = NULL;
HWND g_hBrowseBtn = NULL;
HWND g_hVolumeBar = NULL;
HWND g_hVolumeText = NULL;
HWND g_hStatusText = NULL;
HWND g_hStartBtn = NULL;
HWND g_hStopBtn = NULL;

HWAVEIN g_hWaveIn = NULL;
FILE* g_fp = NULL;
WCHAR g_output_file[MAX_PATH] = {0};
WAVEFORMATEX g_wfx = {0};

volatile BOOL g_recording = FALSE;
volatile int g_lastVolume = 0;

// 全局音频缓冲区
WAVEHDR g_waveHeaders[NUM_BUFFERS] = {0};
BYTE* g_waveBuffers[NUM_BUFFERS] = {0};
DWORD g_bufferSize = 0;

// 函数声明
void listDevicesToCombo(HWND hCombo);
BOOL generateDefaultFilename(WCHAR* buffer, size_t size);
void updateStatus(const WCHAR* fmt, ...);
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ✅ 新增：统一停止录音函数
void stopRecording(HWND hwnd) {
    if (g_recording) {
        g_recording = FALSE;
        if (g_hWaveIn) {
            waveInStop(g_hWaveIn); // 非阻塞
        }
        KillTimer(hwnd, 1);
        updateStatus(L"⏹️ 正在停止录音...");
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_PROGRESS_CLASS | ICC_STANDARD_CLASSES };
    InitCommonControlsEx(&icex);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RecorderWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    g_hwnd = CreateWindowEx(
        0, L"RecorderWindowClass", L"🎙️ Windows 录音工具 v3.6",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, NULL
    );

    if (!g_hwnd) return 1;

    ShowWindow(g_hwnd, nCmdShow);
    UpdateWindow(g_hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            CreateWindow(L"STATIC", L"录音设备:", WS_CHILD | WS_VISIBLE, 10, 10, 80, 20, hwnd, NULL, NULL, NULL);
            g_hDeviceCombo = CreateWindow(L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
                90, 8, 300, 100, hwnd, (HMENU)IDC_DEVICE_COMBO, NULL, NULL);
            listDevicesToCombo(g_hDeviceCombo);

            CreateWindow(L"STATIC", L"录音时长:", WS_CHILD | WS_VISIBLE, 10, 40, 80, 20, hwnd, NULL, NULL, NULL);
            g_hDurationEdit = CreateWindow(L"EDIT", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                90, 38, 100, 20, hwnd, (HMENU)IDC_DURATION_EDIT, NULL, NULL);
            CreateWindow(L"STATIC", L"秒 (0=无限)", WS_CHILD | WS_VISIBLE, 195, 40, 120, 20, hwnd, NULL, NULL, NULL);

            CreateWindow(L"STATIC", L"输出文件:", WS_CHILD | WS_VISIBLE, 10, 70, 80, 20, hwnd, NULL, NULL, NULL);
            g_hOutputEdit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                90, 68, 250, 20, hwnd, (HMENU)IDC_OUTPUT_EDIT, NULL, NULL);
            g_hBrowseBtn = CreateWindow(L"BUTTON", L"📁 浏览...", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                345, 66, 80, 24, hwnd, (HMENU)IDC_BROWSE_BTN, NULL, NULL);

            WCHAR defaultName[MAX_PATH];
            if (generateDefaultFilename(defaultName, MAX_PATH)) {
                SetWindowTextW(g_hOutputEdit, defaultName);
            }

            CreateWindow(L"STATIC", L"音量:", WS_CHILD | WS_VISIBLE, 10, 100, 50, 20, hwnd, NULL, NULL, NULL);
            g_hVolumeBar = CreateWindow(PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                60, 100, 300, 20, hwnd, (HMENU)IDC_VOLUME_BAR, NULL, NULL);
            g_hVolumeText = CreateWindow(L"STATIC", L"0%", WS_CHILD | WS_VISIBLE, 370, 100, 50, 20, hwnd, (HMENU)IDC_VOLUME_TEXT, NULL, NULL);

            g_hStartBtn = CreateWindow(L"BUTTON", L"● 开始录音", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                100, 140, 100, 30, hwnd, (HMENU)IDC_START_BTN, NULL, NULL);
            g_hStopBtn = CreateWindow(L"BUTTON", L"■ 停止", WS_CHILD | WS_VISIBLE | WS_DISABLED,
                220, 140, 100, 30, hwnd, (HMENU)IDC_STOP_BTN, NULL, NULL);

            g_hStatusText = CreateWindow(L"STATIC", L"就绪", WS_CHILD | WS_VISIBLE, 10, 180, 400, 20, hwnd, (HMENU)IDC_STATUS_TEXT, NULL, NULL);

            SetFocus(hwnd);
            break;
        }

        case WM_COMMAND: {
            WORD id = LOWORD(wParam);
            if (id == IDC_BROWSE_BTN) {
                WCHAR filter[] = L"WAV 文件 (*.wav)\0*.wav\0所有文件 (*.*)\0*.*\0";
                OPENFILENAMEW ofn = {0};
                WCHAR filename[MAX_PATH] = {0};
                GetWindowTextW(g_hOutputEdit, filename, MAX_PATH);

                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFile = filename;
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrFilter = filter;
                ofn.nFilterIndex = 1;
                ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

                if (GetSaveFileNameW(&ofn)) {
                    SetWindowTextW(g_hOutputEdit, filename);
                }
            }
            else if (id == IDC_START_BTN) {
                if (g_recording) {
                    // ✅ 空格/点击 start 按钮时正在录音 → 停止
                    stopRecording(hwnd);
                } else {
                    // 开始录音逻辑（略，保持不变）
                    WCHAR durationStr[32], outputFile[MAX_PATH];
                    GetWindowTextW(g_hDurationEdit, durationStr, 32);
                    GetWindowTextW(g_hOutputEdit, outputFile, MAX_PATH);

                    int duration = _wtoi(durationStr);
                    if (duration < 0) duration = 0;

                    if (outputFile[0] == L'\0') {
                        updateStatus(L"❌ 请指定输出文件");
                        return 0;
                    }

                    int sel = (int)SendMessage(g_hDeviceCombo, CB_GETCURSEL, 0, 0);
                    UINT deviceId = (sel == CB_ERR) ? WAVE_MAPPER : (UINT)SendMessage(g_hDeviceCombo, CB_GETITEMDATA, sel, 0);

                    g_wfx.wFormatTag = WAVE_FORMAT_PCM;
                    g_wfx.nChannels = CHANNELS;
                    g_wfx.nSamplesPerSec = SAMPLE_RATE;
                    g_wfx.wBitsPerSample = BITS_PER_SAMPLE;
                    g_wfx.nBlockAlign = g_wfx.nChannels * g_wfx.wBitsPerSample / 8;
                    g_wfx.nAvgBytesPerSec = g_wfx.nSamplesPerSec * g_wfx.nBlockAlign;

                    if (waveInOpen(&g_hWaveIn, deviceId, &g_wfx, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
                        updateStatus(L"❌ 无法打开录音设备");
                        return 0;
                    }

                    wcscpy_s(g_output_file, _countof(g_output_file), outputFile);
                    g_fp = _wfopen(outputFile, L"wb");
                    if (!g_fp) {
                        waveInClose(g_hWaveIn);
                        g_hWaveIn = NULL;
                        updateStatus(L"❌ 无法创建输出文件");
                        return 0;
                    }

                    // 写入 WAV 头（临时）
                    DWORD chunkSize = 36 + 0xFFFFFFFF;
                    fwrite("RIFF", 1, 4, g_fp);
                    fwrite(&chunkSize, 1, 4, g_fp);
                    fwrite("WAVEfmt ", 1, 8, g_fp);
                    DWORD subChunk1Size = 16;
                    fwrite(&subChunk1Size, 1, 4, g_fp);
                    WORD wFormatTag = 1;
                    fwrite(&wFormatTag, 1, 2, g_fp);
                    fwrite(&g_wfx.nChannels, 1, 2, g_fp);
                    fwrite(&g_wfx.nSamplesPerSec, 1, 4, g_fp);
                    fwrite(&g_wfx.nAvgBytesPerSec, 1, 4, g_fp);
                    fwrite(&g_wfx.nBlockAlign, 1, 2, g_fp);
                    fwrite(&g_wfx.wBitsPerSample, 1, 2, g_fp);
                    fwrite("data", 1, 4, g_fp);
                    DWORD dataChunkSize = 0xFFFFFFFF;
                    fwrite(&dataChunkSize, 1, 4, g_fp);

                    g_bufferSize = (g_wfx.nAvgBytesPerSec * BUFFER_SIZE_MS) / 1000;
                    for (int i = 0; i < NUM_BUFFERS; i++) {
                        if (g_waveBuffers[i] == NULL) {
                            g_waveBuffers[i] = (BYTE*)malloc(g_bufferSize);
                        }
                        g_waveHeaders[i].lpData = (LPSTR)g_waveBuffers[i];
                        g_waveHeaders[i].dwBufferLength = g_bufferSize;
                        g_waveHeaders[i].dwFlags = 0;
                        waveInPrepareHeader(g_hWaveIn, &g_waveHeaders[i], sizeof(WAVEHDR));
                        waveInAddBuffer(g_hWaveIn, &g_waveHeaders[i], sizeof(WAVEHDR));
                    }

                    waveInStart(g_hWaveIn);
                    g_recording = TRUE;

                    EnableWindow(g_hStartBtn, FALSE);
                    EnableWindow(g_hStopBtn, TRUE);
                    EnableWindow(g_hDeviceCombo, FALSE);
                    EnableWindow(g_hDurationEdit, FALSE);
                    EnableWindow(g_hOutputEdit, FALSE);
                    EnableWindow(g_hBrowseBtn, FALSE);

                    updateStatus(L"🎤 正在录音... 按 [停止] 或 [空格键] 结束");

                    if (duration > 0) {
                        SetTimer(hwnd, 1, (UINT)(duration * 1000), NULL);
                    }
                }
            }
            else if (id == IDC_STOP_BTN) {
                stopRecording(hwnd);
            }
            break;
        }

        case WM_TIMER:
            if (wParam == 1 && g_recording) {
                stopRecording(hwnd);
            }
            break;

        case WM_KEYDOWN:
            if (wParam == VK_SPACE) {
                // ✅ 统一调用 stopRecording / 触发开始
                if (g_recording) {
                    stopRecording(hwnd);
                } else {
                    // 模拟点击“开始”按钮（会进入录制逻辑）
                    SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_START_BTN, BN_CLICKED), 0);
                }
                return 0;
            } else if (wParam == VK_ESCAPE) {
                PostMessage(hwnd, WM_CLOSE, 0, 0);
                return 0;
            }
            break;

        case WM_UPDATE_VOLUME:
            if (g_recording) {
                int vol = (int)lParam;
                if (vol > 100) vol = 100;
                SendMessage(g_hVolumeBar, PBM_SETPOS, vol, 0);
                WCHAR volText[16];
                swprintf_s(volText, _countof(volText), L"%d%%", vol);
                SetWindowTextW(g_hVolumeText, volText);
            }
            break;

        case WM_CLOSE_AUDIO:
            if (g_hWaveIn) {
                waveInReset(g_hWaveIn);
                waveInClose(g_hWaveIn);
                g_hWaveIn = NULL;
            }
            break;

        case WM_AUDIO_STOPPED:
            if (g_fp) {
                long dataLength = ftell(g_fp) - 44;
                if (dataLength > 0) {
                    fseek(g_fp, 40, SEEK_SET);
                    fwrite(&dataLength, 1, 4, g_fp);
                    fseek(g_fp, 4, SEEK_SET);
                    long riffSize = dataLength + 36;
                    fwrite(&riffSize, 1, 4, g_fp);
                }
                fclose(g_fp);
                g_fp = NULL;
            }

            for (int i = 0; i < NUM_BUFFERS; i++) {
                if (g_waveBuffers[i]) {
                    free(g_waveBuffers[i]);
                    g_waveBuffers[i] = NULL;
                }
            }

            g_recording = FALSE;

            EnableWindow(g_hStartBtn, TRUE);
            EnableWindow(g_hStopBtn, FALSE);
            EnableWindow(g_hDeviceCombo, TRUE);
            EnableWindow(g_hDurationEdit, TRUE);
            EnableWindow(g_hOutputEdit, TRUE);
            EnableWindow(g_hBrowseBtn, TRUE);
            updateStatus(L"✅ 录音已保存");
            KillTimer(hwnd, 1);
            break;

        case WM_CLOSE:
            if (g_recording) {
                int result = MessageBoxW(hwnd, L"正在录音中，确定要退出吗？\n录音将被保存后退出。", L"确认退出", MB_ICONQUESTION | MB_YESNO);
                if (result != IDYES) {
                    return 0;
                }
                stopRecording(hwnd);
                // 等待自然结束（最多3秒）
                DWORD start = GetTickCount();
                while (g_recording && (GetTickCount() - start) < 3000) {
                    MSG msg;
                    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                    Sleep(10);
                }
                if (g_hWaveIn) PostMessage(hwnd, WM_CLOSE_AUDIO, 0, 0);
                if (g_fp) {
                    fclose(g_fp);
                    g_fp = NULL;
                }
            }
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            if (g_fp) { fclose(g_fp); g_fp = NULL; }
            for (int i = 0; i < NUM_BUFFERS; i++) {
                if (g_waveBuffers[i]) {
                    free(g_waveBuffers[i]);
                    g_waveBuffers[i] = NULL;
                }
            }
            if (g_hWaveIn) {
                waveInClose(g_hWaveIn);
                g_hWaveIn = NULL;
            }
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void listDevicesToCombo(HWND hCombo) {
    SendMessage(hCombo, CB_RESETCONTENT, 0, 0);
    UINT num = waveInGetNumDevs();
    if (num == 0) {
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)L"[无可用设备]");
        return;
    }
    for (UINT i = 0; i < num; i++) {
        WAVEINCAPSW caps = {0};
        if (waveInGetDevCapsW(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
            SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)caps.szPname);
            SendMessage(hCombo, CB_SETITEMDATA, i, (LPARAM)i);
        }
    }
    SendMessage(hCombo, CB_SETCURSEL, 0, 0);
}

BOOL generateDefaultFilename(WCHAR* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm t = {0};
    localtime_s(&t, &now);
    return swprintf_s(buffer, size, L"recording_%04d%02d%02d_%02d%02d%02d.wav",
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
        t.tm_hour, t.tm_min, t.tm_sec) > 0;
}

void updateStatus(const WCHAR* fmt, ...) {
    WCHAR buf[256] = {0};
    va_list args;
    va_start(args, fmt);
    vswprintf_s(buf, _countof(buf), fmt, args);
    va_end(args);
    SetWindowTextW(g_hStatusText, buf);
}

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    if (uMsg == WIM_DATA) {
        WAVEHDR* pwh = (WAVEHDR*)dwParam1;

        if (g_fp && g_recording) {
            short* samples = (short*)pwh->lpData;
            DWORD numSamples = pwh->dwBytesRecorded / sizeof(short);

            const float GAIN = 2.0f;
            for (DWORD i = 0; i < numSamples; i++) {
                int amplified = (int)(samples[i] * GAIN);
                if (amplified > 32767) amplified = 32767;
                else if (amplified < -32768) amplified = -32768;
                samples[i] = (short)amplified;
            }

            short maxAmp = 0;
            for (DWORD i = 0; i < numSamples; i++) {
                short amp = abs(samples[i]);
                if (amp > maxAmp) maxAmp = amp;
            }
            g_lastVolume = (int)((float)maxAmp / 32768.0f * 100);
            if (g_lastVolume > 100) g_lastVolume = 100;

            if (g_hwnd) PostMessage(g_hwnd, WM_UPDATE_VOLUME, 0, g_lastVolume);

            fwrite(pwh->lpData, 1, pwh->dwBytesRecorded, g_fp);
        }

        waveInUnprepareHeader(hwi, pwh, sizeof(WAVEHDR));

        if (g_recording && hwi == g_hWaveIn) {
            waveInPrepareHeader(hwi, pwh, sizeof(WAVEHDR));
            waveInAddBuffer(hwi, pwh, sizeof(WAVEHDR));
        }
    }
    else if (uMsg == WIM_CLOSE) {
        if (g_hwnd) {
            PostMessage(g_hwnd, WM_AUDIO_STOPPED, 0, 0);
        }
    }
}