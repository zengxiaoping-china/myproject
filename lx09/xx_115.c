//习题3.编写一个函数 print,打印一个学生的成绩数组,该数组中有5个学生的数据记录，每个记录包括 num,name,score[3],编写一个函数 input,用来输入5个学生的数据记录,用 print 函数输出这些记录。

#include<stdio.h>
#define N 3

struct Student
{
    long int num;
    char name[20];
    float score[3];
};

void input(struct Student *p) {
    int i, j;
    for (i = 0; i < N; i++, p++) {
        printf("请输入第%d个学生的学号：", i + 1);
        scanf("%ld", &p->num);
        printf("请输入第%d个学生的名字：", i + 1);
        scanf("%s", p->name);

        while (1) {
            printf("请输入第%d个学生的三门成绩：", i + 1);
            scanf("%f %f %f", &p->score[0], &p->score[1], &p->score[2]);

            // 假设成绩合法
            int valid = 1;
            for (j = 0; j < 3; j++) {
                if (p->score[j] < 0 || p->score[j] > 100) {
                    valid = 0;  // 发现非法成绩
                    break;      // 提前退出 for 循环
                }
            }

            if (valid) {
                break;  // ✅ 所有成绩合法，跳出 while
            } else {
                printf("成绩输入错误！请重新输入\n");
                // 清空输入缓冲区（可选，提升健壮性）
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF); 
            }
            // 继续 while 循环，重新输入
        }
    }
}

void print(struct Student *p){
    int i;
    printf(" NUM     NAME SCORE-1 SCORE-2 SCORE-3\n");
    for ( i = 0; i < N; i++,p++)
    {
        printf("%-6d",p->num);
        printf("%-10s",p->name);
        printf("%-6.2f %-6.2f %-6.2f\n",p->score[0],p->score[1],p->score[2]);
    }
}

int main(){
    struct Student stu[N];
    struct Student *p=stu;
    input(p);
    printf("----------------------------------\n");//分隔线
    print(p);
    return 0;
}