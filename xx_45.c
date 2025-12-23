//练习递归函数解决汉诺塔问题

#include<stdio.h>

int main(){
    void hanoi(int n,char one,char two,char three);
    int m;
    printf("input the number of diskes:");
    scanf("%d",&m);
    printf("\nThe step to move %d diskes:\n",m);
    hanoi(m,'A','B','C');
    return 0;
}

// 计数器函数
int count_step(){
    static int step = 0;  // 静态变量，保持值不变
    step++;
    return step;
}

void hanoi(int n,char one,char two,char three){
    void move(char x,char y);
    if(n == 1){
        move(one,three);
    }
    else{
        hanoi(n-1,one,three,two);
        move(one,three);
        hanoi(n-1,two,one,three);
    }
}

void move(char x,char y){
    printf("Step %2d: %c --> %c\n", count_step(), x, y);
}