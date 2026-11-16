#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
Node *nodenew(Student s)
{
	Node *n;
	n = malloc(sizeof(Node));
	if (n == NULL){
		printf("分配失败");
		return NULL;
	}
	n->data = s;
	n->next = NULL;
	return n;
}
Node *list_add(Node *head,Student s)
{
	Node *n;
	n = nodenew(s);
	if (n == NULL) {
		return head;
	}
	n->next=head;
	return n;
}
Node *list_append(Node *head, Student s)
{
	Node *n = nodenew(s);
	Node *p;
	if (n == NULL) return head;
	if (head == NULL) return n;
	p = head;
	while (p->next != NULL){
		p = p->next;
	}
	p ->next =n;
	return head;
}
Node *list_find(Node *head, char *name)
{
	Node *p = head;
	while (p != NULL){
		if (strcmp(p->data.name,name)==0){
			return p;
		}
		p=p->next;
	}
	return NULL;
}
Node *list_remove(Node *head, char *name)
{
	Node *p, *q;
	if (head == NULL) return NULL;
	if (strcmp(head->data.name, name) == 0) {
		p=head;
		head = head->next;
		free(p);
		return head;
	}
	p = head;
	while (p->next != NULL){
		if (strcmp(p->next->data.name,name)==0){
			q = p->next;
			p->next = q->next;
			free(q);
			return head;
		}
		p = p->next;
	}
	return head;
}
void list_print(Node *head)
{
	Node *p = head;
	int i = 1;
	if (p == NULL) {
		printf("内容为空\n");
		return;
	}
	while (p != NULL){
		printf("%d.%s %d\n",i,p->data.name,p->data.score);
		p=p->next;
		i++;
	}
}
void list_clear(Node *head)
{
	Node *p = head;
	Node *q;
	while (p != NULL){
		q=p->next;
		free(p);
		p=q;
	}
}
