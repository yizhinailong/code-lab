#include <stdio.h>
#include <stdlib.h>

#include "linear_list_sequential.h"

void PrintListInfo(SqList& L) {
    if (Empty(L)) {
        printf("线性表为空\n");
    } else {
        int list_length = Length(L);
        printf("线性表的长度为 %d\n", list_length);
        PrintList(L);
    }
}

int main() {
    SqList L;
    InitList(L);

    for (int i = 1; i < 31; i++) {
        ListInsert(L, i, i);
    }

    PrintListInfo(L);

    for (int i = 0; i < 10; i++) {
        printf("测试 GetElem : ");
        int e, index = rand() % 20;
        if (GetElem(L, index, e)) {
            printf("访问成功, index = %d, e = %d\n", index, e);
        } else {
            printf("访问出错, index = %d\n", index);
            e = index;
        }

        printf("测试 LocateElem : ");
        int result = LocateElem(L, e);
        if (result == -1) {
            printf("不存在这个值\n");
        } else {
            printf("结果为: result = %d\n", result);
        }
    }

    for (int i = 1; i < 10; i++) {
        ElemType e;
        ListDelete(L, i, e);
        printf("被删除的元素为第 %d 个元素，e = %d\n", i, e);
        PrintListInfo(L);
    }

    if (DestroyList(L)) {
        printf("线性表销毁成功\n");
    } else {
        printf("线性表未被正确初始化或者已经被销毁了\n");
    }

    return 0;
}
