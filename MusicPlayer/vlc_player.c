#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

// 将 UTF-8 字符串转为 UTF-16
int utf8_to_utf16(const char* utf8, wchar_t* utf16, int size) {
    return MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, size);
}

// 从系统 PATH 中查找 vlc.exe 的完整路径
int find_vlc_in_path(wchar_t* out_path, int out_size) {
    // 获取 PATH 环境变量（宽字符）
    DWORD len = GetEnvironmentVariableW(L"PATH", NULL, 0);
    if (len == 0 || len > 32767) return 0;

    wchar_t* path_env = malloc(len * sizeof(wchar_t));
    if (!path_env) return 0;

    GetEnvironmentVariableW(L"PATH", path_env, len);

    // 分割 PATH（以 ; 分隔）
    wchar_t* context = NULL;
    wchar_t* dir = wcstok_s(path_env, L";", &context);
    while (dir) {
        // 构造 candidate: dir\vlc.exe
        wchar_t candidate[MAX_PATH] = {0};
        wcsncpy(candidate, dir, MAX_PATH - 10);
        size_t dir_len = wcsnlen(candidate, MAX_PATH);
        if (dir_len > 0 && candidate[dir_len - 1] != L'\\') {
            wcscat(candidate, L"\\");
        }
        wcscat(candidate, L"vlc.exe");

        // 检查文件是否存在
        if (GetFileAttributesW(candidate) != INVALID_FILE_ATTRIBUTES) {
            wcsncpy(out_path, candidate, out_size - 1);
            out_path[out_size - 1] = L'\0';
            free(path_env);
            return 1; // 找到！
        }

        dir = wcstok_s(NULL, L";", &context);
    }

    free(path_env);
    return 0; // 未找到
}

// 静默播放 MP3
int play_mp3_with_vlc_silent(const char* utf8_file_path) {
    wchar_t wpath[MAX_PATH] = {0};
    if (!utf8_to_utf16(utf8_file_path, wpath, MAX_PATH)) {
        printf("❌ 路径转换失败\n");
        return -1;
    }

    // 👉 关键：先查找 vlc.exe 完整路径
    wchar_t vlc_full_path[MAX_PATH] = {0};
    if (!find_vlc_in_path(vlc_full_path, MAX_PATH)) {
        printf("❌ 未在系统 PATH 中找到 vlc.exe，请确认已安装并加入环境变量\n");
        return -1;
    }

    // 构造参数（注意：第一个参数是 exe，第二个是命令行）
    wchar_t args[32767];
    swprintf(args, sizeof(args)/sizeof(wchar_t),
             L"\"%ls\" --play-and-exit --quiet --intf dummy --no-video --no-embedded-video --no-splash \"%ls\"",
             vlc_full_path, wpath);

    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // 注意：这里 lpApplicationName = NULL，命令行包含完整路径
    BOOL success = CreateProcessW(
        NULL,         // lpApplicationName = NULL
        args,         // lpCommandLine 包含完整 exe 路径
        NULL, NULL, FALSE,
        CREATE_NO_WINDOW,
        NULL, NULL,
        &si, &pi
    );

    if (!success) {
        DWORD err = GetLastError();
        wprintf(L"❌ 启动 VLC 失败 (错误码: %lu)\n", err);
        wprintf(L"   尝试的路径: %ls\n", vlc_full_path);
        return -1;
    }

    wprintf(L"▶ 静默播放: %ls\n", wpath);
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

// ========== 以下函数保持不变 ==========

int play_single_file(const char* file_path) {
    size_t len = strlen(file_path);
    if (len < 4) return -1;
    const char* ext = file_path + len - 4;
    if (_stricmp(ext, ".mp3") != 0) {
        printf("⚠️ 仅支持 .mp3 文件\n");
        return -1;
    }
    return play_mp3_with_vlc_silent(file_path);
}

int play_folder(const char* folder_path) {
    wchar_t wfolder[MAX_PATH] = {0};
    if (!utf8_to_utf16(folder_path, wfolder, MAX_PATH)) {
        printf("❌ 文件夹路径无效\n");
        return -1;
    }

    wchar_t wsearch[MAX_PATH] = {0};
    wcsncpy(wsearch, wfolder, MAX_PATH - 10);
    wcscat(wsearch, L"\\*.mp3");

    WIN32_FIND_DATAW find_data;
    HANDLE hFind = FindFirstFileW(wsearch, &find_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        wprintf(L"📁 文件夹中未找到 .mp3 文件: %ls\n", wfolder);
        return -1;
    }

    int count = 0;
    do {
        if (wcscmp(find_data.cFileName, L".") == 0 ||
            wcscmp(find_data.cFileName, L"..") == 0) continue;

        wchar_t full_path[MAX_PATH] = {0};
        swprintf(full_path, MAX_PATH, L"%ls\\%ls", wfolder, find_data.cFileName);

        char utf8_path[MAX_PATH * 4] = {0};
        WideCharToMultiByte(CP_UTF8, 0, full_path, -1, utf8_path, sizeof(utf8_path), NULL, NULL);

        printf("\n🎵 [%d] 发现歌曲: %s\n", ++count, utf8_path);
        if (play_mp3_with_vlc_silent(utf8_path) != 0) {
            printf("⚠️ 播放失败，跳过...\n");
        }
    } while (FindNextFileW(hFind, &find_data));

    FindClose(hFind);
    printf("\n✅ 共播放 %d 首歌曲\n", count);
    return 0;
}

int is_directory(const char* path) {
    wchar_t wpath[MAX_PATH] = {0};
    if (!utf8_to_utf16(path, wpath, MAX_PATH)) return -1;
    DWORD attr = GetFileAttributesW(wpath);
    if (attr == INVALID_FILE_ATTRIBUTES) return -1;
    return (attr & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
}

int main() {
    setlocale(LC_ALL, ".UTF-8");
    SetConsoleOutputCP(CP_UTF8);

    printf("🎶 VLC 智能音乐播放器\n");
    printf("请输入 MP3 文件路径 或 音乐文件夹路径（支持中文）:\n> ");

    char input_path[1024] = {0};
    if (!fgets(input_path, sizeof(input_path), stdin)) {
        printf("❌ 读取输入失败\n");
        return 1;
    }

    size_t len = strlen(input_path);
    if (len > 0 && input_path[len - 1] == '\n') {
        input_path[len - 1] = '\0';
    }

    if (strlen(input_path) == 0) {
        printf("❌ 路径不能为空\n");
        return 1;
    }

    int type = is_directory(input_path);
    if (type == -1) {
        printf("❌ 路径不存在或无效: %s\n", input_path);
        return 1;
    }

    if (type == 1) {
        printf("\n📁 检测到文件夹，开始播放所有 MP3...\n");
        play_folder(input_path);
    } else {
        printf("\n🎵 检测到单个文件，开始播放...\n");
        play_single_file(input_path);
    }

    printf("\n👋 播放结束，按回车退出...\n");
    getchar();
    return 0;
}