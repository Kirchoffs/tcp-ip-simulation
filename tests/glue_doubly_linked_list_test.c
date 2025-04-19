#include "glue_doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AppData_ {
    char id[15];
    unsigned int ttl;
    char description[75];
    unsigned int user_id;
    GlueNode glue;
} AppData;

void print_app_data_details(GlueNode *glue) {
    AppData *app_data = (AppData *)((char *)glue - OFFSET(AppData, glue));
    printf("ID: %s\n", app_data->id);
    printf("TTL: %u\n", app_data->ttl);
    printf("Description: %s\n", app_data->description);
    printf("User ID: %u\n", app_data->user_id);
}

int main() {
    AppData *app_data_x = calloc(1, sizeof(AppData));
    strncpy(app_data_x->id, "app_x", strlen("app_x"));
    app_data_x->ttl = 15;
    strncpy(app_data_x->description, "This is app_x", strlen("This is app_x"));
    app_data_x->user_id = 1;
    GLUE_NODE_INIT((&app_data_x->glue));

    AppData *app_data_y = calloc(1, sizeof(AppData));
    strncpy(app_data_y->id, "app_y", strlen("app_y"));
    app_data_y->ttl = 25;
    strncpy(app_data_y->description, "This is app_y", strlen("This is app_y"));
    app_data_y->user_id = 2;
    GLUE_NODE_INIT((&app_data_y->glue));

    AppData *app_data_z = calloc(1, sizeof(AppData));
    strncpy(app_data_z->id, "app_z", strlen("app_z"));
    app_data_z->ttl = 35;
    strncpy(app_data_z->description, "This is app_z", strlen("This is app_z"));
    app_data_z->user_id = 3;
    GLUE_NODE_INIT((&app_data_z->glue));

    GlueDoublyLinkedList* list = malloc(sizeof(GlueDoublyLinkedList));
    init_glue_doubly_linked_list(list, OFFSET(AppData, glue));
    insert_glue_node(list, &app_data_x->glue);
    insert_glue_node(list, &app_data_y->glue);
    insert_glue_node(list, &app_data_z->glue);

    AppData *ptr = NULL;
    ITERATE_GLUE_DOUBLY_LINKED_LIST_BEGIN(list, AppData, ptr) {
        print_app_data_details(&ptr->glue);
    } ITERATE_GLUE_DOUBLY_LINKED_LIST_END();

    remove_glue_node(list, &app_data_z->glue);
    free(app_data_z);

    ITERATE_GLUE_DOUBLY_LINKED_LIST_BEGIN(list, AppData, ptr) {
        print_app_data_details(&ptr->glue);
    } ITERATE_GLUE_DOUBLY_LINKED_LIST_END();

    ITERATE_GLUE_DOUBLY_LINKED_LIST_BEGIN(list, AppData, ptr) {
        remove_glue_node(list, &ptr->glue);
        free(ptr);
    } ITERATE_GLUE_DOUBLY_LINKED_LIST_END();

    free(list);

    return 0;
}
