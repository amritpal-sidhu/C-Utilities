#include "stack.h"

#include <stdlib.h>


int stack__init(stack_s *s, void *obj)
{
    singly_linked_node_s *new_node;
    int retval = 0;

    if (s) {

        s->top = NULL;
        s->size = 0;

        if (obj && (new_node=malloc(sizeof(singly_linked_node_s)))) {

            new_node->obj = obj;
            new_node->next = NULL;
            s->top = new_node;
            s->size = 1;
        }

        retval = 1;
    }

    return retval;
}

int stack__push(stack_s *s, void *obj)
{
    singly_linked_node_s *new_node = malloc(sizeof(singly_linked_node_s));
    int retval = 0;

    if (s && obj && new_node) {

        new_node->obj = obj;
        new_node->next = NULL;
        new_node->next = s->top;
        s->top = new_node;
        s->size += 1;
        retval = 1;
    }

    return retval;
}


int stack__pop(stack_s *s, void **obj)
{
    singly_linked_node_s *old_node;
    int retval = 0;

    if (s && s->top) {

        old_node = s->top;
        s->top = old_node->next;

        if (obj)
            *obj = old_node->obj;

        free(old_node);
        s->size -= 1;
        retval = 1;
    }

    return retval;
}

void stack__clear(stack_s *s)
{
    if (s) {

        while (s->top)
            stack__pop(s, NULL);
    }
}
