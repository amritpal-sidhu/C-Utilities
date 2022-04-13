#pragma once

#include "linked_list_types.h"


typedef struct queue_s {

    doubly_linked_node_t *front;
    doubly_linked_node_t *back;
    unsigned int element_size;
    unsigned int size;

} queue_t;


int queue__init(queue_t *q, const unsigned int element_size);

int queue__push(queue_t *q, const void *obj);
int queue__pop(queue_t *q, void *obj);

void queue__clear(queue_t *q);
