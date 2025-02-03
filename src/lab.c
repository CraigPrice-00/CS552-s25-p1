/**Update this file with the starter code**/
#include "lab.h"

//Code Review: I added a comment to this function and memory safety on malloc
/* makeSentinel: this function takes no arguments and returns a node struct
   to use as the sentinel node. 
*/
node_t* makeSentinel() {
    node_t* sentinel = malloc(sizeof(node_t));
    if (!sentinel) { return NULL; }

    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    return sentinel;
}

//Code Review: I added a comment to this function and memory safety on malloc
/* list_init: this function initializes the list and returns it as a list_t struct
   parameters:
   void (*destroy_data)(void *): a function pointer to the destroy_data function
   int (*compare_to)(const void *, const void *): a function pointer to the compare_to function
*/
list_t *list_init(void (*destroy_data)(void *),
int (*compare_to)(const void *, const void *)) {
    list_t* newList = malloc(sizeof(list_t));
    if (!newList) { return NULL; }

    newList->size = 0;
    newList->destroy_data = destroy_data;
    newList->compare_to = compare_to;

    newList->head = makeSentinel();
    if (!newList->head) { return NULL; }

    return newList;
}

//Code Review: I added a comment to this function and memory safety check on the list
/* list_destroy: this function destroys the list and all nodes
   parameters:
   list_t ** list: a pointer to the list to be destroyed
*/
void list_destroy(list_t **list) {
    if (!*list || !list || !(*list)->head) { return; }

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

//Code Review: I added a comment to this function and memory safety on malloc
/* list_add: this function adds some data to a list
   parameters:
   list_t *list: a pointer to the list to add to
   void *data: the data to add
*/
list_t *list_add(list_t *list, void *data) {
    node_t* newNode = malloc(sizeof(node_t));
    if (!newNode) { return NULL; }

    newNode->data = data;
    newNode->next = list->head->next;
    newNode->prev = list->head;
    list->head->next = newNode;
    newNode->next->prev = newNode;
    list->size++;
    return list;
}

//Code Review: I added a comment to this function
/* list_remove_index: this function removes the node at a specified index and returns the data
   parameters:
   list_t *list: a pointer to the list to remove from
   size_t index: the index to remove from the list
*/
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

//Code Review: I added a comment to this function
/* list_indexof: this function finds the first occurrence of a specified data and returns the index
   parameters:
   list_t *list: a pointer to the list to check
   void *data: the data to find the index of
*/
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