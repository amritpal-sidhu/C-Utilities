#pragma once

#include "linked_list_types.h"


typedef struct queue_s {

    doubly_linked_node_s *front;
    doubly_linked_node_s *back;
    unsigned int size;

} queue_s;


int queue__init(queue_s *q, const int *val);

int queue__push(queue_s *q, const int val);
int queue__pop(queue_s *q, int *val);

void queue__clear(queue_s *q);
