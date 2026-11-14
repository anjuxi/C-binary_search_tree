# Binary Search Tree in C

[中文说明](README.zh-CN.md)

[![C11](https://img.shields.io/badge/C-11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![GCC](https://img.shields.io/badge/GCC-supported-orange.svg)](https://gcc.gnu.org/)
[![Python](https://img.shields.io/badge/Python-3.9%2B-green.svg)](https://www.python.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

## Project Overview

This project is a learning-oriented binary search tree implementation that can also be compiled directly into another C project. It uses C11 and focuses on node memory management, the three deletion cases, ordered traversal, and boundary handling.

This is an ordinary binary search tree, not an AVL or red-black tree. Duplicate values are rejected, and the tree does not rebalance itself. `Data` is currently defined as `int` in `tree.h`.

Features:

- Create, clear, and destroy trees.
- Insert and remove nodes while maintaining the node count.
- Find nodes and read minimum or maximum values.
- Pre-order, in-order, and post-order traversal, plus tree printing.
- Query the height, node count, and leaf count.
- Check common operations and edge cases with a separate test program.

```mermaid
flowchart LR
    A["Include tree.h"] --> B["Compile tree.c with your program"]
    B --> C["Create an empty tree"]
    C --> D["Insert, find, remove, or traverse"]
    D --> E["Clear and reuse, or destroy"]
```

## Dependencies

- **C compiler**: C11 support is required; GCC is used for development and testing.
- **Python 3.9+**: Only needed for `test_tree.py`; no third-party Python packages are used.
- **C standard library**: The library uses `stdbool.h`, `stdio.h`, and `stdlib.h`; the tests also use `assert.h`.

## Project Structure

All files live in the project root. No separate source or build directories are required.

```text
.
├── tree.h           Public types and function declarations
├── tree.c           Binary search tree implementation
├── demo.c           Demo program
├── test_tree.c      Assertion tests
├── test_tree.py     Compile and run the tests and demo
├── README.md        Main English documentation
├── README.zh-CN.md  Chinese documentation
├── LICENSE          MIT license
└── .gitignore       Local build artifact exclusions
```

## Usage

### 1. Integrate with your program

Include `tree.h` in your source and compile `tree.c` with your program.

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
        printf("Minimum: %d\n", minValue);
    }

    treeDestroy(tree);
    return 0;
}
```

If the file is named `your_program.c`, run this command from the project root:

```bash
gcc -std=c11 tree.c your_program.c -o your_program
```

Adjust the source paths if you copy the files elsewhere. Use the API instead of modifying `root` or `size` directly, since manual changes can break the tree structure or node count.

### 2. Build and run the demo

On Windows:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic tree.c demo.c -o tree_demo.exe
.\tree_demo.exe
```

On macOS or Linux:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic tree.c demo.c -o tree_demo
./tree_demo
```

The demo covers insertion, traversal, lookup, deletion, clearing, and destruction.

### 3. Run the tests

```bash
python test_tree.py
```

The script compiles the test and demo programs separately with:

```text
-std=c11 -Wall -Wextra -Wpedantic -Werror
```

Executables are created in the system temporary directory and removed afterward. Tests cover `NULL`, empty trees, stored zeroes, duplicate insertion, failed lookup, leaf removal, one-child removal, two-child removal, root removal, and reuse after clearing.

### 4. Public API

| Function | Description |
| --- | --- |
| `Tree* treeCreate(void)` | Create an empty tree; return `NULL` on allocation failure. |
| `void treeDestroy(Tree* t)` | Destroy a tree; `NULL` is accepted. |
| `bool treeInsert(Tree* t, Data value)` | Insert a new value; reject duplicates and allocation failures. |
| `bool treeRemove(Tree* t, Data value)` | Remove a value; return `false` when it is absent. |
| `TreeNode* treeFind(const Tree* t, Data value)` | Find a node or return `NULL`. |
| `bool treeContains(const Tree* t, Data value)` | Check whether a value exists. |
| `bool treeMin(const Tree* t, Data* outValue)` | Read the minimum through an output parameter. |
| `bool treeMax(const Tree* t, Data* outValue)` | Read the maximum through an output parameter. |
| `bool treeIsEmpty(const Tree* t)` | Check whether the tree is empty. |
| `int treeSize(const Tree* t)` | Return the node count. |
| `void treeClear(Tree* t)` | Remove all nodes but keep the tree object. |
| `void treePreOrder(const Tree* t)` | Print a pre-order traversal. |
| `void treeInOrder(const Tree* t)` | Print an in-order traversal in ascending order. |
| `void treePostOrder(const Tree* t)` | Print a post-order traversal. |
| `void treePrint(const Tree* t)` | Print the tree with horizontal indentation. |
| `int treeHeight(const Tree* t)` | Return the height; an empty tree is 0 and a leaf is 1. |
| `int treeCountLeaves(const Tree* t)` | Return the leaf count. |

The output parameter of `treeMin` or `treeMax` is valid only when the function returns `true`, so an empty tree is not confused with a stored value of 0.

### 5. Complexity

| Operation | Average time | Worst time | Extra space |
| --- | --- | --- | --- |
| Insert | O(log n) | O(n) | O(1) |
| Remove | O(log n) | O(n) | O(h) |
| Lookup | O(log n) | O(n) | O(1) |
| Traversal | O(n) | O(n) | O(h) |
| Height and leaf count | O(n) | O(n) | O(h) |

Here, `n` is the node count and `h` is the tree height. Insertion and lookup are iterative; removal, traversal, and statistics are recursive. A degenerate tree has height `n`, and recursive operations need the corresponding call-stack space.

## Contributing

1. Fork the repository and create a branch for your change.
2. Keep the code compatible with C11 and avoid platform-specific extensions.
3. Add assertions for behavior changes and run `python test_tree.py`.
4. Do not commit executables, object files, or caches.
5. Explain the reason for the change and the test result in your pull request. Opening an issue first is also welcome.

## Contact

**Ailan Anjuxi (谙弆悕博士)**

- Email: [anjuxi.ME@outlook.com](mailto:anjuxi.ME@outlook.com)
- SIP: [sip:anjuxi@sip.linphone.org](sip:anjuxi@sip.linphone.org)

Licensed under the [MIT License](LICENSE).
