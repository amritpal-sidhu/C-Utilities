#pragma once
/**
 * Red Black Tree implementation in C
 */

typedef struct rb_node_t {

    int val;
    struct rb_node_t *parent;
    struct rb_node_t *left;
    struct rb_node_t *right;
    int color;

} rb_node_t;

/**
 * @param  root: pointer to root of the tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
rb_node_t *red_black_tree__insert(rb_node_t *root, const int val);

/**
 * @param  root: pointer to root of the tree
 * @param  val: value to delete from the tree
 * @retval Pointer to the root of the tree
 */
rb_node_t *red_black_tree__delete(rb_node_t *root, const int val);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
rb_node_t *red_black_tree__find(rb_node_t *root, const int val);

/**
 * Print the contents of the tree.
 * 
 * @param  root: pointer to root of the tree
 */
void red_black_tree__print(const rb_node_t *root);
