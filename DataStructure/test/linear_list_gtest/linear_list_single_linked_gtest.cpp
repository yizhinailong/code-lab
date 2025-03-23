#include "linear_list_single_linked.h"

#include <cstdlib>
#include <gtest/gtest.h>

TEST(InitListTest, InitListWithHeadSuccessCase) {
    LinkList L = nullptr;
    bool result = InitListWithHead(&L);

    // 验证结果
    EXPECT_TRUE(result);         // 初始化成功
    EXPECT_NE(L, nullptr);       // 头指针有效
    EXPECT_EQ(L->next, nullptr); // 头节点的 next 为 NULL（空链表）
    // ListDestroy(&L);             // 释放内存
    free(L);
}

TEST(InitListTest, InitListNoHeadSuccessCase) {
    LinkList L = nullptr;
    bool result = InitListNoHead(&L);

    // 验证结果
    EXPECT_TRUE(result);   // 初始化成功
    EXPECT_EQ(L, nullptr); // 头指针为空
    free(L);
}

// 辅助函数：捕获链表内容为字符串（用于验证）
std::string ListToStringWithHead(LinkList L) {
    std::string result;
    LNode* current = L->next; // 跳过头结点
    while (current != NULL) {
        result += std::to_string(current->data) + " ";
        current = current->next;
    }
    return result;
}

TEST(ListHeadInsertWithHeadTest, InsertIntoEmptyList) {
    LinkList head = nullptr;
    InitListWithHead(&head);                 // 初始化头结点

    head = ListHeadInsertWithHead(head, 10); // 插入第一个节点

    // 验证结果
    EXPECT_EQ(ListToStringWithHead(head), "10 ");
    ListDestroy(&head); // 释放内存
}

TEST(ListHeadInsertWithHeadTest, InsertIntoNonEmptyList) {
    LinkList head = nullptr;
    InitListWithHead(&head);
    head = ListHeadInsertWithHead(head, 20); // 插入第一个节点（值为20）
    head = ListHeadInsertWithHead(head, 10); // 插入第二个节点（值为10）

    // 验证链表结构
    EXPECT_EQ(ListToStringWithHead(head), "10 20 ");
    ListDestroy(&head);
}

TEST(ListHeadInsertWithHeadTest, MemoryLeakCheck) {
    LinkList head = nullptr;
    InitListWithHead(&head);
    head = ListHeadInsertWithHead(head, 5);
    ListDestroy(&head);
    EXPECT_EQ(head, nullptr); // 验证指针置空
}

// 辅助函数：捕获链表内容为字符串（无头结点）
std::string ListToStringNoHead(LinkList L) {
    std::string result;
    LNode* current = L;
    while (current != NULL) {
        result += std::to_string(current->data) + " ";
        current = current->next;
    }
    return result;
}

TEST(ListHeadInsertNoHeadTest, InsertIntoEmptyList) {
    LinkList L = nullptr;
    L = ListHeadInsertNoHead(L, 10); // 插入第一个节点

    // 验证结果
    EXPECT_EQ(ListToStringNoHead(L), "10 ");
    ListDestroy(&L); // 释放内存
}

TEST(ListHeadInsertNoHeadTest, InsertIntoNonEmptyList) {
    LinkList L = nullptr;
    L = ListHeadInsertNoHead(L, 20); // 插入第一个节点（值为20）
    L = ListHeadInsertNoHead(L, 10); // 插入第二个节点（值为10）

    // 验证链表结构
    EXPECT_EQ(ListToStringNoHead(L), "10 20 ");
    ListDestroy(&L);
}

TEST(ListHeadInsertNoHeadTest, MemoryLeakCheck) {
    LinkList L = nullptr;
    L = ListHeadInsertNoHead(L, 5);
    ListDestroy(&L);
    EXPECT_EQ(L, nullptr); // 验证指针置空
}

TEST(ListTailInsertWithHeadTest, InsertIntoEmptyList) {
    LinkList head = nullptr;
    InitListWithHead(&head);                 // 初始化头结点

    head = ListTailInsertWithHead(head, 10); // 插入第一个节点

    // 验证结果
    EXPECT_EQ(ListToStringWithHead(head), "10 ");
    ListDestroy(&head); // 释放内存
}

TEST(ListTailInsertWithHeadTest, InsertIntoNonEmptyList) {
    LinkList head = nullptr;
    InitListWithHead(&head);
    head = ListTailInsertWithHead(head, 20); // 插入第一个节点（值为20）
    head = ListTailInsertWithHead(head, 30); // 插入第二个节点（值为30）

    // 验证链表结构
    EXPECT_EQ(ListToStringWithHead(head), "20 30 ");
    ListDestroy(&head);
}

TEST(ListTailInsertWithHeadTest, MemoryLeakCheck) {
    LinkList head = nullptr;
    InitListWithHead(&head);
    head = ListTailInsertWithHead(head, 5);
    ListDestroy(&head);
    EXPECT_EQ(head, nullptr); // 验证指针置空
}

TEST(ListTailInsertNoHeadTest, InsertIntoEmptyList) {
    LinkList L = nullptr;
    L = ListTailInsertNoHead(L, 10); // 插入第一个节点

    // 验证结果
    EXPECT_EQ(ListToStringNoHead(L), "10 ");
    ListDestroy(&L); // 释放内存
}

TEST(ListTailInsertNoHeadTest, InsertIntoNonEmptyList) {
    LinkList L = nullptr;
    L = ListTailInsertNoHead(L, 20); // 插入第一个节点（值为20）
    L = ListTailInsertNoHead(L, 30); // 插入第二个节点（值为30）

    // 验证链表结构
    EXPECT_EQ(ListToStringNoHead(L), "20 30 ");
    ListDestroy(&L);
}

TEST(ListTailInsertNoHeadTest, MemoryLeakCheck) {
    LinkList L = nullptr;
    L = ListTailInsertNoHead(L, 5);
    ListDestroy(&L);
    EXPECT_EQ(L, nullptr); // 验证指针置空
}
