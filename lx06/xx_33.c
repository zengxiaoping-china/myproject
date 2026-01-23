/*学习字符数组*/

#include <stdio.h>

int main() {
    char str1[] = "Hello, World!";
    char str2[] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};

    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    // 输出字符数组表示的菱形图案
    char diamond[][5] = {
        {' ', ' ', '*', ' ', ' '},
        {' ', '*', ' ', '*', ' '},
        {'*', ' ', ' ', ' ', '*'},
        {' ', '*', ' ', '*', ' '},
        {' ', ' ', '*', ' ', ' '}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c", diamond[i][j]);
        }
        printf("\n");
    }
    return 0;
}