/*要求输出100~200的不能被3整除的数。*/

#include <stdio.h>

int main(){
    int i, count=0;

    printf("\n要求输出100~200的不能被3整除的数\n\n");

    for(i=100;i<=200;i++){
        if (i % 3 != 0)
        {
            count++;
            if(count % 10 !=0){
                printf("%d\t", i);
            }
            else{
                printf("%d\n", i);
            }
            
        } 
    }
    // 补最后一行换行
    if (count % 10 != 0) printf("\n");

    printf("\n一共有%d个不能被3整除的数\n", count);
    
    return 0;
}