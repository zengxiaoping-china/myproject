#include <stdio.h>
#include <string.h>

// 通用转置函数（支持任意类型、任意 n）
void transpose_generic(void* matrix, int n, size_t elem_size) {
    // 临时缓冲区（用于交换）
    char temp[256]; // 足够存一个元素（假设元素 <= 256 字节）
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // 计算 matrix[i][j] 和 matrix[j][i] 的地址
            char* addr_ij = (char*)matrix + (i * n + j) * elem_size;
            char* addr_ji = (char*)matrix + (j * n + i) * elem_size;
            
            // 交换两个元素
            memcpy(temp, addr_ij, elem_size);
            memcpy(addr_ij, addr_ji, elem_size);
            memcpy(addr_ji, temp, elem_size);
        }
    }
}

// 打印整型矩阵
void print_int_matrix(int* mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", mat[i * n + j]);
        }
        printf("\n");
    }
}

// 打印字符型矩阵
void print_char_matrix(char* mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2c ", mat[i * n + j]);
        }
        printf("\n");
    }
}

int main() {
    // ===== 示例1：整型 3x3 矩阵 =====
    int int_mat[] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    int n1 = 3;
    
    printf("原始整型矩阵 (%dx%d):\n", n1, n1);
    print_int_matrix(int_mat, n1);
    
    transpose_generic(int_mat, n1, sizeof(int));
    
    printf("转置后:\n");
    print_int_matrix(int_mat, n1);
    
    printf("\n" "====================\n\n");

    // ===== 示例2：字符型 4x4 矩阵 =====
    char char_mat[] = {
        'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h',
        'i', 'j', 'k', 'l',
        'm', 'n', 'o', 'p'
    };
    int n2 = 4;
    
    printf("原始字符矩阵 (%dx%d):\n", n2, n2);
    print_char_matrix(char_mat, n2);
    
    transpose_generic(char_mat, n2, sizeof(char));
    
    printf("转置后:\n");
    print_char_matrix(char_mat, n2);
    
    return 0;
}