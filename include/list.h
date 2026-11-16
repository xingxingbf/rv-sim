#ifndef LIST_H
#define LIST_H
#define NAME_L 100
typedef struct {
	char name[NAME_L];
	int score;
} Student;
typedef struct Node {
	Student data;
	struct Node *next;
} Node;
Node *list_add(Node *head, Student s);
Node *list_append(Node *head, Student s);
Node *list_remove(Node *head, char *name);
Node *list_find(Node *head, char *name);
void list_print(Node *head);
void list_clear(Node *head);
#endif
