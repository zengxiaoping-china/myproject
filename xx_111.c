//

#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(struct Student)

struct Student
{
    long num;
    float srcoe;
    struct Student *next;
};

int n;
struct Student *creat(void){
    struct Student *head;
    struct Student *p1,*p2;
    n=0;
    p1=p2=(struct Student *)malloc(LEN);
    scanf("%ld",&p1->num);
    scanf("%f",&p1->srcoe);
    head=NULL;
    while (p1->num!=0)
    {
        n++;
        if (n==1)
        {
            head=p1;
        }
        else{
            p2->next=p1;
        }
        p2=p1;
        p1=(struct Student *)malloc(LEN);
        scanf("%ld",&p1->num);
        scanf("%f",&p1->srcoe);
    }
    p2->next=NULL;
    return head;
}

int main(){
    struct Student *pt;
    pt=creat();
    for ( ; pt < pt+n; pt++)
    {
        printf("%ld\n",pt->num);
        printf("%2.2f\n",pt->srcoe);
        printf("%ld",pt->next);
        printf("\n-------------\n");
    }
    return 0;
}