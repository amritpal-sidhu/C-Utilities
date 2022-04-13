#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl_tree.h"


/**
 * Private function declarations
 */
static int height(avl_node_s *node);
static unsigned max_height(avl_node_s *node);
static int balance_factor(avl_node_s *node);
static avl_node_s *left_rotate(avl_node_s *pivot);
static avl_node_s *right_rotate(avl_node_s *pivot);
static avl_node_s *recursive_insert(avl_s *avl, avl_node_s *node, avl_node_s *new_node);
static avl_node_s *avl_tree__delete_helper(avl_s *avl, avl_node_s *node, const void *obj);
static avl_node_s *avl_tree__min_helper(avl_node_s *node);
static avl_node_s *avl_tree__max_helper(avl_node_s *node);
static avl_node_s *avl_tree__find_helper(avl_s *avl, avl_node_s *node, const void *obj);


/**
 * Public function definitions
 */
int avl_tree__init(avl_s *avl, const unsigned int element_size, compare_function_t compare_function)
{
    int valid = avl && !avl->size && element_size && compare_function;

    if (valid) {

        avl->root = NULL;
        avl->element_size = element_size;
        avl->compare_function = compare_function;
        avl->size = 0;
    }

    return valid;
}

int avl_tree__insert(avl_s *avl, const void *obj)
{   
    int valid = avl && avl->element_size && avl->compare_function && obj;

    if (valid) {

        avl_node_s *new_node = malloc(sizeof(avl_node_s));

        new_node->obj = malloc(avl->element_size);
        memcpy(new_node->obj, obj, avl->element_size);
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 0;
        avl->root = recursive_insert(avl, avl->root, new_node);
        avl->size += 1;
    }
    

    return valid;
}

int avl_tree__delete(avl_s *avl, const void *obj)
{
    int valid = avl && avl->root && avl->compare_function && obj;

    if (valid)
        avl->root = avl_tree__delete_helper(avl, avl->root, obj);

    return valid;
}

int avl_tree__min(avl_s *avl, avl_node_s *min)
{
    int valid = avl && avl->root && avl->compare_function && min;

    if (valid)
        min = avl_tree__min_helper(avl->root);

    return valid;
}

int avl_tree__max(avl_s *avl, avl_node_s *max)
{
    int valid = avl && avl->root && avl->compare_function && max;

    if (valid)
        max = avl_tree__max_helper(avl->root);

    return valid;
}

int avl_tree__find(avl_s *avl, const void *obj, avl_node_s *node)
{
    int valid = avl && avl->compare_function && obj && node;

    if (valid)
        node = avl_tree__find_helper(avl, avl->root, obj);

    return valid;
}


/**
 * Private function definitions
 */
static int height(avl_node_s *node)
{
    int height = 0;
    if (node) height = node->height;
    return height;
}

static unsigned max_height(avl_node_s *node)
{
    int max_height = 0;

    if (node) {
        const unsigned left_height = height(node->left);
        const unsigned right_height = height(node->right);
        max_height = left_height > right_height ? left_height : right_height;
    }

    return max_height;
}

static int balance_factor(avl_node_s *node)
{    
    int bf = 0;
    if (node) bf = height(node->left) - height(node->right);
    return bf;
}

static avl_node_s *left_rotate(avl_node_s *pivot)
{
    avl_node_s *new_pivot = pivot->right;

    pivot->right = new_pivot->left;
    new_pivot->left = pivot;

    pivot->height = max_height(pivot) + 1;
    new_pivot->height = max_height(new_pivot) + 1;

    return new_pivot;
}

static avl_node_s *right_rotate(avl_node_s *pivot)
{
    avl_node_s *new_pivot = pivot->left;

    pivot->left = new_pivot->right;
    new_pivot->right = pivot;

    pivot->height = max_height(pivot) + 1;
    new_pivot->height = max_height(new_pivot) + 1;

    return new_pivot;
}

static avl_node_s *recursive_insert(avl_s *avl, avl_node_s *node, avl_node_s *new_node)
{
    if (!node)
        node = new_node;
    else if (avl->compare_function(new_node->obj, node->obj) < 0)
        node->left = recursive_insert(avl, node->left, new_node);
    else
        node->right = recursive_insert(avl, node->right, new_node);

    node->height = max_height(node) + 1;

    int bf = balance_factor(node);

    if (bf > 1) {

        if (avl->compare_function(new_node->obj, node->left->obj) < 0)
            node = right_rotate(node);
        else if (avl->compare_function(new_node->obj, node->left->obj) > 0) {
            node->left = left_rotate(node->left);
            node = right_rotate(node);
        }

    } else if (bf < -1) {

        if (avl->compare_function(new_node->obj, node->right->obj) > 0)
            node = left_rotate(node);
        else if (avl->compare_function(new_node->obj, node->right->obj) < 0) {
            node->right = right_rotate(node->right);
            node = left_rotate(node);
        }
    }

    return node;
}

static avl_node_s *avl_tree__delete_helper(avl_s *avl, avl_node_s *node, const void *obj)
{
    if (node) {

        if (avl->compare_function(obj, node->obj) < 0)
            node->left = avl_tree__delete_helper(avl, node->left, obj);

        else if (avl->compare_function(obj, node->obj) > 0)
            node->right = avl_tree__delete_helper(avl, node->right, obj);

        else {

            avl_node_s *node_to_delete = node;

            if ( !node_to_delete->left && !node_to_delete->right ) {
                node = NULL;
                free(node_to_delete->obj);
                free(node_to_delete);
                avl->size -= 1;
            
            } else if ( !node_to_delete->left ) {
                node = node_to_delete->right;
                free(node_to_delete->obj);
                free(node_to_delete);
                avl->size -= 1;
            
            } else if ( !node_to_delete->right ) {
                node = node_to_delete->left;
                free(node_to_delete->obj);
                free(node_to_delete);
                avl->size -= 1;
            
            } else {
                /* Replace with predecessor approach */
                node_to_delete = avl_tree__max_helper(node->left);
                memcpy(node->obj, node_to_delete->obj, avl->element_size);
                node->left = avl_tree__delete_helper(avl, node->left, node->obj);
            }
        }

        if (node) {

            node->height = max_height(node) + 1;
            int bf = balance_factor(node);

            if (bf > 1) {

                if (balance_factor(node->left) < 0) {
                    node->left = left_rotate(node->left);
                    node = right_rotate(node);
                } else
                    node = right_rotate(node);

            } else if (bf < -1) {

                if (balance_factor(node->right) > 0) {
                    node->right = right_rotate(node->right);
                    node = left_rotate(node);
                } else
                    node = left_rotate(node);
            }
        }
    }

    return node;
}

static avl_node_s *avl_tree__min_helper(avl_node_s *node)
{
    if (node) while (node->left) node = node->left;

    return node;
}

static avl_node_s *avl_tree__max_helper(avl_node_s *node)
{
    if (node) while (node->right) node = node->right;

    return node;
}

static avl_node_s *avl_tree__find_helper(avl_s *avl, avl_node_s *node, const void *obj)
{
    int valid_and_not_found = node && avl->compare_function(obj, node->obj);

    if (valid_and_not_found) {

        if (avl->compare_function(obj, node->obj) < 0)
            node = avl_tree__find_helper(avl, node->left, obj);
        else
            node = avl_tree__find_helper(avl, node->right, obj);
    }

    return node;
}
