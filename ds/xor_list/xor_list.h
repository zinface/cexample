#ifndef _XOR_LIST_H
#define _XOR_LIST_H

#include <stdint.h>
#include <stddef.h>

// XOR Linked List Implementation
// Inspired by Tsoding

typedef struct xor_list_node {
    uintptr_t npx;
} xor_list_node_t;

typedef struct xor_list {
    xor_list_node_t *head;
    xor_list_node_t *tail;
} xor_list_t;

static inline xor_list_node_t *
xor_node(xor_list_node_t *a, xor_list_node_t *b)
{
    return (xor_list_node_t *)((uintptr_t)a ^ (uintptr_t)b);
}

static inline xor_list_node_t *
xor_list_next(xor_list_node_t *curr, xor_list_node_t *prev)
{
    return xor_node((xor_list_node_t *)curr->npx, prev);
}

static inline void
xor_list_init(xor_list_t *l)
{
    l->head = NULL;
    l->tail = NULL;
}

static inline int
xor_list_empty(const xor_list_t *l)
{
    return l->head == NULL;
}

static inline void
xor_list_node_init(xor_list_node_t *n)
{
    n->npx = 0;
}

static inline void
xor_list_append(xor_list_t *l, xor_list_node_t *n)
{
    xor_list_node_init(n);
    n->npx = (uintptr_t)l->tail;
    if (l->tail) {
        l->tail->npx ^= (uintptr_t)n;
    } else {
        l->head = n;
    }
    l->tail = n;
}

static inline void
xor_list_prepend(xor_list_t *l, xor_list_node_t *n)
{
    xor_list_node_init(n);
    n->npx = (uintptr_t)l->head;
    if (l->head) {
        l->head->npx ^= (uintptr_t)n;
    } else {
        l->tail = n;
    }
    l->head = n;
}

static inline void
xor_list_add_before(xor_list_t *l, xor_list_node_t *pos, xor_list_node_t *prev, xor_list_node_t *n)
{
    xor_list_node_t *next;
    next = xor_list_next(pos, prev);
    xor_list_node_init(n);
    n->npx = (uintptr_t)prev ^ (uintptr_t)pos;
    prev->npx ^= (uintptr_t)pos ^ (uintptr_t)n;
    pos->npx ^= (uintptr_t)prev ^ (uintptr_t)n;
}

static inline void
xor_list_add_after(xor_list_t *l, xor_list_node_t *pos, xor_list_node_t *prev, xor_list_node_t *n)
{
    xor_list_node_t *next;
    next = xor_list_next(pos, prev);
    xor_list_node_init(n);
    n->npx = (uintptr_t)pos ^ (uintptr_t)next;
    pos->npx ^= (uintptr_t)next ^ (uintptr_t)n;
    if (next) {
        next->npx ^= (uintptr_t)pos ^ (uintptr_t)n;
    } else {
        l->tail = n;
    }
}

static inline xor_list_node_t *
xor_list_find(xor_list_t *l, int (*pred)(xor_list_node_t *n, void *arg), void *arg, xor_list_node_t **out_prev)
{
    xor_list_node_t *curr = l->head;
    xor_list_node_t *prev = NULL;
    while (curr) {
        if (pred(curr, arg)) {
            if (out_prev)
                *out_prev = prev;
            return curr;
        }
        xor_list_node_t *next = xor_list_next(curr, prev);
        prev = curr;
        curr = next;
    }
    return NULL;
}

#define xor_list_for_each(pos, prev, list)                  \
    for ((prev) = NULL, (pos) = (list)->head;               \
         (pos) != NULL;                                     \
         ({                                                 \
             xor_list_node_t *next =                        \
                 xor_list_next((pos), (prev));              \
             (prev) = (pos);                                \
             (pos) = next;                                  \
         }))

#define xor_list_for_each_reverse(pos, next, list)          \
    for ((next) = NULL, (pos) = (list)->tail;               \
         (pos) != NULL;                                     \
         ({                                                 \
             xor_list_node_t *prev =                        \
                 xor_list_next((pos), (next));              \
             (next) = (pos);                                \
             (pos) = prev;                                  \
         }))

#define container_of(ptr, type, member) ({                  \
    const typeof(((type *)0)->member) *__mptr = (ptr);      \
    (type *)((char *)__mptr - offsetof(type, member));      \
})

#endif /* _XOR_LIST_H */