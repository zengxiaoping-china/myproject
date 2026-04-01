//习题12.建立一个链表,每个结点包括:学号、姓名、性别、年龄。输入一个年龄,如果链表中的结点所包含的年龄等于此年龄,则将此结点删去。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student
{
    int num;
    char name[20];
    char sex;
    int age;
    struct Student *next;
};

void input_stuinfo(struct Student *head) {
    if (!head) {
        fprintf(stderr, "学生链表为空！\n");
        return;
    }

    struct Student *p = head;
    int i = 1;
    int c;

    do {
        printf("请输入第%d个学生的信息\n", i);
        
        // 学号
        printf("第%d个学生的学号：", i);
        scanf("%d", &p->num);
        while ((c = getchar()) != '\n' && c != EOF); // 清空学号后的换行

        // 姓名
        printf("第%d个学生的姓名：", i);
        if (fgets(p->name, sizeof(p->name), stdin) == NULL) {
            if (feof(stdin)) {
                fprintf(stderr, "\n输入提前结束（EOF）。\n");
            } else {
                fprintf(stderr, "读取输入失败！\n");
            }
            break;
        }
        p->name[strcspn(p->name, "\n")] = '\0';

        // 性别 —— 关键修正：加空格！
        printf("第%d个学生的性别（M/F）：", i);
        scanf(" %c", &p->sex); // ✅ %c 前加空格，自动跳过空白

        // 年龄
        printf("第%d个学生的年龄：", i);
        scanf("%d", &p->age);
        while ((c = getchar()) != '\n' && c != EOF); // 清空年龄后的换行

        p = p->next;
        i++;
    } while (p != NULL);

    printf("输入结束，一共输入了%d个学生的信息\n", i - 1);
}

// 返回删除后的链表头
struct Student* search_stu_age(struct Student *head, int age) {
    struct Student *prev = NULL;
    struct Student *curr = head;
    int count = 0;

    while (curr != NULL) {
        if (curr->age == age) {
            struct Student *to_delete = curr;
            curr = curr->next;

            if (prev == NULL) {
                // 删除头节点
                head = curr;
            } else {
                prev->next = curr;
            }

            free(to_delete); // ✅ 释放内存
            count++;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (count == 0) {
        printf("没有找到年龄相符的！\n\n");
    } else {
        printf("找到了 %d 个年龄相符的，并将其删除了。\n\n", count);
    }

    return head; // ✅ 返回新头指针
}

void print_stuinfo(struct Student *head){
    struct Student *p;
    p=head;
    int i=1;
    printf("=================学生信息表=================\n\n");
    printf(" NUM      NAME           SEX   AGE\n");
    printf("--------------------------------------\n");
    while (p != NULL) {
        printf("%-6d%-20s%-5c%-4d\n", p->num, p->name, p->sex, p->age);
        p = p->next;
    }
}

int main() {
    // 动态创建6个学生节点
    struct Student *a = malloc(sizeof(struct Student));
    struct Student *b = malloc(sizeof(struct Student));
    struct Student *c = malloc(sizeof(struct Student));
    struct Student *d = malloc(sizeof(struct Student));
    struct Student *e = malloc(sizeof(struct Student));
    struct Student *f = malloc(sizeof(struct Student));

    // 检查内存分配是否成功
    if (!a || !b || !c || !d || !e || !f) {
        fprintf(stderr, "内存分配失败！\n");
        // 简单处理：释放已分配的内存（略）
        return -1;
    }

    // 初始化数据
    a->num = 1001; strcpy(a->name, "zengxiaoping"); a->sex = 'M'; a->age = 25;
    b->num = 1002; strcpy(b->name, "zhangxueyou");  b->sex = 'M'; b->age = 32;
    c->num = 1003; strcpy(c->name, "wangzuxian");   c->sex = 'F'; c->age = 24;
    d->num = 1004; strcpy(d->name, "liudehua");     d->sex = 'M'; d->age = 36;
    e->num = 1005; strcpy(e->name, "dengchao");     e->sex = 'M'; e->age = 28;
    f->num = 1006; strcpy(f->name, "guofucheng");   f->sex = 'M'; f->age = 36;

    // 链接
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    f->next = NULL;

    struct Student *head = a;

    print_stuinfo(head);
    int age;
    printf("\n请输入需要查找的年龄：");
    scanf("%d", &age);
    head = search_stu_age(head, age);
    print_stuinfo(head);

    // ✅ 可选：释放剩余节点（如果需要）
    while (head) {
        struct Student *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}