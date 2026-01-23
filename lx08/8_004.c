//15.有一个班4个学生,5门课程。
//①求第1门课程的平均分;
//②找出有两门以上课程不及格的学生,输出他们的学号和全部课程成绩及平均成绩;
//③找出平均成绩在 90 分以上或全部课程成绩在85分以上的学生。分别编3个函数实现以上3个要求。

#include<stdio.h>
#include<string.h>

#define STU_NUM 4
#define COURSE_NUM 5

void calculate_average(float arr[][COURSE_NUM]){
    float sum=0.0,aver=0.0;
    int i,course_index = 0;;
    for ( i = 0; i < STU_NUM; i++)
    {
        sum=sum+arr[i][course_index];
    }
    aver=sum/STU_NUM;
    printf("%d 名学生的第 %d 门课的平均成绩是：%2.2f",STU_NUM,course_index+1,aver);
}

void count_failures(float arr[][COURSE_NUM],char *p[]){
    
    int i,j,k;
    int found = 0;
    for ( i = 0; i < STU_NUM; i++)
    {
        int count=0;
        for ( j = 0; j < COURSE_NUM; j++)
        {
            if (arr[i][j]<60)
            {
                count++;
            }
        }
        if (count>=2)
        {
            found = 1;
            printf("至少有两门成绩不及格的学生学号是：%s",*(p+i));
            float sum=0,aver;
            printf("\n\n全部成绩：");
            for ( k = 0; k < COURSE_NUM; k++)
            {
                printf("%2.2f ",arr[i][k]);
                sum=sum+arr[i][k];
            }
            aver=sum/COURSE_NUM;
            printf("\n\n平均成绩：%2.2f\n",aver);
            printf("----------------------------------------\n");
        }
         
    }
    if (!found) {
        printf("没有学生有两门及以上课程不及格。\n");
    }
}

void count_scores_above(float arr[][COURSE_NUM],char *p[]){
    int i,j;
    int found = 0;
    printf("平均成绩在 90 分以上或全部课程成绩在85分以上的学生\n\n");
    for ( i = 0; i < STU_NUM; i++)
    {
        int count=0;
        float sum=0,aver=0;
        for ( j = 0; j < COURSE_NUM; j++)
        {
            sum=sum+arr[i][j];
            if (arr[i][j]>=85)
            {
                count++;
            }
        }
        aver=sum/COURSE_NUM;
        if (aver>=90 || count==5)
        {
            found = 1;
            printf("满足条件的学生学号是：%s\n\n",*(p+i));
        }
    }
    if (!found) {
        printf("没有学生满足条件。\n");
    }
}

int main(){
    float stu_scores[STU_NUM][COURSE_NUM]={{95,92,93,80,96},{89,92,58,52,78},{92,86,85,88,87},{85,96,57,48,82}};
    char *student_num[STU_NUM]={"0001","0002","0003","0004"};
    printf("\n\n");
    calculate_average(stu_scores);
    printf("\n==================================================\n\n");
    count_failures(stu_scores,student_num);
    printf("\n==================================================\n\n");
    count_scores_above(stu_scores,student_num);
    return 0;
}