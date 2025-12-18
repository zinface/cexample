#include "xor_list.h"

#include <stdio.h>

struct book {
    int id;
    char name[50];
    xor_list_node_t node;
};

int match_id(xor_list_node_t *n, void *arg)
{
    struct book *b = container_of(n, struct book, node);
    return b->id == *(int *)arg;
}

int main() {
    xor_list_t list;
    xor_list_init(&list);

    struct book a = { .id = 1, .name = "西游记" };
    struct book b = { .id = 2, .name = "红楼梦" };
    struct book c = { .id = 3, .name = "三国演义" };
    struct book d = { .id = 4, .name = "水浒传" };
    xor_list_append(&list, &a.node);
    xor_list_append(&list, &b.node);
    xor_list_append(&list, &c.node);
    xor_list_append(&list, &d.node);

    xor_list_node_t *pos, *prev, *next;
    printf("\n----for_each forward----\n");
    xor_list_for_each(pos, prev, &list) {
        struct book *it = container_of(pos, struct book, node);
        printf("[%d] 《%s》\n", it->id, it->name);
    }
    printf("\n----for_each reverse----\n");
    xor_list_for_each_reverse(pos, next, &list) {
        struct book *it = container_of(pos, struct book, node);
        printf("[%d] 《%s》\n", it->id, it->name);
    }

    struct book e = { 5, "聊斋志异" };
    struct book f = { 6, "老子" };
    int key = 3;
    pos = xor_list_find(&list, match_id, &key, &prev);
    if (pos) {
        xor_list_add_after(&list, pos, prev, &e.node);
        xor_list_add_after(&list, pos, prev, &f.node);
    }
    printf("\n----add_before_(id=%d)_after----\n", key);
    xor_list_for_each(pos, prev, &list) {
        struct book *it = container_of(pos, struct book, node);
        printf("[%d] 《%s》\n", it->id, it->name);
    }
    printf("\n----reverse add_before_(id=%d)_after----\n", key);
    xor_list_for_each_reverse(pos, next, &list) {
        struct book *it = container_of(pos, struct book, node);
        printf("[%d] 《%s》\n", it->id, it->name);
    }
    return 0;
}