//17.写一函数,实现两个字符串的比较。即自己写一个 strcmp 函数,函数原型为int strcmp(char * p1,char *p2)

#include<stdio.h>
#include<string.h>

//自己瞎写的（有问题）
int new_strcmp(char *p1,char *p2){
    int i,result;
    size_t len_1=strlen(p1);
    size_t len_2=strlen(p2);
    for ( i = 0; p1[i] !='\0'&& p2[i]!='\0'; i++)
    {
        if (p1[i]>p2[i])
        {
            result=1;
            break;
        }
        else if(p1[i]==p2[i])
        {
            if ((i+1)!=len_1&&(i+1)!=len_2)
            {
                continue;
            }
            else if ((i+1)==len_1&&(i+1)==len_2)
            {
                result=0;
                break;
            }
            else if(len_1<len_2)
            {
                result=-1;
                break;
            }
            else{
                result=1;
                break;
            }    
        }
        else if(p1[i]<p2[i]){
            result=-1;
            break;
        }
    }
    return result;
}

//经典标准写法
int new2_strcmp(const char *p1, const char *p2) {
    while (*p1 && (*p1 == *p2)) {
        p1++;
        p2++;
    }
    return *(unsigned char *)p1 - *(unsigned char *)p2;
}

//教学目的写法
int new3_strcmp(char *p1, char *p2) {
    int i = 0;
    while (p1[i] != '\0' && p2[i] != '\0') {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i]; // 直接返回差值
        }
        i++;
    }
    // 有一个字符串已结束
    return p1[i] - p2[i]; // 此时至少一个是 '\0'
}

int main(){
    char str1[256];
    char str2[256];

    printf("请输入第一个字符串：");
    if (fgets(str1,sizeof(str1),stdin)==NULL)
    {
        fprintf(stderr,"获取字符串失败！");
        return 1;
    }
    str1[strcspn(str1,"\n")]='\0';

    printf("请输入第二个字符串：");
    if (fgets(str2,sizeof(str2),stdin)==NULL)
    {
        fprintf(stderr,"获取字符串失败！");
        return 1;
    }
    str2[strcspn(str2,"\n")]='\0';

    printf("\n-------------------------------\n\n");
    
    int cmp=new2_strcmp(str1,str2);
    if (cmp>0)
    {
        printf("大的字符串是：%s\n\n",str1);
    }
    else if (cmp==0)
    {
        printf("两个字符串相同\n\n");
    }
    else
    {
        printf("大的字符串是：%s\n\n",str2);
    }

    printf("函数返回值是：%d\n",cmp);
    return 0;
}