#include "graph.h"

#include <stdlib.h>

int main() {
    Graph *graph = create_graph("Test Topology");
    
    Node *node_a = create_graph_node(graph, "Node A");
    Node *node_b = create_graph_node(graph, "Node B");
    Node *node_c = create_graph_node(graph, "Node C");

    insert_link_between_two_nodes(node_a, node_b, "eth1", "eth2", 1);
    insert_link_between_two_nodes(node_b, node_c, "eth3", "eth4", 2);
    insert_link_between_two_nodes(node_c, node_a, "eth5", "eth6", 3);

    dump_graph(graph);

    free(node_a);
    free(node_b);
    free(node_c);
    free(graph);

    return 0;
}
