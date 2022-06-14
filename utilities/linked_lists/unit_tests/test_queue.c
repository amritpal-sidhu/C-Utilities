#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "unity.h"


void setUp(void)
{
    srand(time(NULL));
}

void tearDown(void)
{

}


void test_empty_queue_init(void)
{
    TEST_ASSERT_NULL(queue__new(0));
}

void test_queue_init_with_value(void)
{
    queue_t *q;
    int expected_value = rand();
    const unsigned int expected_size = 1;
    int actual_value = expected_value+32;

    TEST_ASSERT_NOT_NULL(q=queue__new(sizeof(int)));
    TEST_ASSERT(queue__push(q, &expected_value));
    TEST_ASSERT_NOT_NULL(q->front);
    TEST_ASSERT_NOT_NULL(q->back);
    TEST_ASSERT_EQUAL(expected_size, q->size);
    TEST_ASSERT(queue__pop(q, &actual_value));
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_EQUAL(expected_value, actual_value);
    TEST_ASSERT_EQUAL(expected_size-1, q->size);

    queue__delete(q);
}

void test_series_of_random_values_push_and_pop(void)
{
    queue_t *q;
    const unsigned int number_of_values = 1024;
    int expected_values[number_of_values];
    int actual_value;

    TEST_ASSERT_NOT_NULL(q=queue__new(sizeof(int)));
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_EQUAL(0, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        expected_values[i] = rand();
        TEST_ASSERT(queue__push(q, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(q->front);
        TEST_ASSERT_NOT_NULL(q->back);
        TEST_ASSERT_EQUAL(i+1, q->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        actual_value = expected_values[i]+32;
        TEST_ASSERT(queue__pop(q, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i], actual_value);
        TEST_ASSERT_EQUAL(number_of_values-1-i, q->size);
    }

    TEST_ASSERT_EQUAL(0, q->size);
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_FALSE(queue__pop(q, &actual_value));

    queue__delete(q);
}

void test_series_of_string_array_push_and_pop(void)
{
    queue_t *q;
    const unsigned int number_of_values = 8;
    /**
     * Hardcoded for now.
     * Could be generated externally and moved to a file.
     */
    char *expected_values[8] = {
        "abc",
        "delta",
        "fg",
        "hijklmn",
        "op",
        "qr",
        "stuvw",
        "xyz"
    };
    char *actual_value;

    TEST_ASSERT_NOT_NULL(q=queue__new(number_of_values*sizeof(char)));
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_EQUAL(0, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        TEST_ASSERT(queue__push(q, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(q->front);
        TEST_ASSERT_NOT_NULL(q->back);
        TEST_ASSERT_EQUAL(i+1, q->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        actual_value = '\0';
        TEST_ASSERT(queue__pop(q, &actual_value));
        TEST_ASSERT_EQUAL_STRING(expected_values[i], actual_value);
        TEST_ASSERT_EQUAL(number_of_values-1-i, q->size);
    }

    TEST_ASSERT_EQUAL(0, q->size);
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_FALSE(queue__pop(q, &actual_value));

    queue__delete(q);
}

void test_series_of_struct_array_push_and_pop(void)
{
    queue_t *q;
    const unsigned int number_of_values = 8;
    /**
     * Hardcoded for now.
     * Could be generated externally and moved to a file.
     */
    struct test_s {
        int x;
        int y;
        int z;
    } expected_values[8] = {
        {0,0,0},
        {0,0,1},
        {0,1,0},
        {0,1,1},
        {1,0,0},
        {1,0,1},
        {1,1,0},
        {1,1,1},
    };
    struct test_s actual_value;

    TEST_ASSERT_NOT_NULL(q=queue__new(sizeof(struct test_s)));
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_EQUAL(0, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        TEST_ASSERT(queue__push(q, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(q->front);
        TEST_ASSERT_NOT_NULL(q->back);
        TEST_ASSERT_EQUAL(i+1, q->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, q->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        actual_value.x = -1;
        actual_value.y = -1;
        actual_value.z = -1;
        TEST_ASSERT(queue__pop(q, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i].x, actual_value.x);
        TEST_ASSERT_EQUAL(expected_values[i].y, actual_value.y);
        TEST_ASSERT_EQUAL(expected_values[i].z, actual_value.z);
        TEST_ASSERT_EQUAL(number_of_values-1-i, q->size);
    }

    TEST_ASSERT_EQUAL(0, q->size);
    TEST_ASSERT_NULL(q->front);
    TEST_ASSERT_NULL(q->back);
    TEST_ASSERT_FALSE(queue__pop(q, &actual_value));

    queue__delete(q);
}
