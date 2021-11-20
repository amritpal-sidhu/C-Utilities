#include "queue.h"

#include <stdlib.h>
#include <time.h>

#include "unity.h"


/**
 * Private helper functions
 */
static void print_queue(const queue_s *q);
static void print_queue_reverse(const queue_s *q);


void setUp(void)
{
    srand(time(NULL));
}

void tearDown(void)
{

}


void test_empty_queue_init(void)
{
    queue_s q;
    const unsigned int expected_size = 0;

    queue__init(&q, NULL);

    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(expected_size, q.size);
}

void test_queue_init_with_value(void)
{
    queue_s q;
    const int expected_value = rand();
    const unsigned int expected_size = 1;
    int actual_value = expected_value+32;

    TEST_ASSERT(queue__init(&q, &expected_value));
    TEST_ASSERT_NOT_EQUAL(NULL, q.front);
    TEST_ASSERT_NOT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(expected_value, q.front->val);
    TEST_ASSERT_EQUAL(expected_size, q.size);
    TEST_ASSERT(queue__pop(&q, &actual_value));
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(expected_value, actual_value);
    TEST_ASSERT_EQUAL(expected_size-1, q.size);
}

void test_series_of_random_values_push_and_pop(void)
{
    queue_s q;
    const unsigned int number_of_values = 1024;
    int expected_values[number_of_values];
    int actual_value;

    TEST_ASSERT(queue__init(&q, NULL));
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(0, q.size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        expected_values[i] = rand();
        TEST_ASSERT(queue__push(&q, expected_values[i]));
        TEST_ASSERT_NOT_EQUAL(NULL, q.front);
        TEST_ASSERT_NOT_EQUAL(NULL, q.back);
        TEST_ASSERT_EQUAL(i+1, q.size);
    }

    TEST_ASSERT_EQUAL(number_of_values, q.size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        actual_value = expected_values[i]+32;
        TEST_ASSERT(queue__pop(&q, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i], actual_value);
        TEST_ASSERT_EQUAL(number_of_values-1-i, q.size);
    }

    TEST_ASSERT_EQUAL(0, q.size);
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_FALSE(queue__pop(&q, &actual_value));
}


/**
 * Private function definitions
 */
static void print_queue(const queue_s *q)
{
    doubly_linked_node_s *cur = q->front;

    while (cur) {
        TEST_PRINTF("%i, ", cur->val);
        cur = cur->next;
    }
}

static void print_queue_reverse(const queue_s *q)
{
    doubly_linked_node_s *cur = q->back;

    while (cur) {
        TEST_PRINTF("%i, ", cur->val);
        cur = cur->prev;
    }
}
