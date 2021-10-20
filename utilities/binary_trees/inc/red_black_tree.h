#pragma once
/**
 * Red Black Tree implementation in C
 */

typedef enum {
    RED,
    BLACK
} rb_node_color_e;

typedef struct rb_node_s {

    int val;
    struct rb_node_s *parent;
    struct rb_node_s *left;
    struct rb_node_s *right;
    rb_node_color_e color;

} rb_node_s;

/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
int red_black_tree__insert(rb_node_s **root, const int val);

/**
 * @param  root: reference pointer to the root of the tree
 * @param  val: value to delete from the tree
 * @retval Integral value indicating success or failure,
 *         1 and 0 respectively
 */
int red_black_tree__delete(rb_node_s **root, const int val);

/**
 * @param  root: pointer to root of the tree
 * @param  val: Value of data at tree node
 * @retval Pointer to node with first matching value, or NULL
 */
rb_node_s *red_black_tree__find(rb_node_s *root, const int val);

/**
 * Print the contents of the tree.
 * 
 * @param  root: pointer to root of the tree
 */
void red_black_tree__print(const rb_node_s *root);
