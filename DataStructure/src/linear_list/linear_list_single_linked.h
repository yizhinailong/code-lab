#pragma once

typedef int ElemType;

/**
 * @brief 定义单链表节点及链表类型的数据结构。
 *
 * 该结构体用于表示单链表的节点和链表类型，包含以下成员和类型定义：
 * - LNode: 链表节点结构体，包含数据域和指针域
 * - LinkList: 链表头指针类型，指向链表头节点
 */
typedef struct LNode {
    ElemType data;      ///< 数据存储域，保存当前节点的元素值（类型由ElemType定义）
    struct LNode* next; ///< 指针域，存储直接后继节点的地址（末节点指向NULL）
} LNode, *LinkList;

/**
 * @brief 初始化单链表。构建一个空链表结构。
 *
 * 该函数用于初始化单链表，创建头节点并设置初始状态。
 * 初始化成功后，链表将包含一个数据域无效的头节点（head node），
 * 其next指针指向 NULL ，表示空链表状态。
 *
 * @param L 要初始化的链表头指针（LinkList类型），
 *          成功时L指向新创建的头节点，
 *          失败时L将被置为 NULL
 * @return true  成功分配头节点内存，完成初始化
 * @return false 内存分配失败，头节点创建未完成
 */
bool InitList(LinkList L);

/**
 * @brief 使用头插法向单链表插入新元素
 *
 * 在链表的最前端插入新节点，新节点将成为链表的首元节点。
 * 时间复杂度为O(1)，适用于需要频繁在链表头部操作的场景。
 *
 * @param L 链表头指针，操作成功后指向新插入的节点
 * @param e 待插入的元素值，类型与ElemType定义一致
 * @return LinkList 成功返回新节点指针，失败返回NULL
 */
LinkList ListHeadInsert(LinkList L, ElemType e);

/**
 * @brief 使用尾插法向单链表插入新元素
 *
 * 在链表的末尾插入新节点，新节点将成为链表的最后一个节点。
 * 时间复杂度为O(n)，其中n是链表的长度，因为需要遍历链表找到尾节点。
 * 适用于需要频繁在链表尾部操作的场景。
 *
 * @param L 链表头指针，指向链表的头节点
 * @param e 待插入的元素值，类型与ElemType定义一致
 * @return LinkList 成功返回新插入节点的指针，失败返回NULL
 */
LinkList ListTailInsert(LinkList L, ElemType e);

/**
 * @brief 检查单链表是否为空
 *
 * 该函数用于判断给定的单链表是否为空。
 * 空链表的定义是头节点的next指针指向NULL。
 *
 * @param L 链表头指针，指向链表的头节点
 * @return true  链表为空
 * @return false 链表不为空
 */
bool ListIsEmpty(LinkList L);

// bool ListDeleteElem(LinkList L, ElemType e); // 删除指定元素
// bool ListLocateElem(LinkList L, ElemType& e); // 元素查找定位
// int ListGetLength(LinkList L);                // 获取链表长度
// void ListReverse(LinkList L);                // 链表逆置
// void ListDestroy(LinkList L);                // 销毁链表
// bool ListMerge(LinkList La, LinkList Lb);   // 合并有序链表
// bool ListHasCycle(LinkList L);                // 检测环存在性
// LNode* ListGetMidNode(LinkList L);            // 获取中间节点

/**
 * @brief 打印单链表中的所有元素
 *
 * 该函数用于遍历并打印单链表中的所有元素。
 * 打印时跳过头节点，从首元节点开始打印。
 *
 * @param L 链表头指针，指向链表的头节点
 */
void PrintList(LinkList L);
