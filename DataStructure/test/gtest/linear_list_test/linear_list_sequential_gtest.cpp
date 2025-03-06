#include <gtest/gtest.h>

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

TEST(LinearListTest, Initialization) {
    SqList L;
    InitList(L);
    EXPECT_EQ(Length(L), 0);
    EXPECT_TRUE(Empty(L));
}

TEST(LinearListTest, Insertion) {
    SqList L;
    InitList(L);
    for (int i = 1; i < 31; i++) {
        EXPECT_TRUE(ListInsert(L, i, i));
    }
    EXPECT_EQ(Length(L), 30);
    PrintListInfo(L);
}

TEST(LinearListTest, GetElem) {
    SqList L;
    InitList(L);
    for (int i = 1; i < 31; i++) {
        EXPECT_TRUE(ListInsert(L, i, i));
    }

    for (int i = 0; i < 10; i++) {
        int e, index = rand() % 20 + 1; // 确保索引在有效范围内
        if (GetElem(L, index, e)) {
            EXPECT_EQ(e, index);
        } else {
            FAIL() << "访问出错, index = " << index;
        }
    }
}

TEST(LinearListTest, LocateElem) {
    SqList L;
    InitList(L);
    for (int i = 1; i < 31; i++) {
        EXPECT_TRUE(ListInsert(L, i, i));
    }

    for (int i = 1; i < 31; i++) {
        int result = LocateElem(L, i);
        EXPECT_EQ(result, i);
    }

    int result = LocateElem(L, 31);
    EXPECT_EQ(result, -1);
}

TEST(LinearListTest, Deletion) {
    SqList L;
    InitList(L);
    for (int i = 1; i < 31; i++) {
        EXPECT_TRUE(ListInsert(L, i, i));
    }

    for (int i = 1; i < 10; i++) {
        ElemType e;
        EXPECT_TRUE(ListDelete(L, i, e));
        EXPECT_EQ(e, 2 * i - 1);
        PrintListInfo(L);
        printf("删除的元素为 e = %d\n", e);
    }
    EXPECT_EQ(Length(L), 21);
}

TEST(LinearListTest, Destruction) {
    SqList L;
    InitList(L);
    EXPECT_TRUE(DestroyList(L));
    EXPECT_FALSE(DestroyList(L)); // 再次销毁应失败
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
