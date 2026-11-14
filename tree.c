#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

static void treeNodeDestroy(TreeNode* node);
static TreeNode* treeRemoveNode(TreeNode* node, Data value, bool* removed);
static TreeNode* treeFindMin(TreeNode* node);
static TreeNode* treeFindMax(TreeNode* node);
static void treePreOrderNode(const TreeNode* node);
static void treeInOrderNode(const TreeNode* node);
static void treePostOrderNode(const TreeNode* node);
static void treePrintNode(const TreeNode* node, int depth);
static int treeNodeHeight(const TreeNode* node);
static int treeNodeCountLeaves(const TreeNode* node);

Tree* treeCreate(void) {
    Tree* t = malloc(sizeof(*t));
    if (!t) {
        return NULL;
    }

    t->root = NULL;
    t->size = 0;
    return t;
}

void treeDestroy(Tree* t) {
    if (!t) {
        return;
    }

    treeNodeDestroy(t->root);
    free(t);
}

bool treeInsert(Tree* t, Data value) {
    if (!t) {
        return false;
    }

    // 先找空位，确认能插入后再分配节点。
    TreeNode** link = &t->root;
    while (*link) {
        if (value < (*link)->data) {
            link = &(*link)->left;
        } else if (value > (*link)->data) {
            link = &(*link)->right;
        } else {
            return false;
        }
    }

    TreeNode* newNode = malloc(sizeof(*newNode));
    if (!newNode) {
        return false;
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    *link = newNode;
    t->size++;
    return true;
}

bool treeRemove(Tree* t, Data value) {
    if (!t) {
        return false;
    }

    bool removed = false;
    t->root = treeRemoveNode(t->root, value, &removed);
    if (removed) {
        t->size--;
    }
    return removed;
}

TreeNode* treeFind(const Tree* t, Data value) {
    if (!t) {
        return NULL;
    }

    TreeNode* current = t->root;
    while (current) {
        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else {
            return current;
        }
    }
    return NULL;
}

bool treeContains(const Tree* t, Data value) {
    return treeFind(t, value) != NULL;
}

bool treeMin(const Tree* t, Data* outValue) {
    if (!t || !t->root || !outValue) {
        return false;
    }

    *outValue = treeFindMin(t->root)->data;
    return true;
}

bool treeMax(const Tree* t, Data* outValue) {
    if (!t || !t->root || !outValue) {
        return false;
    }

    *outValue = treeFindMax(t->root)->data;
    return true;
}

bool treeIsEmpty(const Tree* t) {
    return !t || t->size == 0;
}

int treeSize(const Tree* t) {
    return t ? t->size : 0;
}

void treeClear(Tree* t) {
    if (!t) {
        return;
    }

    treeNodeDestroy(t->root);
    t->root = NULL;
    t->size = 0;
}

void treePreOrder(const Tree* t) {
    if (!t) {
        return;
    }

    printf("前序遍历：");
    treePreOrderNode(t->root);
    printf("\n");
}

void treeInOrder(const Tree* t) {
    if (!t) {
        return;
    }

    printf("中序遍历：");
    treeInOrderNode(t->root);
    printf("\n");
}

void treePostOrder(const Tree* t) {
    if (!t) {
        return;
    }

    printf("后序遍历：");
    treePostOrderNode(t->root);
    printf("\n");
}

void treePrint(const Tree* t) {
    if (!t) {
        printf("NULL\n");
        return;
    }

    if (treeIsEmpty(t)) {
        printf("空树（size=0）\n");
        return;
    }

    printf("树结构（size=%d）：\n", t->size);
    treePrintNode(t->root, 0);
}

int treeHeight(const Tree* t) {
    return t ? treeNodeHeight(t->root) : 0;
}

int treeCountLeaves(const Tree* t) {
    return t ? treeNodeCountLeaves(t->root) : 0;
}

static void treeNodeDestroy(TreeNode* node) {
    if (!node) {
        return;
    }

    treeNodeDestroy(node->left);
    treeNodeDestroy(node->right);
    free(node);
}

static TreeNode* treeRemoveNode(TreeNode* node, Data value, bool* removed) {
    if (!node) {
        return NULL;
    }

    if (value < node->data) {
        node->left = treeRemoveNode(node->left, value, removed);
    } else if (value > node->data) {
        node->right = treeRemoveNode(node->right, value, removed);
    } else {
        *removed = true;

        if (!node->left) {
            TreeNode* rightChild = node->right;
            free(node);
            return rightChild;
        }
        if (!node->right) {
            TreeNode* leftChild = node->left;
            free(node);
            return leftChild;
        }

        // 双子节点用右子树的最小值接替，再删除接替节点。
        TreeNode* successor = treeFindMin(node->right);
        node->data = successor->data;
        node->right = treeRemoveNode(node->right, successor->data, removed);
    }
    return node;
}

static TreeNode* treeFindMin(TreeNode* node) {
    if (!node) {
        return NULL;
    }

    while (node->left) {
        node = node->left;
    }
    return node;
}

static TreeNode* treeFindMax(TreeNode* node) {
    if (!node) {
        return NULL;
    }

    while (node->right) {
        node = node->right;
    }
    return node;
}

static void treePreOrderNode(const TreeNode* node) {
    if (!node) {
        return;
    }

    printf("%d ", node->data);
    treePreOrderNode(node->left);
    treePreOrderNode(node->right);
}

static void treeInOrderNode(const TreeNode* node) {
    if (!node) {
        return;
    }

    treeInOrderNode(node->left);
    printf("%d ", node->data);
    treeInOrderNode(node->right);
}

static void treePostOrderNode(const TreeNode* node) {
    if (!node) {
        return;
    }

    treePostOrderNode(node->left);
    treePostOrderNode(node->right);
    printf("%d ", node->data);
}

static void treePrintNode(const TreeNode* node, int depth) {
    if (!node) {
        return;
    }

    treePrintNode(node->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%d\n", node->data);
    treePrintNode(node->left, depth + 1);
}

static int treeNodeHeight(const TreeNode* node) {
    if (!node) {
        return 0;
    }

    int leftHeight = treeNodeHeight(node->left);
    int rightHeight = treeNodeHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

static int treeNodeCountLeaves(const TreeNode* node) {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return 1;
    }

    return treeNodeCountLeaves(node->left) + treeNodeCountLeaves(node->right);
}
