#pragma once


typedef struct avl_node_s {
    
    int val;
    struct avl_node_s *left;
    struct avl_node_s *right;
    unsigned height;

} avl_node_s;


/**
 * @param  root: pointer to root of the tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
avl_node_s *avl_tree__insert(avl_node_s *root, const int val);

/**
 * @param  root: pointer to root of tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
avl_node_s *avl_tree__delete(avl_node_s *root, const int val);

/**
 * @param  node: The relative node for which a min value will
 *               be searched for.
 * @return Pointer to min value node relative to argument
 */
avl_node_s *avl_tree__min(avl_node_s *node);

/**
 * @param  node: The relative node for which a max value will
 *               be searched for.
 * @return Pointer to max value node relative to argument
 */
avl_node_s *avl_tree__max(avl_node_s *node);

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
