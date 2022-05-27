#include "queue.h"

#include <stdlib.h>
#include <string.h>


queue_t *queue__new(const unsigned int element_size)
{
    queue_t *q = NULL;

    if (element_size && (q=malloc(sizeof(queue_t)))) {

        q->front = NULL;
        q->back = NULL;
        q->element_size = element_size;
        q->size = 0;
    }

    return q;
}

void queue__delete(queue_t *q)
{
    free(q);
}

int queue__push(queue_t *q, const void *obj)
{
    int retval = 0;
    doubly_linked_node_t *new_node = malloc(sizeof(doubly_linked_node_t));

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


int queue__pop(queue_t *q, void *obj)
{
    doubly_linked_node_t *old_node;
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

void queue__clear(queue_t *q)
{
    if (q) {

        while (q->front)
            queue__pop(q, NULL);
    }
}
