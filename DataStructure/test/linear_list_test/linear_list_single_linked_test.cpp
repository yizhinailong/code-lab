#include <stdio.h>

#include "linear_list_single_linked.h"

void IsEmpty(LinkList L) {
    bool flag = ListIsEmpty(L);
    if (flag) {
        printf("现在链表 L 为空\n");
    } else {
        printf("现在链表 L 不为空\n");
    }
}

int main() {
    LinkList L;
    IsEmpty(L);

    InitList(L);
    IsEmpty(L);

    for (int i = 0; i < 10; i++) {
        ListHeadInsert(L, i + 1);
    }
    printf("头插法插入数据完成，插入的数据为：\n");
    PrintList(L);
    IsEmpty(L);

    for (int i = 0; i < 10; i++) {
        ListTailInsert(L, i + 1);
    }
    printf("尾插法插入数据完成，插入的数据为：\n");
    PrintList(L);

    return 0;
}
