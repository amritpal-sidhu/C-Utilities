#include <stdio.h>
#include <stdlib.h>

#include "binary_search_tree.h"


/**
 * Public function definitions
 */
binary_node_t *binary_search_tree__insert(binary_node_t *root, const int val) {

    binary_node_t *new_node = malloc(sizeof(binary_node_t));
    binary_node_t *cur, *parent;

    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;

    if (!root) {
        root = new_node;
    }
    else {

        cur = root;

        while (cur) {

            parent = cur;

            if (val < cur->val)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (val < parent->val)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    return root;
}

binary_node_t *binary_search_tree__delete(binary_node_t *root, const int val) {

    if (root) {

        if (val < root->val)
            root->left = binary_search_tree__delete(root->left, val);

        else if (val > root->val)
            root->right = binary_search_tree__delete(root->right, val);

        else {

            binary_node_t *node_to_delete = root;

            if ( !node_to_delete->left && !node_to_delete->right ) {
                root = NULL;
                free(node_to_delete);
            }
            else if ( !node_to_delete->left ) {
                root = node_to_delete->right;
                free(node_to_delete);
            }
            else if ( !node_to_delete->right ) {
                root = node_to_delete->left;
                free(node_to_delete);
            }
            else {
                /* Replace with successor approach */
                // node_to_delete = min_value_node(root->right);
                // root->val = node_to_delete->val;
                // root->right = binary_search_tree__delete(root->right, root->val);

                /* Replace with predecessor approach */
                node_to_delete = max_value_node(root->left);
                root->val = node_to_delete->val;
                root->left = binary_search_tree__delete(root->left, root->val);
            }
        }
    }

    return root;
}

binary_node_t *min_value_node(binary_node_t *node) {

    if (node) while (node->left) node = node->left;

    return node;
}

binary_node_t *max_value_node(binary_node_t *node) {

    if (node) while (node->right) node = node->right;

    return node;
}

binary_node_t *binary_search_tree__find(binary_node_t *root, const int val) {

    if (root && root->val != val) {

        if (val < root->val)
            root = binary_search_tree__find(root->left, val);
        else
            root = binary_search_tree__find(root->right, val);
    }

    return root;
}

void binary_search_tree__print(const binary_node_t *root) {

    static int depth;

    if (root) {

        ++depth;

        binary_search_tree__print(root->right);

        for (int i = 1; i < depth; ++i) printf("\t");
        printf("%i\n", root->val);

        binary_search_tree__print(root->left);

        --depth;
    }
}
