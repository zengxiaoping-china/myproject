#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

int main() {
    // 设置控制台为 UTF-8（可选，英文路径不需要）
    SetConsoleOutputCP(CP_UTF8);

    char input[512];
    printf("🎵 测试播放器（使用英文路径）\n");
    printf("输入: p \"C:/path/to/test.mp3\"\n\n");

    while (1) {
        printf(">>> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == 'q') break;
        if (input[0] == 's') {
            mciSendStringA("stop mysound", NULL, 0, NULL);
            mciSendStringA("close mysound", NULL, 0, NULL);
            printf("Stopped.\n");
            continue;
        }
        if (input[0] == 'p' && input[1] == ' ') {
            char* path = input + 2;
            // 去掉首尾引号（如果有的话）
            if (path[0] == '"') {
                path++;
                char* end = strchr(path, '"');
                if (end) *end = '\0';
            }

            // 将 \ 替换为 /
            for (char* p = path; *p; p++) {
                if (*p == '\\') *p = '/';
            }

            char cmd[1024];
            snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias mysound", path);

            MCIERROR err = mciSendStringA(cmd, NULL, 0, NULL);
            if (err != 0) {
                printf("❌ Open failed (error %lu). Path: %s\n", err, path);
            } else {
                err = mciSendStringA("play mysound", NULL, 0, NULL);
                if (err != 0) {
                    printf("❌ Play failed (error %lu)\n", err);
                } else {
                    printf("▶ Playing: %s\n", path);
                }
            }
        }
    }

    mciSendStringA("close all", NULL, 0, NULL);
    return 0;
}