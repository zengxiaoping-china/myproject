//练习递归函数解决汉诺塔问题

#include<stdio.h>

void hanoi(int n, char one, char two, char three, int *step);
void move(char x, char y, int *step);
int get_final_step(int step);

int main(){
    int m, step = 0;
    printf("\n请输入汉诺塔的层数:");
    scanf("%d", &m);
    
    printf("\n这是%d层汉诺塔执行的步骤:\n\n", m);
    hanoi(m, 'A', 'B', 'C', &step);
    
    int total_steps = get_final_step(step);
    printf("\n\n程序执行结束 一共执行了%2d次操作\n", total_steps);
    return 0;
}

void hanoi(int n, char one, char two, char three, int *step){
    if(n == 1){
        move(one, three, step);
    } else {
        hanoi(n-1, one, three, two, step);
        move(one, three, step);
        hanoi(n-1, two, one, three, step);
    }
}

void move(char x, char y, int *step){
    (*step)++;
    printf("Step %2d: %c --> %c", *step, x, y);
    
    if(*step % 5 == 0) {
        printf("\n\n");
    } else {
        printf("\t");
    }
}

int get_final_step(int step){
    return step;
}