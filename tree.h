#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef int Data;

typedef struct TreeNode {
    Data data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
    int size;
} Tree;

// 创建空树，内存不足时返回 NULL。
Tree* treeCreate(void);

// 销毁整棵树，传入 NULL 时什么也不做。
void treeDestroy(Tree* t);

// 插入新值，重复值和内存分配失败都会返回 false。
bool treeInsert(Tree* t, Data value);

// 删除指定值，树中没有该值时返回 false。
bool treeRemove(Tree* t, Data value);

// 查找节点，找不到时返回 NULL。
TreeNode* treeFind(const Tree* t, Data value);

// 判断树中是否有指定值。
bool treeContains(const Tree* t, Data value);

// 通过 outValue 返回最小值，空树或 outValue 为 NULL 时返回 false。
bool treeMin(const Tree* t, Data* outValue);

// 通过 outValue 返回最大值，空树或 outValue 为 NULL 时返回 false。
bool treeMax(const Tree* t, Data* outValue);

bool treeIsEmpty(const Tree* t);
int treeSize(const Tree* t);
void treeClear(Tree* t);

void treePreOrder(const Tree* t);
void treeInOrder(const Tree* t);
void treePostOrder(const Tree* t);
void treePrint(const Tree* t);

// 高度按节点数计算，空树为 0，叶节点为 1。
int treeHeight(const Tree* t);
int treeCountLeaves(const Tree* t);

#endif
