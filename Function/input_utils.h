#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <stdio.h>

// 清空输入缓冲区（处理 scanf/fgets 残留）
void clear_input_buffer(void);

// 安全读取一行（最多 max_len - 1 字符，自动去 \n）
char* safe_fgets(char *buffer, int max_len, FILE *stream);

// 输入并校验正整数（带提示和范围）
int input_positive_int(const char *prompt, int min_val, int max_val);

// 输入并校验字符串（非空、长度限制）
void input_nonempty_string(const char *prompt, char *output, size_t output_size);

// 输入并校验单字符（从给定选项中选择，如 "MF"）
char input_char_from_options(const char *prompt, const char *valid_chars);

#endif // INPUT_UTILS_H