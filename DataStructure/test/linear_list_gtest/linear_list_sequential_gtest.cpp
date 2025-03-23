#include "linear_list_sequential.h"

#include <gtest/gtest.h>

// 测试初始化列表
TEST(InitListTest, InitializesListCorrectly) {
    SqList list;
    InitList(list);
    EXPECT_NE(list.data, nullptr);
    EXPECT_EQ(list.max_size, MAXSIZE);
    EXPECT_EQ(list.length, 0);
    free(list.data);
}

// 测试获取列表长度
TEST(LengthTest, ReturnsCorrectLength) {
    SqList list;
    InitList(list);
    EXPECT_EQ(Length(list), 0);

    ListInsert(list, 1, 10);
    EXPECT_EQ(Length(list), 1);

    ListInsert(list, 2, 20);
    EXPECT_EQ(Length(list), 2);

    free(list.data); // 清理内存
}

// 测试查找元素
TEST(LocateElemTest, ElementExists_ReturnsCorrectIndex) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 1);
    ListInsert(list, 2, 2);
    ListInsert(list, 3, 3);

    EXPECT_EQ(LocateElem(list, 2), 2);
    EXPECT_EQ(LocateElem(list, 3), 3);
    EXPECT_EQ(LocateElem(list, 1), 1);

    free(list.data); // 清理内存
}

TEST(LocateElemTest, ElementDoesNotExist_ReturnsNegativeOne) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 1);
    ListInsert(list, 2, 2);
    ListInsert(list, 3, 3);

    EXPECT_EQ(LocateElem(list, 4), -1);
    EXPECT_EQ(LocateElem(list, 0), -1);

    free(list.data); // 清理内存
}

TEST(LocateElemTest, EmptyList_ReturnsNegativeOne) {
    SqList list;
    InitList(list);
    EXPECT_EQ(LocateElem(list, 1), -1);

    free(list.data); // 清理内存
}

TEST(LocateElemTest, DuplicateElements_ReturnsFirstIndex) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 1);
    ListInsert(list, 2, 2);
    ListInsert(list, 3, 2);
    ListInsert(list, 4, 3);

    EXPECT_EQ(LocateElem(list, 2), 2);

    free(list.data); // 清理内存
}

// 测试获取元素
TEST(GetElemTest, ElementExists_ReturnsCorrectValue) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);
    ListInsert(list, 2, 20);
    ListInsert(list, 3, 30);

    ElemType e;
    EXPECT_TRUE(GetElem(list, 1, e));
    EXPECT_EQ(e, 10);

    EXPECT_TRUE(GetElem(list, 2, e));
    EXPECT_EQ(e, 20);

    EXPECT_TRUE(GetElem(list, 3, e));
    EXPECT_EQ(e, 30);

    free(list.data); // 清理内存
}

TEST(GetElemTest, ElementDoesNotExist_ReturnsFalse) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);

    ElemType e;
    EXPECT_FALSE(GetElem(list, 0, e));
    EXPECT_FALSE(GetElem(list, 2, e));

    free(list.data); // 清理内存
}

// 测试插入元素
TEST(ListInsertTest, InsertAtValidPosition_ReturnsTrue) {
    SqList list;
    InitList(list);
    EXPECT_TRUE(ListInsert(list, 1, 10));
    EXPECT_TRUE(ListInsert(list, 2, 20));
    EXPECT_TRUE(ListInsert(list, 3, 30));

    EXPECT_EQ(Length(list), 3);
    EXPECT_EQ(list.data[0], 10);
    EXPECT_EQ(list.data[1], 20);
    EXPECT_EQ(list.data[2], 30);

    free(list.data); // 清理内存
}

TEST(ListInsertTest, InsertAtInvalidPosition_ReturnsFalse) {
    SqList list;
    InitList(list);
    EXPECT_FALSE(ListInsert(list, 0, 10));
    EXPECT_FALSE(ListInsert(list, 2, 20));

    free(list.data); // 清理内存
}

TEST(ListInsertTest, InsertInFullList_ReturnsFalse) {
    SqList list;
    InitList(list);
    for (int i = 1; i <= MAXSIZE; i++) {
        EXPECT_TRUE(ListInsert(list, i, i));
    }
    EXPECT_FALSE(ListInsert(list, MAXSIZE + 1, MAXSIZE + 1));

    free(list.data); // 清理内存
}

// 测试删除元素
TEST(ListDeleteTest, DeleteAtValidPosition_ReturnsTrue) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);
    ListInsert(list, 2, 20);
    ListInsert(list, 3, 30);

    ElemType e;
    EXPECT_TRUE(ListDelete(list, 2, e));
    EXPECT_EQ(e, 20);
    EXPECT_EQ(Length(list), 2);
    EXPECT_EQ(list.data[0], 10);
    EXPECT_EQ(list.data[1], 30);

    free(list.data); // 清理内存
}

TEST(ListDeleteTest, DeleteAtInvalidPosition_ReturnsFalse) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);

    ElemType e;
    EXPECT_FALSE(ListDelete(list, 0, e));
    EXPECT_FALSE(ListDelete(list, 2, e));

    free(list.data); // 清理内存
}

TEST(ListDeleteTest, DeleteFromEmptyList_ReturnsFalse) {
    SqList list;
    InitList(list);

    ElemType e;
    EXPECT_FALSE(ListDelete(list, 1, e));

    free(list.data); // 清理内存
}

// 测试打印列表
TEST(PrintListTest, PrintsListCorrectly) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);
    ListInsert(list, 2, 20);
    ListInsert(list, 3, 30);

    testing::internal::CaptureStdout();
    PrintList(list);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "线性表中的元素为 10 20 30 \n");

    free(list.data); // 清理内存
}

// 测试判断列表是否为空
TEST(EmptyTest, EmptyList_ReturnsTrue) {
    SqList list;
    InitList(list);
    EXPECT_TRUE(Empty(list));

    ListInsert(list, 1, 10);
    EXPECT_FALSE(Empty(list));

    free(list.data); // 清理内存
}

// 测试销毁列表
TEST(DestroyListTest, DestroysListCorrectly) {
    SqList list;
    InitList(list);
    ListInsert(list, 1, 10);
    ListInsert(list, 2, 20);
    ListInsert(list, 3, 30);

    EXPECT_TRUE(DestroyList(list));
    EXPECT_EQ(list.data, nullptr);
    EXPECT_EQ(list.length, 0);
    EXPECT_EQ(list.max_size, 0);
}
