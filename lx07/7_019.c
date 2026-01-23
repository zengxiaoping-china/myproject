#include <stdio.h>

#define STUDENTS 10
#define COURSES 5

/* 定义存储成绩的二维数组 */
float scores[STUDENTS][COURSES];

/* 函数声明 */
void input_scores();
void calculate_student_averages();
void calculate_course_averages();
void find_highest_score();
void calculate_variance();

int main() {
    printf("请输入 %d 个学生 %d 门课的成绩：\n", STUDENTS, COURSES);
    input_scores(); // 读取数据

    printf("\n---------- 结果输出 ----------\n");

    // 功能 ①：计算每个学生的平均分
    calculate_student_averages();
    printf("\n");

    // 功能 ②：计算每门课的平均分
    calculate_course_averages();
    printf("\n");

    // 功能 ③：找出最高分
    find_highest_score();
    printf("\n");

    // 功能 ④：计算平均分方差
    calculate_variance();

    return 0;
}

// 辅助函数：读取成绩
void input_scores() {
    for (int i = 0; i < STUDENTS; i++) {
        printf("请输入第 %d 个学生的 %d 门课成绩：", i + 1, COURSES);
        for (int j = 0; j < COURSES; j++) {
            scanf("%f", &scores[i][j]);
        }
    }
}

// ① 计算每个学生的平均分
void calculate_student_averages() {
    printf(">>> ① 每个学生的平均分：\n");
    for (int i = 0; i < STUDENTS; i++) {
        float sum = 0;
        for (int j = 0; j < COURSES; j++) {
            sum += scores[i][j];
        }
        float avg = sum / COURSES;
        printf("学生 %d 的平均分: %.2f\n", i + 1, avg);
    }
}

// ② 计算每门课的平均分
void calculate_course_averages() {
    printf(">>> ② 每门课的平均分：\n");
    for (int j = 0; j < COURSES; j++) { // 外层循环遍历课程（列）
        float sum = 0;
        for (int i = 0; i < STUDENTS; i++) { // 内层循环遍历学生（行）
            sum += scores[i][j];
        }
        float avg = sum / STUDENTS;
        printf("课程 %d 的平均分: %.2f\n", j + 1, avg);
    }
}

// ③ 找出所有 50 个分数中最高的分数所对应的学生和课程
void find_highest_score() {
    printf(">>> ③ 最高分信息：\n");
    float max_score = scores[0][0];
    int student_idx = 0;
    int course_idx = 0;

    for (int i = 0; i < STUDENTS; i++) {
        for (int j = 0; j < COURSES; j++) {
            if (scores[i][j] > max_score) {
                max_score = scores[i][j];
                student_idx = i;
                course_idx = j;
            }
        }
    }

    printf("最高分: %.2f\n", max_score);
    printf("对应学生: 第 %d 位\n", student_idx + 1);
    printf("对应课程: 第 %d 门\n", course_idx + 1);
}

// ④ 计算平均分方差
void calculate_variance() {
    printf(">>> ④ 平均分方差：\n");
    float sum_x = 0;    // 用于累加学生的平均分 (Σxi)
    float sum_x2 = 0;   // 用于累加学生平均分的平方 (Σxi²)

    // 1. 先计算每个学生的平均分，并累加到 sum_x 和 sum_x2
    for (int i = 0; i < STUDENTS; i++) {
        float student_sum = 0;
        for (int j = 0; j < COURSES; j++) {
            student_sum += scores[i][j];
        }
        float xi = student_sum / COURSES; // 单个学生的平均分 xi
        sum_x += xi;
        sum_x2 += xi * xi;
    }

    // 2. 根据题目公式计算方差
    // 公式：σ = (1/n)Σxi² - ( (Σxi) / n )²
    float n = STUDENTS;
    float term1 = sum_x2 / n;
    float term2 = (sum_x / n) * (sum_x / n);

    float variance = term1 - term2;

    printf("方差 σ = %.4f\n", variance);
}