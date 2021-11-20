#pragma once
/**
 * Simple binary search tree implementation in C for practice and
 * future reference.
 */

typedef struct bst_node_s {

    int val;
    struct bst_node_s *left;
    struct bst_node_s *right;

} bst_node_s;

/**
 * @param  root: pointer to root of the tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
bst_node_s *binary_search_tree__insert(bst_node_s *root, const int val);

/**
 * @param  root: pointer to root of tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
bst_node_s *binary_search_tree__delete(bst_node_s *root, const int val);

/**
 * @param  node: The relative node for which a min value will
 *               be searched for.
 * @return Pointer to min value node relative to argument
 */
bst_node_s *min_value_node(bst_node_s *node);

/**
 * @param  node: The relative node for which a max value will
 *               be searched for.
 * @return Pointer to max value node relative to argument
 */
bst_node_s *max_value_node(bst_node_s *node);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
bst_node_s *binary_search_tree__find(bst_node_s *root, const int val);

/**
 * Print the contents of the tree.
 */
void binary_search_tree__print(const bst_node_s *root);
