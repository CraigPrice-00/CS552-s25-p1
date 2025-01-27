/**Update this file with the starter code**/
#include "lab.h"

node_t* makeSentinel() {
    node_t* sentinel = malloc(sizeof(node_t));
    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    return sentinel;
}

list_t *list_init(void (*destroy_data)(void *),
int (*compare_to)(const void *, const void *)) {
    list_t* newList = malloc(sizeof(list_t));
    newList->size = 0;
    newList->destroy_data = destroy_data;
    newList->compare_to = compare_to;
    newList->head = makeSentinel();
    return newList;
}

void list_destroy(list_t **list) {
    node_t* currentNode = (*list)->head->next;
    while ((*list)->compare_to(currentNode,(*list)->head)) {
        node_t* temp = currentNode->next;
        (*list)->destroy_data(currentNode->data);
        free(currentNode);
        currentNode = temp;
    }
    free((*list)->head);
    free(*list);
    *list = NULL;
}

list_t *list_add(list_t *list, void *data) {
    node_t* newNode = malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = list->head->next;
    newNode->prev = list->head;
    list->head->next = newNode;
    newNode->next->prev = newNode;
    list->size++;
    return list;
}

void* list_remove_index(list_t *list, size_t index) {
    if (index >= list->size) {
        return NULL;
    }
    else {
        node_t* currentNode = list->head->next;
        for (size_t i = 0; i < index; i++) {
            currentNode = currentNode->next;
        }
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;
        list->size = list->size - 1;
        void* returnData = currentNode->data;
        free(currentNode);
        return returnData;
    }
}

int list_indexof(list_t *list, void *data) {
    node_t* currentNode = list->head->next;
    int currentIndex = 0;
    while (list->compare_to(currentNode, list->head)) {
        if (!list->compare_to(currentNode->data, data)) {
            return currentIndex;
        }
        else {
            currentNode = currentNode->next;
            currentIndex++;
        }
    }
    return -1;
}