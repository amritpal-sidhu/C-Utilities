#include "stack.h"

#include <stdlib.h>
#include <string.h>


int stack__init(stack_t *s, const unsigned int element_size)
{
    int retval = 0;

    if (s && element_size) {

        s->top = NULL;
        s->element_size = element_size;
        s->size = 0;

        retval = 1;
    }

    return retval;
}

int stack__push(stack_t *s, const void *obj)
{
    int retval = 0;
    singly_linked_node_t *new_node = malloc(sizeof(singly_linked_node_t));

    if (s && s->element_size && obj && new_node
        && (new_node->obj=malloc(s->element_size))) {

        memcpy(new_node->obj, obj, s->element_size);
        new_node->next = NULL;
        new_node->next = s->top;
        s->top = new_node;
        s->size += 1;
        retval = 1;
    }

    return retval;
}


int stack__pop(stack_t *s, void *obj)
{
    singly_linked_node_t *old_node;
    int retval = 0;

    if (s && s->top) {

        old_node = s->top;
        s->top = old_node->next;

        if (obj)
            memcpy(obj, old_node->obj, s->element_size);

        free(old_node);
        s->size -= 1;
        retval = 1;
    }

    return retval;
}

void stack__clear(stack_t *s)
{
    if (s) {

        while (s->top)
            stack__pop(s, NULL);
    }
}
