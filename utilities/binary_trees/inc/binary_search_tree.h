#pragma once
/**
 * Simple binary search tree implementation in C for practice and
 * future reference.
 */

typedef struct binary_node_t {

    int val;
    struct binary_node_t *left;
    struct binary_node_t *right;

} binary_node_t;

/**
 * @param  root: pointer to root of the tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
binary_node_t *binary_search_tree__insert(binary_node_t *root, const int val);

/**
 * @param  root: pointer to root of tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
binary_node_t *binary_search_tree__delete(binary_node_t *root, const int val);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
binary_node_t *binary_search_tree__find(binary_node_t *root, const int val);

/**
 * Print the contents of the tree.
 */
void binary_search_tree__print(const binary_node_t *root);
