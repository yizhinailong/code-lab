#include "linear_list_sequential.h"

#include <stdio.h>
#include <stdlib.h>

void InitList(SqList& L) {
    L.data = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
    L.max_size = MAXSIZE;
    L.length = 0;
}

int Length(SqList& L) {
    return L.length;
}

int LocateElem(SqList& L, ElemType e) {
    for (int i = 0; i < Length(L); i++) {
        if (L.data[i] == e) {
            return i + 1;
        }
    }
    return -1;
}

bool GetElem(SqList& L, int i, ElemType& e) {
    if (i <= 0 || i > Length(L)) {
        return false;
    }

    e = L.data[i - 1];
    return true;
}

bool ListInsert(SqList& L, int i, ElemType e) {
    if (i <= 0 || i > Length(L) + 1) {
        return false;
    }

    if (Length(L) >= L.max_size) {
        return false;
    }

    for (int j = Length(L); j >= i; j--) {
        L.data[j] = L.data[j - 1];
    }

    L.data[i - 1] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList& L, int i, ElemType& e) {
    if (Empty(L) || i <= 0 || i > Length(L)) {
        return false;
    }

    e = L.data[i - 1];
    for (int j = i; j < Length(L); j++) {
        L.data[j - 1] = L.data[j];
    }

    L.length--;
    return true;
}

void PrintList(SqList& L) {
    printf("线性表中的元素为 ");
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

bool Empty(SqList& L) {
    return L.length == 0;
}

bool DestroyList(SqList& L) {
    if (L.data != NULL) {
        free(L.data);
        L.data = NULL;
        L.length = 0;
        L.max_size = 0;
        return true;
    }
    return false;
}
