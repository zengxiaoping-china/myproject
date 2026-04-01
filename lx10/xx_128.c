#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_LENGHT 20
#define FILE_NAME "students.txt"

typedef struct 
{
    int id;
    float chinese;
    float math;
    float english;
    float avargrade;
    char name[NAME_LENGHT];
}Stu;

// 从文本文件加载
void loadStudents(Stu **students, int *count) {
        FILE *fp = fopen(FILE_NAME, "r");
        if (!fp) {
            *students = NULL;
            *count = 0;
            return;
        }

        // 先统计行数（预分配内存）
        int lines = 0;
        char ch;
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '\n') lines++;
        }
        // 处理最后一行无换行的情况
        if (lines > 0 || ftell(fp) > 0) {
            rewind(fp);
            if (fgetc(fp) != EOF) {
                rewind(fp);
                if (lines == 0) lines = 1;
            }
        } else {
            lines = 0;
        }
        rewind(fp);

        if (lines == 0) {
            *students = NULL;
            *count = 0;
            fclose(fp);
            return;
        }

        *students = (Stu *)malloc(lines * sizeof(Stu));
        if (!*students) {
            fprintf(stderr, "❌ 内存分配失败！\n");
            *count = 0;
            fclose(fp);
            return;
        }

        char line[256];
        int i = 0;
        while (fgets(line, sizeof(line), fp)) {
            // 去掉换行符
            line[strcspn(line, "\r\n")] = '\0';
            if (strlen(line) == 0) continue;

            Stu s;
            char nameBuf[NAME_LENGHT];
            int items = sscanf(line, "%d|%[^|]|%f|%f|%f|%f", &s.id, nameBuf, &s.chinese, &s.math,&s.english,&s.avargrade);
            if (items == 6) {
                strncpy(s.name, nameBuf, NAME_LENGHT - 1);
                s.name[NAME_LENGHT - 1] = '\0';
                (*students)[i++] = s;
            }
            // 如果解析失败，跳过该行（容错）
        }

        *count = i;
        fclose(fp);
}

void displayAllStudents(Stu *students, int count) {
    if (count == 0) { printf("暂无学生数据！\n"); return; }
    printf("\n=== 所有学生信息 ===\n");
    printf("%-8s %-10s %-8s %-8s %-8s %-16s\n", "学号", "姓名", "语文", "数学", "英语", "平均成绩");
    printf("------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-10s %-8.2f %-8.2f %-8.2f %-8.2f\n",
               students[i].id, students[i].name,
               students[i].chinese, students[i].math,students[i].english,students[i].avargrade);
    }
}

void freeStudents(Stu *students) {
    free(students);
}

int main(){
    int i,count=0;
    Stu *students = NULL;

    loadStudents(&students, &count);
    printf("✅ 已加载 %d 条学生记录。\n", count);
    printf("按回车继续...");
    getchar();

    displayAllStudents(students, count);
    freeStudents(students);
}