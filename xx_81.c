//练习使用指针变量引用字符串

#include<stdio.h>

int main(){
    char a[]="I am a student";

    char b[20];

    char *p1 = a;

    char *p2 = b;

    int i;

    printf("\na = %s\n",a);

    for (i = 0; a[i] != '\0'; i++)
    {
        b[i] = a[i];
    }
    b[i] = '\0';

    printf("\nb = %s\n",b);

    printf("\np1 = %s\n",p1);

    for (; *p1 != '\0'; p1++,p2++)
    {
        *p2 = *p1;
        //printf("\np2+%d = %c\n",i,*(p2+i));
    }
    *p2 = '\0';

    printf("\np1 = %s\n",p1);

    p2=b;

    printf("\np2 = %s\n",p2);

    return 0;
}