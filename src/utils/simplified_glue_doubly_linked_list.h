#ifndef SIMPLIFIED_GLUE_DOUBLY_LINKED_LIST_H
#define SIMPLIFIED_GLUE_DOUBLY_LINKED_LIST_H

#include <stddef.h>

typedef struct ListNode_ {
    struct ListNode_ *left;
    struct ListNode_ *right;
} ListNode;

void init_list_node(ListNode *node);
void insert_after(ListNode *base_node, ListNode *new_node);

#define OFFSET(struct_name, field_name) (size_t)&((struct_name *)0)->field_name

#define BASE(list_node) ((list_node)->right)

#define ITERATE_LIST_NODE_BEGIN(start_node, curr_node)  \
{                                                       \
    ListNode *_next_node = NULL;                        \
    curr_node = BASE(start_node);                       \
    for (; curr_node != NULL; curr_node = _next_node) { \
        _next_node = curr_node->right;

#define ITERATE_LIST_NODE_END(start_node, curr_node)    \
    }                                                   \
}

#endif
