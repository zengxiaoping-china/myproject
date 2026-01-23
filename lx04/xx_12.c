//练习打印 ASCII 码表，包括 0-127 和 128-255 范围内的字符

#include <stdio.h>
#include <ctype.h>

int main() {
    printf("\n\n=====================================  ASCII  (0-127) =====================================\n\n");
    for (int i = 0; i < 128; i++) {
        if (isprint(i)) {
            printf(" %3d: '%c'\t", i, i);
        } else {
            printf(" %3d: ' '\t", i);
        }
        if (i % 12 ==0)
        {
            printf("\n");
        }
        
    }

    printf("\n\n=====================================  ASCII (128-255) =========================================\n\n");
    //printf("(注意：显示效果取决于终端编码，UTF-8 下可能为乱码)\n\n");
    for (int i = 128; i < 256; i++) {
        unsigned char c = (unsigned char)i;
        // 在 UTF-8 终端中，128-255 单字节通常无效，但仍尝试输出
        printf(" %3d: ", i);
        if (c >= 128) {
            putchar(c);  // 直接输出字节
            printf(" (0x%02X)\t", c);
        } else {
            printf("' '\t");
        }
        if (i % 12 == 0)
        {
            printf("\n");
        }
    }

    return 0;
}