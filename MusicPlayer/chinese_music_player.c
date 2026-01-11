#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

// 将 UTF-8 字符串转为 UTF-16
int utf8_to_utf16(const char* utf8, wchar_t* utf16, int size) {
    return MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, size);
}

// 使用系统默认程序播放 MP3（支持中文路径）
int play_mp3_with_default_player(const char* utf8_file_path) {
    wchar_t wpath[MAX_PATH] = {0};
    if (!utf8_to_utf16(utf8_file_path, wpath, MAX_PATH)) {
        printf("❌ 路径转换失败\n");
        return -1;
    }

    // 使用 ShellExecuteW 打开文件（等效于双击）
    HINSTANCE result = ShellExecuteW(NULL, L"open", wpath, NULL, NULL, SW_SHOWNORMAL);
    
    if ((INT_PTR)result <= 32) {
        wprintf(L"❌ 无法打开文件: %ls (错误码: %d)\n", wpath, (int)(INT_PTR)result);
        return -1;
    }

    wprintf(L"✅ 已启动播放器: %ls\n", wpath);
    return 0;
}

// 遍历文件夹并播放所有 MP3
int play_all_mp3_in_folder_utf8(const char* utf8_folder_path) {
    wchar_t wfolder[MAX_PATH] = {0};
    if (!utf8_to_utf16(utf8_folder_path, wfolder, MAX_PATH)) {
        printf("❌ 文件夹路径无效\n");
        return -1;
    }

    wchar_t wsearch[MAX_PATH] = {0};
    wcsncpy(wsearch, wfolder, MAX_PATH - 10);
    wcscat(wsearch, L"\\*.mp3");

    WIN32_FIND_DATAW find_data;
    HANDLE hFind = FindFirstFileW(wsearch, &find_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"📁 未找到 MP3 文件: %ls\n", wfolder);
        return -1;
    }

    SetConsoleOutputCP(CP_UTF8);

    do {
        if (wcscmp(find_data.cFileName, L".") == 0 || 
            wcscmp(find_data.cFileName, L"..") == 0) continue;

        wchar_t full_path[MAX_PATH] = {0};
        swprintf(full_path, MAX_PATH, L"%ls\\%ls", wfolder, find_data.cFileName);

        char utf8_path[MAX_PATH * 4] = {0};
        WideCharToMultiByte(CP_UTF8, 0, full_path, -1, utf8_path, sizeof(utf8_path), NULL, NULL);

        printf("\n🎵 即将播放: %s\n", utf8_path);
        printf("按 Enter 播放，输入 'q' 退出...\n");

        char input[10];
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'q' || input[0] == 'Q') break;

        // 👉 关键：改用系统播放器
        play_mp3_with_default_player(utf8_path);

        printf("已启动播放器... 按 Enter 播放下一首\n");
        fgets(input, sizeof(input), stdin);

    } while (FindNextFileW(hFind, &find_data));

    FindClose(hFind);
    return 0;
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);

    const char* folder = "D:\\python\\music"; // ← 修改为你的路径
    play_all_mp3_in_folder_utf8(folder);

    printf("\n👋 播放列表结束，按回车退出...\n");
    getchar();
    return 0;
}