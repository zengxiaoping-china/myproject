//练习返回指针值的函数

#include<stdio.h>

void search(int (*p)[4]);

int main(){
    int score[][4] = {{65,78,65,84},{78,50,85,54},{65,78,89,52}};
    search(score);
    return 0;
}

void search(int (*p)[4]){
    int i,j,k=0;
    for ( i = 0; i < 3; i++)
    {   
        
        if(k) printf("\n----------------------------------\n");
        int count=1; 
        for (j = 0; j < 4; j++)
        {
            if (*(*(p+i)+j)<60)
            {
                if(count) printf("\n学生号是：%d 的同学有成绩不及格\n",i);
                printf("\n他第 %d 门课程不及格，成绩是：%d\n",j+1,*(*(p+i)+j));
                count=0,k=1;
            }
        }
    }
}