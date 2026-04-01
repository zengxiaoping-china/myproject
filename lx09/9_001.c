//定义共用体与公用占用的存储空间大小

#include<stdio.h>
#include<string.h>

union Date
{
    int i;
    float f;
    char str[20];
};


int main(){
    union Date date;
    printf("共用体占用了 %d 个字节大小\n",sizeof(date));
    return 0;
}