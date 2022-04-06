#include "queue.h"

#include <stdlib.h>


int queue__init(queue_s *q, void *obj)
{
    doubly_linked_node_s *new_node;
    int retval = 0;

    if (q) {

        q->front = NULL;
        q->back = NULL;
        q->size = 0;

        if (obj && (new_node=malloc(sizeof(doubly_linked_node_s)))) {

            new_node->obj = obj;
            new_node->next = NULL;
            new_node->prev = NULL;
            q->front = new_node;
            q->back = new_node;
            q->size += 1;
        }

        retval = 1;
    }

    return retval;
}

int queue__push(queue_s *q, void *obj)
{
    doubly_linked_node_s *new_node = malloc(sizeof(doubly_linked_node_s));
    int retval = 0;

    if (q && obj && new_node) {

        new_node->obj = obj;
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


int queue__pop(queue_s *q, void **obj)
{
    doubly_linked_node_s *old_node;
    int retval = 0;

    if (q && q->front) {

        old_node = q->front;
        q->front = old_node->next;

        if (q->front)
            q->front->prev = NULL;
        else
            q->back = NULL;

        if (obj)
            *obj = old_node->obj;

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
