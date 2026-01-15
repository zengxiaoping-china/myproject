//创建动态链表

#include <stdio.h>
#include <stdlib.h>

#define LEN sizeof(struct Student)

struct Student {
    long num;
    float score;
    struct Student *next;
};

int n;

struct Student* creat(void) {
    struct Student *head = NULL;
    struct Student *p1, *p2;
    n = 0;

    p1 = (struct Student*)malloc(LEN);
    if (!p1) return NULL;

    scanf("%ld", &p1->num);
    scanf("%f", &p1->score);

    while (p1->num != 0) {
        n++;
        if (n == 1) {
            head = p1;
        } else {
            p2->next = p1;
        }
        p2 = p1;

        p1 = (struct Student*)malloc(LEN);
        if (!p1) break; // 防止 malloc 失败
        scanf("%ld", &p1->num);
        scanf("%f", &p1->score);
    }

    p2->next = NULL;
    free(p1); // 释放最后多分配的节点
    return head;
}

//打印链表函数
void print(struct Student *head){
    struct Student *p=head;
    while (p->next!=NULL)
    {
        printf("%ld\n", p->num);
        printf("%.2f\n", p->score);
        printf("-------------\n");
        p=p->next;
    }
}

//释放动态内存函数
void free_memory(struct Student *head){
    struct Student *p = head;
    while (p != NULL) {
        struct Student *temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {
    struct Student *pt = creat();

    // ✅ 正确遍历链表
    struct Student *p = pt;
    while (p != NULL) {
        printf("%ld\n", p->num);
        printf("%.2f\n", p->score);
        printf("%p\n", (void*)p->next);   // 正确打印指针 
        p = p->next;
    }

    // 可选：释放整个链表内存（避免内存泄漏）
    p = pt;
    while (p != NULL) {
        struct Student *temp = p;
        p = p->next;
        free(temp);
    }

    return 0;
}