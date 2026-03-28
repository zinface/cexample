# XOR Linked List (异或链表)

这是一个 **XOR 链表（XOR Linked List）** 的 C 语言实现，是一种特殊的链表数据结构。

## 源文件
- **文件**: `xor_list.h`
- **路径**: `ds/xor_list/xor_list.h`
- **语言**: C

## 核心概念

XOR 链表是一种内存优化的双向链表，它利用 XOR 运算的性质来存储前后节点的指针。在每个节点中只需要一个指针字段（`npx`），而不是传统双向链表的两个指针字段，从而节省 50% 的指针存储空间。

## 数据结构

```c
typedef struct xor_list_node {
    uintptr_t npx;  // XOR 后的前后指针
} xor_list_node_t;

typedef struct xor_list {
    xor_list_node_t *head;  // 链表头指针
    xor_list_node_t *tail;  // 链表尾指针
} xor_list_t;
```

## 核心函数

| 函数 | 功能 |
|------|------|
| `xor_node(a, b)` | XOR 运算：获取两个指针的异或结果 |
| `xor_list_next(curr, prev)` | 根据当前节点和前驱节点计算后继节点 |
| `xor_list_init(l)` | 初始化空链表 |
| `xor_list_empty(l)` | 检查链表是否为空 |
| `xor_list_append(l, n)` | 在链表末尾添加节点 |
| `xor_list_prepend(l, n)` | 在链表开头添加节点 |
| `xor_list_add_before(l, pos, prev, n)` | 在指定位置前插入节点 |
| `xor_list_add_after(l, pos, prev, n)` | 在指定位置后插入节点 |
| `xor_list_find(l, pred, arg, out_prev)` | 按条件搜索节点 |

## 遍历宏

- `xor_list_for_each(pos, prev, list)` - 正向遍历链表
- `xor_list_for_each_reverse(pos, next, list)` - 反向遍历链表
- `container_of(ptr, type, member)` - 从节点指针获取容器结构体指针

## 优势

✓ **内存节省**：每个节点只需一个指针字段，相比��向链表节省 50% 的指针空间  
✓ **可双向遍历**：既能正向遍历也能反向遍历  
✓ **高效操作**：O(1) 时间复杂度的插入和删除  

## 原理

XOR 链表的核心原理基于 XOR 运算的性质：
- `a ^ a = 0`
- `a ^ 0 = a`
- `a ^ b = b ^ a`（交换律）
- `(a ^ b) ^ a = b`（关键性质）

每个节点的 `npx` 字段存储的是前驱指针和后继指针的 XOR 结果：
```
node->npx = prev_node XOR next_node
```

通过已知前驱节点和 `npx` 值，可以恢复出后继节点：
```
next_node = node->npx XOR prev_node
```

### Python 实现示例

下面是一个 Python 例子来演示 XOR Linked List 的实现：

```python
class Node:
    def __init__(self, value):
        self.value = value
        self.both = 0  # This will store the XOR of previous and next node addresses

class XORLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.node_count = 0

    def add(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.both = id(self.tail)
            self.tail.both ^= id(new_node)
            self.tail = new_node
        self.node_count += 1

    def get(self, index):
        current = self.head
        prev_id = 0
        for _ in range(index):
            next_id = current.both ^ prev_id
            prev_id = id(current)
            current = next_node(next_id)
        return current.value

    def next_node(self, node_id):
        # Convert node_id to the actual node (this is pseudo code)
        return ...

# 使用示例:
# 1. 创建一个 XOR Linked List
# 2. 添加元素
# 3. 访问元素
```

## 使用示例

```c
xor_list_t list;
xor_list_init(&list);  // 初始化链表

// 添加节点
xor_list_append(&list, &node1);
xor_list_append(&list, &node2);

// 正向遍历
xor_list_node_t *pos, *prev;
xor_list_for_each(pos, prev, &list) {
    // 处理节点
}

// 反向遍历
xor_list_node_t *node, *next;
xor_list_for_each_reverse(node, next, &list) {
    // 处理节点
}
```

## 参考资源

- **灵感来自**: Tsoding 的 XOR Linked List 实现
- **相关链接**: [原始仓库](https://github.com/pan0xc/cexample/blob/master/ds/xor_list/xor_list.h)