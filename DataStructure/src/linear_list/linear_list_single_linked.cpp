#include "linear_list_single_linked.h"

#include <stdio.h>
#include <stdlib.h>

bool InitList(LinkList L) {
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return true;
}

LinkList ListHeadInsert(LinkList L, ElemType e) {
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = L->next;
    L->next = s;
    return L;
}

LinkList ListTailInsert(LinkList L, ElemType e) {
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;
    LNode* tail = L;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = s;
    return L;
}

bool ListIsEmpty(LinkList L) {
    return L == NULL || L->next == NULL;
}

void PrintList(LinkList L) {
    LNode* temp = L;
    while (temp->next) {
        printf("%d ", temp->next->data);
        temp = temp->next;
    }
    printf("\n");
}
