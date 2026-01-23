//纯指针写法

//有一个班4个学生,5门课程。
//①求第1门课程的平均分;
//②找出有两门以上课程不及格的学生,输出他们的学号和全部课程成绩及平均成绩;
//③找出平均成绩在 90 分以上或全部课程成绩在85分以上的学生。分别编3个函数实现以上3个要求。

#include <stdio.h>

#define STU_NUM 4
#define COURSE_NUM 5

// ① 求第1门课程的平均分（纯指针）
void calculate_average(float (*arr)[COURSE_NUM]) {
    float sum = 0.0;
    float *p = (float *)arr; // 将二维数组首地址转为 float*

    // 第1门课（列索引0）：位于每行的第0个位置
    // 地址依次是: p+0, p+5, p+10, p+15
    for (int i = 0; i < STU_NUM; i++) {
        sum += *(p + i * COURSE_NUM + 0); // 第 i 行，第 0 列
    }
    printf("%d 名学生的第 1 门课的平均成绩是：%.2f\n", STU_NUM, sum / STU_NUM);
}

// ② 找出有两门以上不及格的学生（纯指针）
void count_failures(float (*arr)[COURSE_NUM], char *ids[]) {
    float *data = (float *)arr; // 转为一维指针
    int found = 0;

    for (int i = 0; i < STU_NUM; i++) {
        int fail_count = 0;
        // 检查当前学生（第 i 行）的所有课程
        for (int j = 0; j < COURSE_NUM; j++) {
            if (*(data + i * COURSE_NUM + j) < 60.0f) {
                fail_count++;
            }
        }

        if (fail_count >= 2) {
            found = 1;
            printf("至少有两门成绩不及格的学生学号是：%s\n", ids[i]);
            printf("全部成绩：");
            
            float row_sum = 0.0;
            for (int j = 0; j < COURSE_NUM; j++) {
                float score = *(data + i * COURSE_NUM + j);
                printf("%.2f ", score);
                row_sum += score;
            }
            printf("\n平均成绩：%.2f\n", row_sum / COURSE_NUM);
            printf("----------------------------------------\n");
        }
    }
    if (!found) {
        printf("没有学生有两门及以上课程不及格。\n");
    }
}

// ③ 找出高分学生（纯指针）
void count_scores_above(float (*arr)[COURSE_NUM], char *ids[]) {
    float *data = (float *)arr;
    int found = 0;
    printf("平均成绩在90分以上或全部课程成绩在85分以上的学生：\n\n");

    for (int i = 0; i < STU_NUM; i++) {
        float row_sum = 0.0;
        int all_ge_85 = 1; // 假设全部 >=85

        for (int j = 0; j < COURSE_NUM; j++) {
            float score = *(data + i * COURSE_NUM + j);
            row_sum += score;
            if (score < 85.0f) {
                all_ge_85 = 0;
            }
        }
        float avg = row_sum / COURSE_NUM;

        if (avg >= 90.0f || all_ge_85) {
            found = 1;
            printf("满足条件的学生学号是：%s\n", ids[i]);
        }
    }
    if (!found) {
        printf("没有学生满足条件。\n");
    }
}

// 主函数
int main() {
    float scores[STU_NUM][COURSE_NUM] = {
        {95, 92, 93, 80, 96},
        {89, 92, 58, 52, 78},
        {92, 86, 85, 88, 87},
        {85, 96, 57, 48, 82}
    };
    char *student_ids[STU_NUM] = {"0001", "0002", "0003", "0004"};

    // 定义指向二维数组的指针
    float (*p)[COURSE_NUM] = scores;

    printf("\n");
    calculate_average(p);
    printf("\n==================================================\n\n");
    count_failures(p, student_ids);
    printf("\n==================================================\n\n");
    count_scores_above(p, student_ids);

    return 0;
}