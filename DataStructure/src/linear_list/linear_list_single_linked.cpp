#include "linear_list_single_linked.h"

#include <cstddef>
#include <cstdio>
#include <cstdlib>

bool InitListWithHead(LinkList* L) {
    *L = (LNode*)malloc(sizeof(LNode));
    if (*L == NULL) {
        return false;
    }
    (*L)->next = NULL;
    return true;
}

bool InitListNoHead(LinkList* L) {
    *L = NULL;
    return true;
}

LinkList ListHeadInsertWithHead(LinkList L, ElemType e) {
    if (L == NULL) {
        return NULL;
    }

    LNode* new_node = (LNode*)malloc(sizeof(LNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = e;
    new_node->next = L->next;
    L->next = new_node;
    return L;
}

LinkList ListHeadInsertNoHead(LinkList L, ElemType e) {
    LNode* new_node = (LNode*)malloc(sizeof(LNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = e;
    new_node->next = L;
    return new_node;
}

LinkList ListTailInsertWithHead(LinkList L, ElemType e) {
    if (L == NULL) {
        return NULL;
    }

    LNode* new_node = (LNode*)malloc(sizeof(LNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = e;
    new_node->next = NULL;

    if (L->next == NULL) {
        L->next = new_node;
        return L;
    }

    LNode* current = L->next;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return L;
}

LinkList ListTailInsertNoHead(LinkList L, ElemType e) {
    LNode* new_node = (LNode*)malloc(sizeof(LNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = e;
    new_node->next = NULL;

    if (L == NULL) {
        return new_node;
    }

    LNode* current = L;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return L;
}

void ListDestroy(LinkList* L) {
    if (*L == NULL) {
        return;
    }
    LNode* current = *L;
    while (current != NULL) {
        LNode* p = current;
        current = current->next;
        free(p);
    }
    *L = NULL;
}
