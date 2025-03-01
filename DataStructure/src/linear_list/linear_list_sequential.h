#pragma once

#define MAXSIZE 100

typedef int ElemType;

/**
 * @brief 定义线性表（顺序表）的数据结构。
 *
 * 该结构体用于表示一个顺序存储的线性表，包含以下成员：
 * - data: 指向存储数据元素的动态数组指针。
 * - length: 当前线性表中实际存储的数据元素个数。
 * - max_size: 线性表的最大容量，即可以存储的最大数据元素个数。
 */
typedef struct {
    ElemType* data; ///< 动态分配的数组，用于存储线性表中的元素。
    int length;     ///< 当前线性表中实际存储的数据元素个数。
    int max_size;   ///< 线性表的最大容量，即可以存储的最大数据元素个数。
} SqList;

/**
 * @brief 初始化线性表。构建一个空的顺序表。
 *
 * 该函数用于初始化一个空的顺序表，分配必要的内存并设置初始状态。
 * 初始化后，线性表的实际长度为0，最大容量为预定义的 MAXSIZE。
 *
 * @param L 要初始化的线性表（SqList 类型）。
 */
void InitList(SqList& L);

/**
 * @brief 求表长。返回线性表 L 的长度，即 L 中数据元素的个数。
 *
 * 该函数用于获取线性表中实际存储的数据元素个数。通过访问 `SqList` 结构体中的 `length` 成员变量，
 * 可以快速获得线性表的当前长度。
 *
 * @param L 要查询长度的线性表（SqList 类型）。
 * @return int 线性表 L 的长度。
 */
int Length(SqList& L);

/**
 * @brief 查找线性表中指定元素的位置。
 *
 * 该函数用于在线性表中查找指定元素 `e` 的位置。通过遍历 `SqList` 结构体中的 `data` 成员变量，
 * 可以找到元素 `e` 在线性表中的索引位置。如果找到该元素，则返回其在表中的位置（从1开始计数）；
 * 如果未找到该元素，则返回 -1 表示未找到。
 *
 * @param L 要查找的线性表（SqList 类型）。
 * @param e 要查找的元素。
 * @return int 元素 `e` 在线性表中的位置（从1开始计数），如果未找到则返回 -1。
 */
int LocateElem(SqList& L, ElemType e);

/**
 * @brief 获取线性表中指定位置的元素。
 *
 * 该函数用于获取线性表中第 i 个位置的数据元素，并将其存储在 `elem` 参数中。
 * 通过访问 `SqList` 结构体中的 `data` 成员变量，可以根据索引 i 获取对应的元素值。
 * 如果索引 i 超出范围，则函数返回 `false`，表示获取失败；否则返回 `true`，表示获取成功。
 *
 * @param L 要查询的线性表（SqList 类型）。
 * @param i 要获取元素的位置索引（从1开始计数）。
 * @param e 用于存储获取到的元素值的引用。
 * @return true 获取成功时返回 `true`。
 * @return false 获取失败时返回 `false`，表示索引超出范围。
 */
bool GetElem(SqList& L, int i, ElemType& e);

/**
 * @brief 在线性表中指定位置插入元素。
 *
 * 该函数用于在线性表的第 i 个位置插入一个新元素 e。如果插入成功，则返回 `true`；
 * 如果插入失败（例如索引超出范围或线性表已满），则返回 `false`。
 * 插入操作会将索引 i 及其之后的所有元素向后移动一位，以腾出空间给新元素。
 *
 * @param L 要操作的线性表（SqList 类型）。
 * @param i 插入元素的位置索引（从1开始计数）。
 * @param e 要插入的新元素。
 * @return true 插入成功时返回 `true`。
 * @return false 插入失败时返回 `false`，可能由于索引超出范围或线性表已满。
 */
bool ListInsert(SqList& L, int i, ElemType e);

/**
 * @brief 从线性表中删除指定位置的元素。
 *
 * 该函数用于从线性表的第 i 个位置删除一个元素，并将被删除的元素值存储在 `e` 参数中。
 * 删除操作会将索引 i 之后的所有元素向前移动一位，以填补空缺。
 * 如果删除成功，则返回 `true`；如果删除失败（例如索引超出范围或线性表为空），则返回 `false`。
 *
 * @param L 要操作的线性表（SqList 类型）。
 * @param i 删除元素的位置索引（从1开始计数）。
 * @param e 用于存储被删除元素值的引用。
 * @return true 删除成功时返回 `true`。
 * @return false 删除失败时返回 `false`，可能由于索引超出范围或线性表为空。
 */
bool ListDelete(SqList& L, int i, ElemType& e);

/**
 * @brief 打印线性表中的所有元素。
 *
 * 该函数用于遍历并打印线性表中所有存储的数据元素。通过访问 `SqList` 结构体中的 `data` 和 `length` 成员变量，
 * 可以逐个输出线性表中的元素。
 *
 * @param L 要打印的线性表（SqList 类型）。
 */
void PrintList(SqList& L);

/**
 * @brief 判断线性表是否为空。
 *
 * 该函数用于检查线性表是否为空。通过访问 `SqList` 结构体中的 `length` 成员变量，
 * 如果 `length` 为0，则表示线性表为空，返回 `true`；否则返回 `false`。
 *
 * @param L 要检查的线性表（SqList 类型）。
 * @return true 线性表为空时返回 `true`。
 * @return false 线性表不为空时返回 `false`。
 */
bool Empty(SqList& L);

/**
 * @brief 销毁线性表并释放内存。
 *
 * 该函数用于销毁线性表，并释放与线性表相关的动态分配内存。
 * 销毁后，线性表的 `data` 指针将被置为 `NULL`，`length` 和 `max_size` 将被重置为 0。
 * 如果销毁成功，返回 `true`；如果线性表未正确初始化或已销毁，则返回 `false`。
 *
 * @param L 要销毁的线性表（SqList 类型）。
 * @return true 销毁成功时返回 `true`。
 * @return false 销毁失败时返回 `false`，可能由于线性表未初始化或已销毁。
 */
bool DestroyList(SqList& L);
