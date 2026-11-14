# C 语言二叉搜索树

[English](README.md)

[![C11](https://img.shields.io/badge/C-11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![GCC](https://img.shields.io/badge/GCC-supported-orange.svg)](https://gcc.gnu.org/)
[![Python](https://img.shields.io/badge/Python-3.9%2B-green.svg)](https://www.python.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

## 项目介绍

这个项目用于学习和演示二叉搜索树，也可以作为源码直接加入其他 C 项目。实现使用 C11，重点放在节点内存管理、三类节点删除、有序遍历和边界情况处理上。

它是一棵普通的二叉搜索树，不是 AVL 树或红黑树。重复值不会插入，树也不会自动旋转平衡。`Data` 当前定义为 `int`，可以在 `tree.h` 中按需修改。

主要功能：

- 创建、清空和销毁树。
- 插入和删除节点，维护节点数量。
- 查找节点，读取最小值和最大值。
- 前序、中序、后序遍历和树形打印。
- 查询树高、节点数和叶节点数。
- 通过独立测试程序检查常见操作和边界情况。

```mermaid
flowchart LR
    A["包含 tree.h"] --> B["将 tree.c 加入编译"]
    B --> C["创建空树"]
    C --> D["插入、查找、删除或遍历"]
    D --> E["清空后复用，或销毁树"]
```

## 依赖说明

- **C 编译器**：支持 C11，项目的开发和测试使用 GCC。
- **Python 3.9+**：只用于运行 `test_tree.py`，脚本不使用第三方 Python 包。
- **C 标准库**：库实现使用 `stdbool.h`、`stdio.h` 和 `stdlib.h`，测试另外使用 `assert.h`。

## 项目结构

所有文件都放在项目根目录，不需要额外建立源码或构建目录。

```text
.
├── tree.h           公共数据结构和函数声明
├── tree.c           二叉搜索树实现
├── demo.c           演示程序
├── test_tree.c      断言测试
├── test_tree.py     编译并运行测试和演示
├── README.md        英文主文档
├── README.zh-CN.md  中文说明
├── LICENSE          MIT 许可证
└── .gitignore       本地构建产物忽略规则
```

## 使用说明

### 1. 集成到自己的程序

在源码中包含 `tree.h`，编译时把 `tree.c` 一起加入即可。

```c
#include <stdio.h>
#include "tree.h"

int main(void) {
    Tree* tree = treeCreate();
    if (!tree) {
        return 1;
    }

    treeInsert(tree, 0);
    treeInsert(tree, -10);
    treeInsert(tree, 10);

    Data minValue;
    if (treeMin(tree, &minValue)) {
        printf("最小值：%d\n", minValue);
    }

    treeDestroy(tree);
    return 0;
}
```

假设这个文件名为 `your_program.c`，在本项目根目录执行：

```bash
gcc -std=c11 tree.c your_program.c -o your_program
```

如果把这些文件复制到了其他位置，按实际路径调整源文件名即可。使用时通过 API 操作树，不要直接修改 `root` 和 `size`，否则可能破坏树的结构或节点计数。

### 2. 编译并运行演示

Windows：

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic tree.c demo.c -o tree_demo.exe
.\tree_demo.exe
```

macOS 或 Linux：

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic tree.c demo.c -o tree_demo
./tree_demo
```

演示程序会依次展示插入、遍历、查找、删除、清空和销毁。

### 3. 运行自动测试

```bash
python test_tree.py
```

测试脚本使用以下选项分别编译测试程序和演示程序：

```text
-std=c11 -Wall -Wextra -Wpedantic -Werror
```

可执行文件生成在系统临时目录中，运行结束后自动删除。测试覆盖 `NULL`、空树、数值 0、重复插入、查找失败、叶节点删除、单子节点删除、双子节点删除、根节点删除以及清空后的复用。

### 4. 公共接口

| 函数 | 说明 |
| --- | --- |
| `Tree* treeCreate(void)` | 创建空树，内存不足时返回 `NULL`。 |
| `void treeDestroy(Tree* t)` | 销毁整棵树，允许传入 `NULL`。 |
| `bool treeInsert(Tree* t, Data value)` | 插入新值，重复或分配失败时返回 `false`。 |
| `bool treeRemove(Tree* t, Data value)` | 删除指定值，不存在时返回 `false`。 |
| `TreeNode* treeFind(const Tree* t, Data value)` | 查找节点，找不到时返回 `NULL`。 |
| `bool treeContains(const Tree* t, Data value)` | 判断指定值是否存在。 |
| `bool treeMin(const Tree* t, Data* outValue)` | 通过输出参数读取最小值。 |
| `bool treeMax(const Tree* t, Data* outValue)` | 通过输出参数读取最大值。 |
| `bool treeIsEmpty(const Tree* t)` | 判断是否为空树。 |
| `int treeSize(const Tree* t)` | 返回节点总数。 |
| `void treeClear(Tree* t)` | 清空节点，保留树对象。 |
| `void treePreOrder(const Tree* t)` | 前序遍历并打印。 |
| `void treeInOrder(const Tree* t)` | 中序遍历并打印，结果按升序排列。 |
| `void treePostOrder(const Tree* t)` | 后序遍历并打印。 |
| `void treePrint(const Tree* t)` | 以横向缩进形式打印树。 |
| `int treeHeight(const Tree* t)` | 返回树高，空树为 0，叶节点为 1。 |
| `int treeCountLeaves(const Tree* t)` | 返回叶节点数量。 |

`treeMin` 和 `treeMax` 只有返回 `true` 时，输出参数中的值才有效，因此空树不会和实际存储的数值 0 混淆。

### 5. 复杂度

| 操作 | 平均时间 | 最坏时间 | 额外空间 |
| --- | --- | --- | --- |
| 插入 | O(log n) | O(n) | O(1) |
| 删除 | O(log n) | O(n) | O(h) |
| 查找 | O(log n) | O(n) | O(1) |
| 遍历 | O(n) | O(n) | O(h) |
| 高度和叶节点统计 | O(n) | O(n) | O(h) |

其中 `n` 是节点数，`h` 是树高。插入和查找使用循环，删除、遍历和统计使用递归。树退化成链表时，树高为 `n`，递归操作也需要相应的调用栈空间。

## 贡献指南

1. Fork 仓库，并为自己的修改创建分支。
2. 保持代码符合 C11，不引入平台专属扩展。
3. 修改行为时补充对应断言，并运行 `python test_tree.py`。
4. 不要提交可执行文件、目标文件或缓存。
5. 提交 Pull Request 时说明修改原因和测试结果，也可以先通过 Issue 讨论。

## 联系作者

**谙弆悕博士（Ailan Anjuxi）**

- 邮箱：[anjuxi.ME@outlook.com](mailto:anjuxi.ME@outlook.com)
- SIP 电话：[sip:anjuxi@sip.linphone.org](sip:anjuxi@sip.linphone.org)

项目使用 [MIT 许可证](LICENSE)。
