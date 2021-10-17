#include <stdio.h>
#include <stdlib.h>

#include "avl_tree.h"


int main(void) {

    avl_node_s *root = NULL;
    char cmd;
    int value;

    do {

        scanf("%c", &cmd);

        if (cmd == 'i') {
            scanf("%i", &value);
            avl_tree__insert(&root, value);
            printf("\n");
            avl_tree__print(root);
            printf("\n");
        }
        else if (cmd == 'd') {
            scanf("%i", &value);
            avl_tree__delete(&root, value);
            printf("\n");
            avl_tree__print(root);
            printf("\n");
        }

    } while (cmd != 'q');

    return 0;
}