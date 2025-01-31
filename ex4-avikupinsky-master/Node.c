#include <stdlib.h>
#include <stddef.h>
#include "Node.h"
#define SUCCESS 1
#define FAILURE 0
#define NEW_FAILED -1

/**
 * Allocates dynamically new Node element.
 * @param elem_copy_func - a function which copies (returns
 * a dynamically allocates copy) of a value.
 * @param elem_cmp_func - a function which compares two values
 * @param elem_free_func - a function which frees a dynamically allocated
 * value allocated by the copy function
 * @return pointer to dynamically allocated Node.
 * @if_fail return NULL.
 */
Node *node_alloc(NodeElemCpy elem_copy_func, NodeElemCmp elem_cmp_func, NodeElemFree elem_free_func){
    if (!elem_copy_func|| !elem_cmp_func || !elem_free_func){
        return NULL;
    }
    Node * new_node = calloc(1, sizeof(Node));
    if (new_node){
        new_node->elem_cmp_func = elem_cmp_func;
        new_node->elem_copy_func = elem_copy_func;
        new_node->elem_free_func = elem_free_func;
    }
    return new_node;
}

/**
 * Puts a new value to the data of the Node.
 * @param node a pointer to Node.
 * @param value the value to be put in the Node.
 * @return 1 if the adding has been done successfully, 0 otherwise.
 */
int set_node_data(Node *node, Value value){
    if (!node || !value || !node->elem_copy_func || !node->elem_free_func){
        return FAILURE;
    }
    if (node->data == NULL){
        node->data = node->elem_copy_func(value);
    } else{
        node->elem_free_func(&node->data);
        node->data = node->elem_copy_func(value);
    }
    return SUCCESS;
}

/**
 * Gets a value and checks if the value is in the Node.
 * @param Node a pointer to Node.
 * @param value the value to look for.
 * @return 1 if the value is in the Node, 0 if no such value in the Node.
 * Returns -1  if something went wrong during the check
 * You cannot assume anything about the input.
 */
int check_node(Node *Node, void *value){
    if (!Node || !value || !Node->data) {
        return NEW_FAILED;
    }
    if (Node->elem_cmp_func(Node->data,value)){
        return SUCCESS;
    } else{
        return FAILURE;
    }

}

/**
 * Deletes the data in the Node.
 * @param node Node a pointer to Node.
 */
void clear_node(Node *Node){
    if (!Node || !Node->data|| !Node->elem_free_func){
        return;
    }
    Node->elem_free_func((void **) Node);
}

/**
 * Gets the number of data values in the hashtable that would have been hashed
 * to this node
 * @param node The current node
 * @return the number of data in the hashtable that would have been hashed
 * to this node or -1 in case of illegal input;
 * You cannot assume anything about the input.
 */
int get_hash_count(Node *node){
    if (!node ){
        return NEW_FAILED;
    } else{
        return node->hashCount;
    }
}

/**
 * Frees a Node and the element the Node itself allocated.
 * @param p_node pointer to dynamically allocated pointer to Node.
 */
void node_free(Node **p_node){
    if (!p_node || !*p_node || !(*p_node)->elem_free_func) {
        return;
    }
    clear_node(*p_node);
    free(*p_node);
    *p_node = NULL;
}


