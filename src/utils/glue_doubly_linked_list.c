#include "glue_doubly_linked_list.h"

#include <stddef.h>

void insert_node_before(GlueNode *base, GlueNode *node) {
    if (base == NULL || node == NULL) {
        return;
    }

    node->left = base->left;
    node->right = base;
    base->left = node;
    if (node->left != NULL) {
        node->left->right = node;
    }
}

void insert_glue_node(GlueDoublyLinkedList *list, GlueNode *node) {
    node->left = NULL;
    node->right = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        GlueNode *head = list->head;
        insert_node_before(head, node);
        list->head = node;
    }
}

void remove_glue_node(GlueDoublyLinkedList *list, GlueNode *node) {
    if (node == NULL || list->head == NULL) {
        return;
    }

    if (node->left != NULL) {
        node->left->right = node->right;
    } else {
        list->head = node->right;
    }

    if (node->right != NULL) {
        node->right->left = node->left;
    }

    node->left = NULL;
    node->right = NULL;
}

void init_glue_doubly_linked_list(GlueDoublyLinkedList *list, unsigned int offset) {
    list->head = NULL;
    list->offset = offset;
}
