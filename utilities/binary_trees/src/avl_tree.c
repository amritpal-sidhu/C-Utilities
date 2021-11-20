#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"


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

static avl_node_s *recursive_insert(avl_node_s *root, avl_node_s *new_node)
{
    if (!root)
        root = new_node;
    else if (new_node->val < root->val)
        root->left = recursive_insert(root->left, new_node);
    else
        root->right = recursive_insert(root->right, new_node);

    root->height = max_height(root) + 1;

    int bf = balance_factor(root);

    if (bf > 1) {

        if (new_node->val < root->left->val)
            root = right_rotate(root);
        else if (new_node->val > root->left->val) {
            root->left = left_rotate(root->left);
            root = right_rotate(root);
        }

    } else if (bf < -1) {

        if (new_node->val > root->right->val)
            root = left_rotate(root);
        else if (new_node->val < root->right->val) {
            root->right = right_rotate(root->right);
            root = left_rotate(root);
        }
    }

    return root;
}

/**
 * Public function definitions
 */
avl_node_s *avl_tree__insert(avl_node_s *root, const int val)
{   
    avl_node_s *new_node = malloc(sizeof(avl_node_s));
    avl_node_s *cur, *parent;

    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;

    return recursive_insert(root, new_node);
}

avl_node_s *avl_tree__delete(avl_node_s *root, const int val)
{
    if (root) {

        if (val < root->val)
            root->left = avl_tree__delete(root->left, val);

        else if (val > root->val)
            root->right = avl_tree__delete(root->right, val);

        else {

            avl_node_s *node_to_delete = root;

            if ( !node_to_delete->left && !node_to_delete->right ) {
                root = NULL;
                free(node_to_delete);
            
            } else if ( !node_to_delete->left ) {
                root = node_to_delete->right;
                free(node_to_delete);
            
            } else if ( !node_to_delete->right ) {
                root = node_to_delete->left;
                free(node_to_delete);
            
            } else {
                /* Replace with predecessor approach */
                node_to_delete = avl_tree__max(root->left);
                root->val = node_to_delete->val;
                root->left = avl_tree__delete(root->left, root->val);
            }
        }

        if (root) {

            root->height = max_height(root) + 1;
            int bf = balance_factor(root);

            if (bf > 1) {

                if (balance_factor(root->left) < 0) {
                    root->left = left_rotate(root->left);
                    root = right_rotate(root);
                } else
                    root = right_rotate(root);

            } else if (bf < -1) {

                if (balance_factor(root->right) > 0) {
                    root->right = right_rotate(root->right);
                    root = left_rotate(root);
                } else
                    root = left_rotate(root);
            }
        }
    }

    return root;
}

avl_node_s *avl_tree__min(avl_node_s *node)
{
    if (node) while (node->left) node = node->left;

    return node;
}

avl_node_s *avl_tree__max(avl_node_s *node)
{
    if (node) while (node->right) node = node->right;

    return node;
}

avl_node_s *avl_tree__find(avl_node_s *root, const int val)
{
    if (root && root->val != val) {

        if (val < root->val)
            root = avl_tree__find(root->left, val);
        else
            root = avl_tree__find(root->right, val);
    }

    return root;
}

void avl_tree__print(const avl_node_s *root)
{
    static int depth;

    if (root) {

        ++depth;

        avl_tree__print(root->right);

        for (int i = 1; i < depth; ++i) printf("\t");
            printf("%i:%i\n", root->val, root->height);

        avl_tree__print(root->left);

        --depth;
    }
}
