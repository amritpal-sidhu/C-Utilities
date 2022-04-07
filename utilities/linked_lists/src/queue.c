#include "queue.h"

#include <stdlib.h>
#include <string.h>


int queue__init(queue_s *q, const unsigned int element_size)
{
    int retval = 0;

    if (q && element_size) {

        q->front = NULL;
        q->back = NULL;
        q->element_size = element_size;
        q->size = 0;

        retval = 1;
    }

    return retval;
}

int queue__push(queue_s *q, const void *obj)
{
    int retval = 0;
    doubly_linked_node_s *new_node = malloc(sizeof(doubly_linked_node_s));

    if (q && q->element_size && obj && new_node
        && (new_node->obj=malloc(q->element_size))) {

        memcpy(new_node->obj, obj, q->element_size);
        new_node->next = NULL;
        new_node->prev = NULL;

        if (q->back) {
            q->back->next = new_node;
            new_node->prev = q->back;
        }
        else
            q->front = new_node;

        q->back = new_node;
        q->size += 1;
        retval = 1;
    }

    return retval;
}


int queue__pop(queue_s *q, void *obj)
{
    doubly_linked_node_s *old_node;
    int retval = 0;

    if (q && q->element_size && q->front) {

        old_node = q->front;
        q->front = old_node->next;

        if (q->front)
            q->front->prev = NULL;
        else
            q->back = NULL;

        if (obj)
            memcpy(obj, old_node->obj, q->element_size);

        free(old_node);
        q->size -= 1;
        retval = 1;
    }

    return retval;
}

void queue__clear(queue_s *q)
{
    if (q) {

        while (q->front)
            queue__pop(q, NULL);
    }
}
