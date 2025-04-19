#ifndef GRAPH_H
#define GRAPH_H

#include "simplified_glue_doubly_linked_list.h"

#include <stddef.h>

#define INTERFACE_NAME_LENGTH 16
#define NODE_NAME_LENGTH 16
#define TOPOLOGY_NAME_LENGTH 16
#define MAX_INTERFACES_PER_NODE 8

typedef struct Node_ Node;
typedef struct Link_ Link;

typedef struct Interface_ {
    char if_name[INTERFACE_NAME_LENGTH];
    Node *node;
    Link *link;
} Interface;

struct Link_ {
    Interface if_x;
    Interface if_y;
    unsigned int cost;   
};

struct Node_ {
    char node_name[NODE_NAME_LENGTH];
    Interface *interfaces[MAX_INTERFACES_PER_NODE];
    ListNode graph_glue;
};

typedef struct Graph_ {
    char topology_name[TOPOLOGY_NAME_LENGTH];
    ListNode node_list;
} Graph;

Graph *create_graph(char *topology_name);
Node *create_graph_node(Graph *graph, char *node_name);
void insert_link_between_two_nodes(Node *node_x, Node *node_y, char *from_if_name, char *to_if_name, unsigned int cost);

static inline int get_node_interfaces_available_slots(Node *node) {
    int i;
    for (i = 0; i < MAX_INTERFACES_PER_NODE; i++) {
        if (node->interfaces[i] == NULL) {
            return i;
        }
    }
    return -1;
}

void dump_graph(Graph *graph);

#endif
