#include "simplified_glue_doubly_linked_list.h"

#include <stdlib.h>

void init_list_node(ListNode *node) {
    node->left = NULL;
    node->right = NULL;
}

void insert_after(ListNode *base_node, ListNode *new_node) {
    new_node->left = base_node;
    new_node->right = base_node->right;

    if (base_node->right != NULL) {
        base_node->right->left = new_node;
    }
    base_node->right = new_node;
}
