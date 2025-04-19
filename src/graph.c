#include "graph.h"
#include "indented_print.h"

#include <stdlib.h>
#include <string.h>

Graph *create_graph(char *topology_name) {
    Graph *graph = calloc(1, sizeof(Graph));
    strncpy(graph->topology_name, topology_name, TOPOLOGY_NAME_LENGTH);
    graph->topology_name[TOPOLOGY_NAME_LENGTH - 1] = '\0';

    init_list_node(&graph->node_list);
    return graph;
}

Node *create_graph_node(Graph *graph, char *node_name) {
    Node *node = calloc(1, sizeof(Node));
    strncpy(node->node_name, node_name, NODE_NAME_LENGTH);
    node->node_name[NODE_NAME_LENGTH - 1] = '\0';

    init_list_node(&node->graph_glue);
    insert_after(&graph->node_list, &node->graph_glue);
    return node;
}

void insert_link_between_two_nodes(Node *node_x, Node *node_y, char *from_if_name, char *to_if_name, unsigned int cost) {
    Link *link = calloc(1, sizeof(Link));

    strncpy(link->if_x.if_name, from_if_name, INTERFACE_NAME_LENGTH);
    link->if_x.if_name[INTERFACE_NAME_LENGTH - 1] = '\0';
    strncpy(link->if_y.if_name, to_if_name, INTERFACE_NAME_LENGTH);
    link->if_y.if_name[INTERFACE_NAME_LENGTH - 1] = '\0';

    link->if_x.link = link;
    link->if_y.link = link;
    
    link->if_x.node = node_x;
    link->if_y.node = node_y;

    link->cost = cost;

    int empty_interface_slot = -1;

    empty_interface_slot = get_node_interfaces_available_slots(node_x);
    node_x->interfaces[empty_interface_slot] = &link->if_x;

    empty_interface_slot = get_node_interfaces_available_slots(node_y);
    node_y->interfaces[empty_interface_slot] = &link->if_y;
}

Node *get_neighbor_node(Interface *interface) {
    Link *link = interface->link;
    if (link->if_x.node == interface->node) {
        return link->if_y.node;
    } else {
        return link->if_x.node;
    }
}

void dump_interface_with_indent(Interface *interface, int indent) {
    Node *neighbor_node = get_neighbor_node(interface);

    indented_printf(indent, "Interface Name: %s\n", interface->if_name);
    indented_printf(indent + 2, "Connected Node: %s\n", interface->node->node_name);
    indented_printf(indent + 2, "Neighbor Node: %s\n", neighbor_node->node_name);
    indented_printf(indent + 2, "Link Cost: %u\n", interface->link->cost);
}

void dump_node_with_indent(Node *node, int indent) {
    indented_printf(indent, "Node Name: %s\n", node->node_name);
    for (int i = 0; i < MAX_INTERFACES_PER_NODE; i++) {
        if (node->interfaces[i] != NULL) {
            dump_interface_with_indent(node->interfaces[i], indent + 2);
        }
    }
}

void dump_graph_with_indent(Graph *graph, int indent) {
    Node *node = NULL;
    ListNode *curr = NULL;

    indented_printf(indent, "Topology Name: %s\n", graph->topology_name);
    ITERATE_LIST_NODE_BEGIN(&graph->node_list, curr) {
        node = (Node *)((char *)curr - OFFSET(Node, graph_glue));
        dump_node_with_indent(node, indent + 2);
    } ITERATE_LIST_NODE_END(&graph->node_list, curr);
}

void dump_graph(Graph *graph) {
    dump_graph_with_indent(graph, 0);
}
