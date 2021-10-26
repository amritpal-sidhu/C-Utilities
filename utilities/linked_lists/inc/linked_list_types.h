#pragma once

typedef struct singly_linked_node_s {

    int val;
    struct singly_linked_node_s *next;

} singly_linked_node_s;

typedef struct doubly_linked_node_s {

    int val;
    struct doubly_linked_node_s *next;
    struct doubly_linked_node_s *prev;

} doubly_linked_node_s;
