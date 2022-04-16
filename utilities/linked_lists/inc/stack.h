#pragma once

#include "linked_list_types.h"


typedef struct stack_s {

    singly_linked_node_t *top;
    unsigned int element_size;
    unsigned int size;

} stack_t;


int stack__init(stack_t *s, const unsigned int element_size);

int stack__push(stack_t *s, const void *obj);
int stack__pop(stack_t *s, void *obj);

void stack__clear(stack_t *s);
