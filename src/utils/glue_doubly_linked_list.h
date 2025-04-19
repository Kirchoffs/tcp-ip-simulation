#ifndef GLUE_DOUBLY_LINKED_LIST_H
#define GLUE_DOUBLY_LINKED_LIST_H

#include <stddef.h>

#define OFFSET(struct_name, field_name) (size_t)&((struct_name *)0)->field_name

typedef struct GlueNode_ {
    struct GlueNode_ *left;
    struct GlueNode_ *right;
} GlueNode;

typedef struct GlueDoublyLinkedList_ {
    GlueNode *head;
    unsigned int offset;
} GlueDoublyLinkedList;

void insert_glue_node(GlueDoublyLinkedList *list, GlueNode *node);
void remove_glue_node(GlueDoublyLinkedList *list, GlueNode *node);
void init_glue_doubly_linked_list(GlueDoublyLinkedList *list, unsigned int offset);

#define ITERATE_GLUE_DOUBLY_LINKED_LIST_BEGIN(list, struct_type, ptr)     \
{                                                                         \
    GlueNode *_cur = NULL, *_next = NULL;                                 \
    for (_cur = (GlueNode *)(list)->head; _cur != NULL; _cur = _next) {   \
        ptr = (struct_type *)((char *)_cur - list->offset);               \
        _next = _cur->right;

#define ITERATE_GLUE_DOUBLY_LINKED_LIST_END()                             \
    }                                                                     \
}

#define GLUE_NODE_INIT(node) \
        node->left = NULL;   \
        node->right = NULL;

#endif
