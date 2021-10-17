#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"


int main(void) {

    binary_node_t *root = NULL;
    char cmd;
    int value;

    do {

        scanf("%c", &cmd);

        if (cmd == 'i') {
            scanf("%i", &value);
            root = binary_tree__insert(root, value);
            printf("\n");
            binary_tree__print(root);
            printf("\n");
        }
        else if (cmd == 'd') {
            scanf("%i", &value);
            root = binary_tree__delete(root, value);
            printf("\n");
            binary_tree__print(root);
            printf("\n");
        }

    } while (cmd != 'q');

    return 0;
}