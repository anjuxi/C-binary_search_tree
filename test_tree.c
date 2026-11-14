#include "tree.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    Tree* tree = treeCreate();
    Data value = -1;
    const Data values[] = {50, 30, 70, 20, 40, 60, 80};

    assert(tree != NULL);
    assert(treeIsEmpty(NULL));
    assert(treeSize(NULL) == 0);
    assert(treeHeight(NULL) == 0);
    assert(treeCountLeaves(NULL) == 0);
    assert(treeFind(NULL, 0) == NULL);
    assert(!treeContains(NULL, 0));
    assert(!treeInsert(NULL, 1));
    assert(!treeRemove(NULL, 1));
    assert(!treeMin(NULL, &value));
    assert(!treeMax(NULL, &value));
    treeClear(NULL);
    treeDestroy(NULL);

    assert(treeIsEmpty(tree));
    assert(treeSize(tree) == 0);
    assert(treeHeight(tree) == 0);
    assert(treeCountLeaves(tree) == 0);
    assert(!treeMin(tree, &value));
    assert(!treeMax(tree, &value));
    assert(!treeMin(tree, NULL));
    assert(!treeMax(tree, NULL));

    // 数据 0 也是有效值，不能拿它表示空树。
    assert(treeInsert(tree, 0));
    assert(!treeInsert(tree, 0));
    assert(treeSize(tree) == 1);
    assert(treeHeight(tree) == 1);
    assert(treeCountLeaves(tree) == 1);
    assert(treeMin(tree, &value) && value == 0);
    assert(treeMax(tree, &value) && value == 0);
    assert(treeFind(tree, 0) == tree->root);
    assert(treeRemove(tree, 0));
    assert(tree->root == NULL);
    assert(!treeRemove(tree, 0));
    assert(treeIsEmpty(tree));

    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        assert(treeInsert(tree, values[i]));
    }
    assert(!treeInsert(tree, 40));
    assert(treeSize(tree) == 7);
    assert(treeHeight(tree) == 3);
    assert(treeCountLeaves(tree) == 4);
    assert(treeContains(tree, 40));
    assert(!treeContains(tree, 100));
    assert(treeFind(tree, 40) != NULL && treeFind(tree, 40)->data == 40);
    assert(treeMin(tree, &value) && value == 20);
    assert(treeMax(tree, &value) && value == 80);

    // 覆盖不存在的值、叶节点和只有左孩子的节点。
    assert(!treeRemove(tree, 100));
    assert(treeSize(tree) == 7);
    assert(treeRemove(tree, 20));
    assert(!treeContains(tree, 20));
    assert(treeSize(tree) == 6);
    assert(treeInsert(tree, 25));
    assert(treeRemove(tree, 30));
    assert(!treeContains(tree, 30));
    assert(treeContains(tree, 25) && treeContains(tree, 40));
    assert(treeSize(tree) == 6);

    // 根节点有两个孩子时，由右子树的最小值接替。
    assert(treeRemove(tree, 50));
    assert(tree->root != NULL && tree->root->data == 60);
    assert(!treeContains(tree, 50));
    assert(treeSize(tree) == 5);

    treeClear(tree);
    assert(treeIsEmpty(tree));
    assert(tree->root == NULL);
    assert(treeHeight(tree) == 0);
    assert(treeCountLeaves(tree) == 0);

    // 再检查只有右孩子的节点和根节点删除。
    assert(treeInsert(tree, 50));
    assert(treeInsert(tree, 30));
    assert(treeInsert(tree, 70));
    assert(treeInsert(tree, 80));
    assert(treeRemove(tree, 70));
    assert(!treeContains(tree, 70));
    assert(treeContains(tree, 80));
    assert(treeSize(tree) == 3);
    assert(treeRemove(tree, 50));
    assert(tree->root != NULL && tree->root->data == 80);
    assert(treeSize(tree) == 2);

    treeClear(tree);
    assert(treeInsert(tree, 100));
    assert(treeInsert(tree, 50));
    assert(treeInsert(tree, 150));
    assert(treeSize(tree) == 3);
    treeClear(tree);
    treeDestroy(tree);

    printf("所有自动测试均已通过。\n");
    return 0;
}
