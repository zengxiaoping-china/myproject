//习题8.输入一行文字,找出其中大写字母、小写字母、空格、数字以及其他字符各有多少。

#include<stdio.h>
#include<string.h>

int main(){
    char string[256];
    int upper = 0, lower = 0, digit = 0, space = 0, other = 0;
    int i;
    printf("\n请输入一行文字：");
    if(fgets(string,sizeof(string),stdin)==NULL){
        printf("输入错误\n");
        return 1;
    }
    string[strcspn(string,"\n")] ='\0';
    /*
    for ( i = 0; string[i] != '\0'; i++)
    {
        if (string[i]>='A' && string[i]<='Z')
        {
            upper++;
        }
        else if (string[i]>='a' && string[i]<='z')
        {
            lower++;
        }
        else if (string[i]>='0' && string[i]<='9')
        {
            digit++;
        }
        else if (string[i]==' ')
        {
            space++;
        }
        else{
            other++;
        }
    }
    */
    //指针法
    char *p;
    p=string;
    while (*p!='\0')
    {
        if(*p>='A' && *p<='Z'){
            upper++;
        }
        else if (*p>='a' && *p<='z')
        {
            lower++;
        }
        else if (*p>='0' && *p<='9')
        {
            digit++;
        }
        else if (*p == ' ')
        {
            space++;
        }
        else{
            other++;
        }
        p++; 
    }
    
    printf("\n这行文字中大写字母有%d个\n\n",upper);
    printf("这行文字中小写字母有%d个\n\n",lower);
    printf("这行文字中阿拉伯数字有%d个\n\n",digit);
    printf("这行文字中空格有%d个\n\n",space);
    printf("这行文字中其他字符有%d个\n",other);
}