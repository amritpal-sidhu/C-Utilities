#include "stack.h"

#include <stdlib.h>


int stack__init(stack_s *s, const int *val) {

    singly_linked_node_s *new_node;
    int retval = 0;

    if (s) {

        s->top = NULL;
        s->size = 0;

        if (val && (new_node=malloc(sizeof(singly_linked_node_s)))) {

            new_node->val = *val;
            new_node->next = NULL;
            s->top = new_node;
            s->size = 1;
        }

        retval = 1;
    }

    return retval;
}

int stack__push(stack_s *s, const int val) {

    singly_linked_node_s *new_node = malloc(sizeof(singly_linked_node_s));
    int retval = 0;

    if (s && new_node) {

        new_node->val = val;
        new_node->next = NULL;
        new_node->next = s->top;
        s->top = new_node;
        s->size += 1;
        retval = 1;
    }

    return retval;
}


int stack__pop(stack_s *s, int *val) {

    singly_linked_node_s *old_node;
    int retval = 0;

    if (s && s->top) {

        old_node = s->top;
        s->top = old_node->next;
        if (val)
            *val = old_node->val;
        free(old_node);
        s->size -= 1;
        retval = 1;
    }

    return retval;
}

void stack__clear(stack_s *s) {

    if (s) {

        while (s->top)
            stack__pop(s, NULL);
    }
}
