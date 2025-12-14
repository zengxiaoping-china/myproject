// record_gui_2.c - 纯录音版（无 MP3 转换）
#define WIN32_LEAN_AND_MEAN
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#include <windows.h>
#include <mmsystem.h>
#include <commdlg.h>
#include <stdio.h>
#include <wchar.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comdlg32.lib")

// 控件 ID
#define IDC_RECORD   1001
#define IDC_STOP     1002
#define IDC_PAUSE    1003
#define IDC_COMBO    1004
#define IDC_WAVEFORM 1005
#define IDC_STATUS   1006

// 录音参数
#define SAMPLE_RATE      44100
#define CHANNELS         2
#define BITS_PER_SAMPLE  16
#define NUM_BUFFERS      3
#define BUFFER_SIZE      (SAMPLE_RATE * CHANNELS * BITS_PER_SAMPLE / 8 / 10) // 0.1秒

// 全局变量
HWND g_hwnd = NULL;
HWAVEIN g_hWaveIn = NULL;
WAVEHDR* g_waveHeaders = NULL;
BYTE** g_waveBuffers = NULL;
FILE* g_fp = NULL;
WCHAR g_output_file[MAX_PATH] = {0};
BOOL g_recording = FALSE;
BOOL g_paused = FALSE;
int g_volumeData[100] = {0};
int g_volumeIndex = 0;

// 函数声明
void listDevicesToCombo(HWND hwnd);
void startRecording(HWND hwnd);
void stopRecording(HWND hwnd);
void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void updateStatus(const WCHAR* format, ...);
void drawWaveform(HDC hdc, RECT rect);

// ==================== 实现 ====================

void updateStatus(const WCHAR* format, ...) {
    WCHAR buffer[512] = {0};
    va_list args;
    va_start(args, format);
    vswprintf_s(buffer, 512, format, args);
    va_end(args);
    SetWindowTextW(GetDlgItem(g_hwnd, IDC_STATUS), buffer);
}

void listDevicesToCombo(HWND hwnd) {
    HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
    SendMessageW(hCombo, CB_RESETCONTENT, 0, 0);
    UINT numDevs = waveInGetNumDevs();
    for (UINT i = 0; i < numDevs; i++) {
        WAVEINCAPSW caps = {0};
        if (waveInGetDevCapsW(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
            SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)caps.szPname);
        }
    }
    if (numDevs > 0) {
        SendMessageW(hCombo, CB_SETCURSEL, 0, 0);
    }
}

void startRecording(HWND hwnd) {
    if (g_recording) return;

    OPENFILENAMEW ofn = {0};
    WCHAR szFile[MAX_PATH] = {0};
    wcscpy_s(szFile, MAX_PATH, L"recording.wav");
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"WAV Files\0*.wav\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = L"wav";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    if (!GetSaveFileNameW(&ofn)) {
        return;
    }

    wcscpy_s(g_output_file, MAX_PATH, szFile);

    g_fp = _wfopen(g_output_file, L"wb");
    if (!g_fp) {
        MessageBoxW(hwnd, L"无法创建录音文件！", L"错误", MB_ICONERROR);
        return;
    }

    // 写入 44 字节占位
    BYTE dummy[44] = {0};
    fwrite(dummy, 1, 44, g_fp);

    g_waveBuffers = (BYTE**)calloc(NUM_BUFFERS, sizeof(BYTE*));
    g_waveHeaders = (WAVEHDR*)calloc(NUM_BUFFERS, sizeof(WAVEHDR));
    for (int i = 0; i < NUM_BUFFERS; i++) {
        g_waveBuffers[i] = (BYTE*)malloc(BUFFER_SIZE);
        memset(&g_waveHeaders[i], 0, sizeof(WAVEHDR));
        g_waveHeaders[i].lpData = (LPSTR)g_waveBuffers[i];
        g_waveHeaders[i].dwBufferLength = BUFFER_SIZE;
    }

    UINT devId = (UINT)SendMessageW(GetDlgItem(hwnd, IDC_COMBO), CB_GETCURSEL, 0, 0);

    WAVEFORMATEX wfx = {0};
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    wfx.nChannels = CHANNELS;
    wfx.nSamplesPerSec = SAMPLE_RATE;
    wfx.wBitsPerSample = BITS_PER_SAMPLE;
    wfx.nBlockAlign = (wfx.nChannels * wfx.wBitsPerSample) / 8;
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

    MMRESULT mmr = waveInOpen(&g_hWaveIn, devId, &wfx, (DWORD_PTR)waveInProc, (DWORD_PTR)hwnd, CALLBACK_FUNCTION);
    if (mmr != MMSYSERR_NOERROR) {
        MessageBoxW(hwnd, L"无法打开录音设备！", L"错误", MB_ICONERROR);
        fclose(g_fp);
        g_fp = NULL;
        return;
    }

    for (int i = 0; i < NUM_BUFFERS; i++) {
        waveInPrepareHeader(g_hWaveIn, &g_waveHeaders[i], sizeof(WAVEHDR));
        waveInAddBuffer(g_hWaveIn, &g_waveHeaders[i], sizeof(WAVEHDR));
    }

    waveInStart(g_hWaveIn);
    g_recording = TRUE;
    g_paused = FALSE;
    g_volumeIndex = 0;
    memset(g_volumeData, 0, sizeof(g_volumeData));

    SetTimer(hwnd, 1, 100, NULL);
    updateStatus(L"⏺️ 正在录音...");
}

void stopRecording(HWND hwnd) {
    if (!g_recording) return;
    g_recording = FALSE;
    g_paused = FALSE;
    if (g_hWaveIn) {
        waveInReset(g_hWaveIn);
        waveInStop(g_hWaveIn);
        waveInClose(g_hWaveIn);
        g_hWaveIn = NULL;
    }
    KillTimer(hwnd, 1);
    updateStatus(L"⏹️ 正在停止录音...");
}

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    HWND hwnd = (HWND)dwInstance;
    if (uMsg == WIM_DATA) {
        if (g_fp && !g_paused) {
            WAVEHDR* hdr = (WAVEHDR*)dwParam1;
            fwrite(hdr->lpData, 1, hdr->dwBytesRecorded, g_fp);

            short* samples = (short*)hdr->lpData;
            int count = hdr->dwBytesRecorded / sizeof(short);
            long sum = 0;
            for (int i = 0; i < count; i++) {
                sum += abs(samples[i]);
            }
            int avg = (count > 0) ? (int)(sum / count) : 0;
            g_volumeData[g_volumeIndex % 100] = avg;
            g_volumeIndex++;

            waveInAddBuffer(hwi, hdr, sizeof(WAVEHDR));
        }
    } else if (uMsg == WIM_CLOSE) {
        PostMessageW(hwnd, WM_USER + 100, 0, 0); // 自定义结束消息
    }
}

void drawWaveform(HDC hdc, RECT rect) {
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 120, 255));
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int midY = rect.top + height / 2;

    MoveToEx(hdc, rect.left, midY, NULL);
    for (int i = 0; i < 100; i++) {
        int x = rect.left + (i * width) / 100;
        int vol = g_volumeData[(g_volumeIndex - 100 + i + 1000) % 100];
        int y = midY - (vol * height) / 32768;
        if (y < rect.top) y = rect.top;
        LineTo(hdc, x, y);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            g_hwnd = hwnd;
            CreateWindowW(L"BUTTON", L"⏺️ 录音", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 80, 30, hwnd, (HMENU)IDC_RECORD, NULL, NULL);
            CreateWindowW(L"BUTTON", L"⏹️ 停止", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 10, 80, 30, hwnd, (HMENU)IDC_STOP, NULL, NULL);
            CreateWindowW(L"BUTTON", L"⏸️ 暂停", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 190, 10, 80, 30, hwnd, (HMENU)IDC_PAUSE, NULL, NULL);
            CreateWindowW(L"STATIC", L"设备:", WS_CHILD | WS_VISIBLE, 10, 50, 50, 20, hwnd, NULL, NULL, NULL);
            CreateWindowW(L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, 60, 50, 200, 200, hwnd, (HMENU)IDC_COMBO, NULL, NULL);
            CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, 10, 80, 400, 100, hwnd, (HMENU)IDC_WAVEFORM, NULL, NULL);
            CreateWindowW(L"STATIC", L"就绪", WS_CHILD | WS_VISIBLE, 10, 190, 400, 20, hwnd, (HMENU)IDC_STATUS, NULL, NULL);
            listDevicesToCombo(hwnd);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDC_RECORD: startRecording(hwnd); break;
                case IDC_STOP: stopRecording(hwnd); break;
                case IDC_PAUSE:
                    if (g_recording) {
                        g_paused = !g_paused;
                        SetWindowTextW((HWND)lParam, g_paused ? L"▶️ 继续" : L"⏸️ 暂停");
                        updateStatus(g_paused ? L"⏸️ 录音已暂停" : L"▶️ 录音继续");
                    }
                    break;
            }
            break;

        case WM_USER + 100: // 录音结束处理
            if (g_fp) {
                long dataLength = ftell(g_fp) - 44;
                if (dataLength > 0) {
                    rewind(g_fp);
                    // 写入标准 WAV 头
                    fwrite("RIFF", 1, 4, g_fp);
                    DWORD chunkSize = dataLength + 36;
                    fwrite(&chunkSize, 1, 4, g_fp);
                    fwrite("WAVEfmt ", 1, 8, g_fp);
                    DWORD subchunk1Size = 16;
                    fwrite(&subchunk1Size, 1, 4, g_fp);
                    WORD audioFormat = 1;
                    fwrite(&audioFormat, 1, 2, g_fp);
                    WORD numChannels = CHANNELS;
                    fwrite(&numChannels, 1, 2, g_fp);
                    DWORD sampleRate = SAMPLE_RATE;
                    fwrite(&sampleRate, 1, 4, g_fp);
                    DWORD byteRate = SAMPLE_RATE * CHANNELS * BITS_PER_SAMPLE / 8;
                    fwrite(&byteRate, 1, 4, g_fp);
                    WORD blockAlign = CHANNELS * BITS_PER_SAMPLE / 8;
                    fwrite(&blockAlign, 1, 2, g_fp);
                    WORD bitsPerSample = BITS_PER_SAMPLE;
                    fwrite(&bitsPerSample, 1, 2, g_fp);
                    fwrite("data", 1, 4, g_fp);
                    fwrite(&dataLength, 1, 4, g_fp);
                }
                fclose(g_fp);
                g_fp = NULL;
            }

            if (g_waveBuffers) {
                for (int i = 0; i < NUM_BUFFERS; i++) {
                    free(g_waveBuffers[i]);
                }
                free(g_waveBuffers);
                g_waveBuffers = NULL;
            }
            free(g_waveHeaders);
            g_waveHeaders = NULL;

            g_recording = FALSE;
            g_paused = FALSE;

            EnableWindow(GetDlgItem(hwnd, IDC_RECORD), TRUE);
            EnableWindow(GetDlgItem(hwnd, IDC_STOP), FALSE);
            SetWindowTextW(GetDlgItem(hwnd, IDC_PAUSE), L"⏸️ 暂停");
            EnableWindow(GetDlgItem(hwnd, IDC_PAUSE), FALSE);

            updateStatus(L"✅ 录音已保存为 WAV 文件");
            break;

        case WM_DRAWITEM: {
            LPDRAWITEMSTRUCT dis = (LPDRAWITEMSTRUCT)lParam;
            if (dis->CtlID == IDC_WAVEFORM) {
                FillRect(dis->hDC, &dis->rcItem, (HBRUSH)(COLOR_WINDOW + 1));
                drawWaveform(dis->hDC, dis->rcItem);
            }
            return TRUE;
        }

        case WM_TIMER:
            InvalidateRect(GetDlgItem(hwnd, IDC_WAVEFORM), NULL, TRUE);
            break;

        case WM_CLOSE:
            if (g_recording) {
                int ret = MessageBoxW(hwnd, L"正在录音，确定要退出吗？", L"确认退出", MB_ICONQUESTION | MB_YESNO);
                if (ret != IDYES) return 0;
                stopRecording(hwnd);
            }
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            if (g_fp) fclose(g_fp);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const WCHAR CLASS_NAME[] = L"SimpleAudioRecorder";

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME, L"音频录音器（WAV 格式）",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 440, 280,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}