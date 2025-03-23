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
 * @brief 初始化带头结点的单链表
 *
 * 创建一个包含头结点的空链表。头结点的数据域无效，其 `next` 指针初始化为 `NULL`。
 *
 * @param L 需要初始化的链表头指针的指针（初始化后指向头结点）
 * @return true 初始化成功（头结点成功分配）
 * @return false 内存分配失败，`L` 将被置为 `NULL`
 */
bool InitListWithHead(LinkList* L);

/**
 * @brief 初始化无头结点的空单链表
 *
 * 将链表头指针初始化为空（`NULL`），表示链表中没有节点。
 * 该函数直接设置头指针为 `NULL`，无需内存分配。
 *
 * @param L 需要初始化的链表头指针的指针
 * @return true 总是返回 `true`，因为初始化无头结点的链表不会失败
 */
bool InitListNoHead(LinkList* L);

/**
 * @brief 在带头结点的单链表头部插入新节点
 *
 * 新节点插入到头结点之后，成为链表的第一个有效数据节点。
 * 时间复杂度为 O(1)。
 *
 * @param L 链表的头指针（指向头结点，必须已初始化）
 * @param e 待插入的元素值
 * @return LinkList
 *   - 成功时返回头结点指针（`L` 不变）
 *   - 内存分配失败时返回 `NULL`
 */
LinkList ListHeadInsertWithHead(LinkList L, ElemType e);

/**
 * @brief 在无头结点的单链表头部插入新节点
 *
 * 新节点将成为链表的新头节点。时间复杂度为 O(1)。
 *
 * @param L 当前链表的头指针（原头节点）
 * @param e 待插入的元素值
 * @return LinkList
 *   - 成功时返回新头节点指针（调用者需更新头指针）
 *   - 内存分配失败时返回 `NULL`
 */
LinkList ListHeadInsertNoHead(LinkList L, ElemType e);

/**
 * @brief 在带头结点的单链表尾部插入新节点
 *
 * 新节点插入到头结点之后的最后一个数据节点之后。时间复杂度为 O(n)。
 *
 * @param L 链表的头指针（指向头结点，必须已初始化）
 * @param e 待插入的元素值
 * @return LinkList
 *   - 成功时返回头结点指针（`L` 不变）
 *   - 内存分配失败时返回 `NULL`
 */
LinkList ListTailInsertWithHead(LinkList L, ElemType e);

/**
 * @brief 在无头结点的单链表尾部插入新节点
 *
 * 新节点将成为链表的最后一个节点。时间复杂度为 O(n)。
 *
 * @param L 当前链表的头指针（原头节点，可为 NULL 表示空链表）
 * @param e 待插入的元素值
 * @return LinkList
 *   - 成功时返回新头节点指针（链表为空时返回新节点指针）
 *   - 内存分配失败时返回 `NULL`
 */
LinkList ListTailInsertNoHead(LinkList L, ElemType e);

/**
 * @brief 销毁单链表并释放所有节点内存
 *
 * 该函数遍历链表并释放所有节点的内存，包括头节点（若有），同时将头指针置空以避免悬空指针。
 *
 * @param L 需要销毁的链表头指针的指针（指向头节点的指针）
 */
void ListDestroy(LinkList* L);

// bool ListIsEmptyWithHead(LinkList L);
// bool ListIsEmptyNoHead(LinkList L);

// bool ListDeleteElem(LinkList L, ElemType e);

// bool ListLocateElem(LinkList L, ElemType& e); // 元素查找定位

// int ListGetLength(LinkList L);                // 获取链表长度

// void ListReverse(LinkList L);                // 链表逆置

// bool ListMerge(LinkList La, LinkList Lb);   // 合并有序链表

// bool ListHasCycle(LinkList L);                // 检测环存在性

// LNode* ListGetMidNode(LinkList L);            // 获取中间节点
