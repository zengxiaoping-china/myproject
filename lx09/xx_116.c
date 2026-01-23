/*习题5.有10个学生,每个学生的数据包括学号、姓名、3门课程的成绩,从键盘输入10个学5.有10个学生,每个学生的数据包括学号、姓名、3门课程的成绩,从键盘输入10个学
生数据,要求输出3门课程总平均成绩,以及最高分的学生的数据(包括学号、姓名、3门课程成绩、平均分数)。*/

#include<stdio.h>
#define N 10

struct Student
{
    long int num;
    char name[20];
    float score[3];
    float aver;
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
        p->aver=(p->score[0]+p->score[1]+p->score[2])/3;
    }
}

void sort(struct Student *p){
    int i,j,k;
    struct Student temp;
    for ( i = 0; i < N-1; i++)
    {
        k=i;
        for ( j = i+1; j < N; j++)
        {
            if ((p+k)->aver<(p+j)->aver)
            {
                k=j;
            }
        }
        if (k!=i)
        {
            temp=*(p+k),*(p+k)=*(p+i),*(p+i)=temp;
        }   
    }
}

void print(struct Student *p){
    int i;
    printf(" NUM     NAME SCORE-1 SCORE-2 SCORE-3 AVER\n");
    for ( i = 0; i < N; i++,p++)
    {
        printf("%-6d",p->num);
        printf("%-10s",p->name);
        printf("%-6.2f %-6.2f %-6.2f",p->score[0],p->score[1],p->score[2]);
        printf("%-6.2f\n",p->aver);
    }
}

int main(){
    struct Student stu[N];
    struct Student *p=stu;
    input(p);
    sort(p);
    printf("----------------------------------\n");//分隔线
    print(p);
    return 0;
}
