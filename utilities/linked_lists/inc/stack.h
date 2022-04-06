#pragma once

#include "linked_list_types.h"


typedef struct stack_s {

    singly_linked_node_s *top;
    unsigned int size;

} stack_s;


int stack__init(stack_s *s, void *obj);

int stack__push(stack_s *s, void *obj);
int stack__pop(stack_s *s, void **obj);

void stack__clear(stack_s *s);
