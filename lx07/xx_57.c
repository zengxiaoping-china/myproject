#include<math.h>
#include ".h\test.h" //注意包含了自定义的头文件
extern int A;

int power(int m){
    int y = 1;
    for (int i = 1; i <= m; i++)
    {
        y = y*A;
    }
    
    return(y);
}