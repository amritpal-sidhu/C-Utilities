#pragma once


typedef struct avl_node_s {
    
    int val;
    struct avl_node_s *left;
    struct avl_node_s *right;
    unsigned height;

} avl_node_s;


/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
avl_node_s *avl_tree__insert(avl_node_s *root, const int val);

/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
avl_node_s *avl_tree__delete(avl_node_s *root, const int val);


avl_node_s *min_value_node(avl_node_s *node);

avl_node_s *max_value_node(avl_node_s *node);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
avl_node_s *avl_tree__find(avl_node_s *root, const int val);

/**
 * Print the contents of the tree.
 * 
 * @param  root: pointer to root of the tree
 */
void avl_tree__print(const avl_node_s *root);
