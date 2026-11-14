#include "tree.h"

#include <stdio.h>

int main(void) {
    Tree* tree = treeCreate();
    Data value;

    if (!tree) {
        fprintf(stderr, "创建树失败，内存不足。\n");
        return 1;
    }

    printf("二叉搜索树演示\n");
    printf("创建空树：\n");
    treePrint(tree);

    printf("插入 50、30、70、20、40、60、80：\n");
    treeInsert(tree, 50);
    treeInsert(tree, 30);
    treeInsert(tree, 70);
    treeInsert(tree, 20);
    treeInsert(tree, 40);
    treeInsert(tree, 60);
    treeInsert(tree, 80);
    treePrint(tree);

    treePreOrder(tree);
    treeInOrder(tree);
    treePostOrder(tree);
    printf("是否包含 40：%s\n", treeContains(tree, 40) ? "是" : "否");
    printf("是否包含 100：%s\n", treeContains(tree, 100) ? "是" : "否");
    if (treeMin(tree, &value)) {
        printf("最小值：%d\n", value);
    }
    if (treeMax(tree, &value)) {
        printf("最大值：%d\n", value);
    }
    printf("树高度：%d\n", treeHeight(tree));
    printf("叶子节点数：%d\n", treeCountLeaves(tree));

    printf("\n删除叶节点 20：\n");
    treeRemove(tree, 20);
    treeInOrder(tree);

    printf("插入 25，再删除只有一个孩子的节点 30：\n");
    treeInsert(tree, 25);
    treeRemove(tree, 30);
    treeInOrder(tree);

    printf("删除有两个孩子的根节点 50：\n");
    treeRemove(tree, 50);
    treePrint(tree);
    treeInOrder(tree);

    printf("\n清空后重新插入 100、50、150：\n");
    treeClear(tree);
    treeInsert(tree, 100);
    treeInsert(tree, 50);
    treeInsert(tree, 150);
    treePrint(tree);

    treeDestroy(tree);
    printf("树已销毁。\n");
    return 0;
}
