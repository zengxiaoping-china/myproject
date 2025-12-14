// simple_window_unicode.c
#include <windows.h>

#define ID_EDIT 1001

HWND g_hEdit = NULL;

// 使用宽字符版本的窗口过程（W -> Wide）
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // 使用 CreateWindowW（宽字符版）
            g_hEdit = CreateWindowW(
                L"EDIT",                          // 宽字符串：L"..."
                L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                10, 10, 280, 25,
                hwnd,
                (HMENU)ID_EDIT,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam); // 注意是 DefWindowProcW
    }
    return 0;
}

// WinMain 的宽字符版本入口（实际仍用 WinMain，但内部全用 W 函数）
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    
    // 注册窗口类 —— 使用宽字符版 WNDCLASSW
    WNDCLASSEXW wc = {0};
    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"SimpleInputWindow";
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassExW(&wc)) {  // RegisterClassExW
        MessageBoxW(NULL, L"窗口类注册失败！", L"错误", MB_ICONERROR);
        return 1;
    }

    // 创建窗口 —— 使用 CreateWindowW
    HWND hwnd = CreateWindowW(
        L"SimpleInputWindow",
        L"请输入字符串",      // ← 中文在这里！用 L"" 包裹
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        320, 100,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxW(NULL, L"窗口创建失败！", L"错误", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {  // GetMessageW
        TranslateMessage(&msg);
        DispatchMessageW(&msg);              // DispatchMessageW
    }

    return (int)msg.wParam;
}