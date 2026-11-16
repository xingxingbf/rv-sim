#include <stdio.h>
#include "list.h"
#include "io.h"

void app_run(void)
{
    Node *head = NULL;
    int number;
    Student s;
    char name[NAME_L];
    Node *p;

    while (1) {
        printf("1头插 2尾插 3按名删除 4查找 5打印整表 9释放 0退出\n");
        printf("输入以执行：");
        scanf("%d", &number);

        if (number == 0) {
            break;
        } else if (number == 1) {
            scanf("%s %d", s.name, &s.score);
            head = list_add(head, s);
        } else if (number == 2) {
            scanf("%s %d", s.name, &s.score);
            head = list_append(head, s);
        } else if (number == 3) {
            scanf("%s", name);
            head = list_remove(head, name);
        } else if (number == 4) {
            scanf("%s", name);
            p = list_find(head, name);
            if (p == NULL) {
                printf("没有这个人\n");
            } else {
                printf("已查询: %s %d\n", p->data.name, p->data.score);
            }
        } else if (number == 5) {
            list_print(head);
        } else if (number == 9) {
            list_clear(head);
            head = NULL;
            printf("已经完成了释放");
        } else {
            printf("你输入的数字不在选项内。");
        }
    }
    list_clear(head);
}
