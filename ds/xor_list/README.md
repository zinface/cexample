原理

XOR Linked List 是一种链表结构，利用异或运算存储指针，从而节省内存空间。在这种���构中，每个节点只存储一个指向前一个节点和后一个节点的异或值。通过异或操作，可以在遍历链表时有效地获取前向和后向节点。

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