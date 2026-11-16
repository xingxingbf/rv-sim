#include <stdio.h>

typedef struct Node {
    int v;
    struct Node *next;
} Node;

typedef struct {
    int xb[3];
    int total;
} Box;

int level3(Node *p) { return p->v; }
int level2(Node *p) { return level3(p->next); }
int level1(Node *head) { return level2(head); }

int main(void)
{
    Node a, b, c, *p;
    a.v = 1; a.next = &b;
    b.v = 5; b.next = &c;
    c.v = 9; c.next = NULL;

    for (p = &a; p != NULL; p = p->next) {
        printf("v = %d\n", p->v);
    }

    Box box;
    int i;
    box.total = 0;
    for (i = 0; i < 4; i++) {
        box.xb[i] = 100 + i;
    }
    printf("xb = %d %d %d\n", box.xb[0], box.xb[1], box.xb[2]);
    printf("total = %d\n", box.total);

    Node x;
    x.v = 7;
    x.next = NULL;
    printf("%d\n", level1(&x));

    return 0;
}
