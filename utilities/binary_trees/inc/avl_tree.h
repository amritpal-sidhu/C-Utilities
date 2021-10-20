#pragma once



/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
int avl_tree__insert(void **root, const int val);

/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
int avl_tree__delete(void **root, const int val);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
void *avl_tree__find(void *root, const int val);

/**
 * Print the contents of the tree.
 * 
 * @param  root: pointer to root of the tree
 */
void avl_tree__print(const void *root);
