#include <stdlib.h>
#include <stddef.h>
#include "Node.h"
#include "HashSet.h"
#define HASH_SET_INITIAL_CAP 16
#define HASH_SET_GROWTH_FACTOR 2
#define DIVIDING_OR_MUL 2
#define HASH_SET_MIN_LOAD_FACTOR 0.25
#define HASH_SET_MAX_LOAD_FACTOR 0.75
#define SUCCESS 1
#define FAILURE 0
#define NEW_FAILED -1

void changing_the_hash_set(HashSet *hash_set, double num);

/**
 *in this function we calculating the value of the hash we have got.
 * @param num
 * @param hash
 * @param capacity
 * @return the number were we should put it in the hash_set
 */
size_t calculating_the_hash(size_t num, size_t hash, unsigned int capacity) {
    return ((hash + (((num +(num*num))/DIVIDING_OR_MUL))) & (capacity - 1));
}


/**
 * in this function we creat a new Noodlist we the current capacity
 * @param hash_set
 */
void making_new_hash_set(HashSet *hash_set) {
    Node ** tmp = calloc((hash_set->capacity),sizeof(*hash_set));
    for (size_t i = 0; i < hash_set->capacity ; ++i) {
        tmp[i] = node_alloc(hash_set->value_cpy,hash_set->value_cmp,hash_set->value_free);
        }
    hash_set->NodesList = tmp;
}

/**
 * in this function we delete a value in the hash_set
 * @param hash_set
 * @param value
 */
void deleting_the_value(HashSet *hash_set, Value value) {
    size_t new_hash = hash_set->hash_func(value), check, last;
    if (hash_set->size*DIVIDING_OR_MUL < hash_set->capacity){
        last = (hash_set->capacity/DIVIDING_OR_MUL);
    } else{
        last = hash_set->size;
    }
    for (size_t i = 0; i < last; ++i) {
        check = calculating_the_hash(i, new_hash, hash_set->capacity);
        if(i == 0){
            hash_set->NodesList[check]->hashCount--;
        }
        if (hash_set->NodesList[check]->data) {
            if (hash_set->value_cmp(hash_set->NodesList[check]->data, value)) {
                clear_node((Node *) &hash_set->NodesList[check]->data);
                break;
            }
        }
    }
    hash_set->size--;
}

/**
 *in this function we find the place tp put the value in the hash_set
 * @param hash_set
 * @param value
 */
void finding_place_for_value_in_hashset(HashSet *hash_set, Value value) {
    size_t num = 0, final_count = hash_set->capacity;
    size_t new_hash = hash_set->hash_func(value), check;
    while (final_count != 0) {
        check = calculating_the_hash(num, new_hash, hash_set->capacity);
        if (num == 0){
            hash_set->NodesList[check]->hashCount++;
        }
        if (hash_set_at(hash_set,check) == NULL){
            set_node_data(hash_set->NodesList[check], value);
            break;
        } else {
            num++;
            final_count--;
        }
    }
}

/**
 * in this function we save all the values that are in the hash_set
 * @param hash_set
 * @return a pinter to a list pf values
 */
Value saving_the_value_in_nodelist(HashSet *hash_set) {
    Value * saving_value = calloc(hash_set->size, sizeof(Value));
    unsigned int another_num = 0;
    for (unsigned int i = 0; i < hash_set->capacity ; ++i) {
        Value new_val = hash_set_at(hash_set, i);
        if (new_val ) {
            new_val= hash_set->value_cpy(new_val);
            saving_value[another_num] = new_val;
            another_num++;
        }
    }
    return saving_value;
}

/**
 * Allocates dynamically new hash set.
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL.
 */
HashSet *hash_set_alloc(
        HashFunc hash_func, HashSetValueCpy value_cpy,
        HashSetValueCmp value_cmp, HashSetValueFree value_free){
    if (!hash_func|| !value_cmp|| !value_cpy || !value_free){
        return NULL;
    }
    HashSet * new_hashset = calloc(1,sizeof(HashSet));
    if (new_hashset){
        new_hashset->capacity = HASH_SET_INITIAL_CAP;
        Node ** new_nodes_list = calloc((HASH_SET_INITIAL_CAP+1),sizeof(*new_hashset));
        new_hashset->NodesList = new_nodes_list;
        for (size_t i = 0; i < new_hashset->capacity; ++i) {
            new_hashset->NodesList[i] = node_alloc(value_cpy,value_cmp,value_free);
        }
        new_hashset->hash_func = hash_func;
        new_hashset->value_cpy = value_cpy;
        new_hashset->value_cmp = value_cmp;
        new_hashset->value_free = value_free;
    }
    return new_hashset;
}

/**
 * Inserts a new Value to the hash set.
 * The function inserts *new*, *copied*, *dynamically allocated* Value,
 * @param hash_set the hash set where we want to insert the new element
 * @param value a Value we would like to add to the hashset
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hash_set_insert(HashSet *hash_set, Value value) {
    if (!hash_set || !value || hash_set_contains_value(hash_set,value)
    || !hash_set->hash_func || !hash_set->value_cmp || !hash_set->value_free
    || !hash_set->value_cpy) {
        return FAILURE;
    }
    finding_place_for_value_in_hashset(hash_set,value);
    hash_set->size++;
    if (hash_set_get_load_factor(hash_set) >= HASH_SET_MAX_LOAD_FACTOR) {
        changing_the_hash_set(hash_set, HASH_SET_GROWTH_FACTOR);
    }
    return SUCCESS;
}

/**
// * in this function we chang the capacity of the hash_set
// * @param hash_set
// * @param num
// */
void changing_the_hash_set(HashSet *hash_set, double num) {
    Value * saving_value = saving_the_value_in_nodelist(hash_set);
    if(!saving_value){
        return;
    }
    for (unsigned int i = 0; i < hash_set->capacity ; ++i) {
        node_free(&hash_set->NodesList[i]);
    }
    free(hash_set->NodesList);
    hash_set->capacity = (hash_set->capacity * num);
    making_new_hash_set(hash_set);
    for (unsigned int i = 0; i < hash_set->size; ++i) {
        finding_place_for_value_in_hashset(hash_set, saving_value[i]);
        hash_set->value_free(&saving_value[i]);
        saving_value[i] = NULL;
    }
    free(saving_value);
    saving_value = NULL;
}

/**
 * The function checks if the given value exists in the hash set.
 * @param hash_set a hash set.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash set, 0 otherwise.
 */
int hash_set_contains_value(HashSet *hash_set, Value value){
    if (!hash_set || !value || !hash_set->hash_func){
        return FAILURE;
    }
    size_t new_hash = hash_set->hash_func(value),check, last;
    if (hash_set->size*DIVIDING_OR_MUL < hash_set->capacity){
        last = (hash_set->capacity/DIVIDING_OR_MUL);
    } else{
        last = hash_set->size;
    }
    for (size_t i = 0; i <last ; ++i) {
        check = calculating_the_hash(i, new_hash, hash_set->capacity);
        if (i == 0 && hash_set->NodesList[check]->hashCount == 0){
            return FAILURE;
        }
        if (hash_set->NodesList[check]->data) {
            if (hash_set->value_cmp(hash_set->NodesList[check]->data, value)) {
                return SUCCESS;
            }
        }
    }
    return FAILURE;
}

/**
 * The function erases a Value.
 * @param hash_set a hash set.
 * @param value the value to be erased from the hashtable
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int hash_set_erase(HashSet *hash_set, Value value) {
    if (!hash_set || !value || !hash_set_contains_value(hash_set, value)) {
        return FAILURE;
    }
    deleting_the_value(hash_set,value);
    if (hash_set_get_load_factor(hash_set) <= HASH_SET_MIN_LOAD_FACTOR) {
        double device = (1/ (double) HASH_SET_GROWTH_FACTOR);
        changing_the_hash_set(hash_set,device);
    }
    if( hash_set->size == 0 && hash_set->capacity == 1){
        node_free(&hash_set->NodesList[2]);
        hash_set->capacity =1;
    }
    return SUCCESS;
}

/**
 * This function returns the load factor of the hash set.
 * @param hash_set a hash set.
 * @return the hash set's load factor, -1 if the function failed.
 */
double hash_set_get_load_factor(HashSet *hash_set){
    if (!hash_set || hash_set->capacity==0 ){
        return NEW_FAILED;
    }
    return (double) (hash_set->size / (double)hash_set->capacity);
}

/**
 * This function deletes all the values in the hash set.
 * @param hash_set a hash set to be cleared.
 */
void hash_set_clear(HashSet *hash_set){
    if (!hash_set){
        return;
    }
    for (unsigned int i = 0; i < hash_set->capacity; ++i) {
        if((hash_set->NodesList[i])){
            hash_set->value_free((void **) &hash_set->NodesList[i]->data);
            hash_set->NodesList[i]->hashCount = 0;
        }
    }
    hash_set->size = 0;
}

/**
 * This function gets the element in the hashset hashed to the indexed value
 * @param hash_set the hashset
 * @param value the index of the node in the hashtable that we would like to have its value
 * @return the element in the hashset hashed to the indexed value
 * NULL in case of an error or an empty node or an unexpected value
 */
Value hash_set_at(HashSet *hash_set, int value){
    if (!hash_set || !hash_set->NodesList || value < 0 || !hash_set->NodesList[value]){
        return NULL;
    }
    return hash_set->NodesList[value]->data;
}

/**
 * Frees the hash set and all its elements.
 * @param p_hash_set pointer to pointer to a hash_set.
 */
void hash_set_free(HashSet **p_hash_set) {
    if (!p_hash_set || !*p_hash_set){
        return;
    }
    for (unsigned int i = 0; i < (*p_hash_set)->capacity; ++i) {
        node_free(&(*p_hash_set)->NodesList[i]);
        (*p_hash_set)->NodesList[i] = NULL;
    }
    free((*p_hash_set)->NodesList);
    (*p_hash_set)->NodesList = NULL;
    free(*p_hash_set);
    *p_hash_set = NULL;
}
