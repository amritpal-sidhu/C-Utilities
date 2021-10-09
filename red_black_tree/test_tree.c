#include <stdio.h>
#include <stdlib.h>

#include "red_black_tree.h"


int main(void) {

    rb_node_t *root = NULL;
    char cmd;
    int value;

    do {

        scanf("%c", &cmd);

        if (cmd == 'i') {
            scanf("%i", &value);
            root = red_black_tree__insert(root, value);
            printf("\n");
            red_black_tree__print(root);
            printf("\n\n");
        }
        else if (cmd == 'd') {
            scanf("%i", &value);
            root = red_black_tree__delete(root, value);
            printf("\n");
            red_black_tree__print(root);
            printf("\n");
        }

    } while (cmd != 'q');

    return 0;
}