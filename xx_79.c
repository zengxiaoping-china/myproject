//练习指针指向二维数组

#include<stdio.h>

int pintf_array(int *array,int n);

int main(){

    int i,j;

    int a[3][4] = {{20,36,21,45},{78,26,63,98},{36,15,86,74}};

    int *p;

    printf("\na = %lld *a = %lld\n",a,*a);

    printf("\na[0] =%lld *(a+0) = %lld\n",a[0],*(a+0));

    printf("\n&a[0] = %lld &a[0][0] = %lld\n",&a[0],&a[0][0]);

    printf("\n&a[1] = %lld a+1 = %lld\n",&a[1],a+1);

    printf("\n&a[1][0] = %lld *(a+1)+0 = %lld\n",&a[1][0],*(a+1)+0);

    printf("\na[2] = %lld *(a+2) = %lld\n",a[2],*(a+2));

    printf("\n&a[2] = %lld a+2 = %lld\n",&a[2],a+2);

    printf("\na[1][0] = %lld *(*(a+1)+0) = %lld\n",a[1][0],*(*(a+1)+0));

    printf("\n*a[2] = %lld *(*(a+2)+1) = %lld\n\n",*a[2],*(*(a+2)+1));

    //pintf_array(*p,12);

    for ( p = a[0]; p < a[0]+12; p++)
    { 
        if ((p-a[0]) % 4 == 0) printf("\n\n");
        printf("%lld ",*p);  
    }

    printf("\n\n==================\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%lld ",*(*(a+i)+j));
        }
        printf("\n\n");
    }
    p=*(a+2)+2;
    printf("p-*(a+0) = %d\n\n",p-*(a+0));

    int (*p2)[4];

    p2=a;

    scanf("%d %d",&i,&j);

    printf("a[%d][%d] = %d",i,j,*(*(p2+i)+j));

    return 0;

}

int pintf_array(int *array,int n){
    int *p,i=0;
    for ( p = array; p < array+n; p++)
    { 
        printf("%lld ",*p);
        i++;
        if (i % 4 == 0) printf("\n");
    }
}

