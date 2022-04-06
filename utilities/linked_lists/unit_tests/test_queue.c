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


UnityTestFunction test_empty_queue_init(void)
{
    queue_s q;
    const unsigned int expected_size = 0;

    queue__init(&q, NULL);

    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(expected_size, q.size);
}

UnityTestFunction test_queue_init_with_value(void)
{
    queue_s q;
    int expected_value = rand();
    const unsigned int expected_size = 1;
    int *actual_value;
    *actual_value = expected_value+32;

    TEST_ASSERT(queue__init(&q, &expected_value));
    TEST_ASSERT_NOT_EQUAL(NULL, q.front);
    TEST_ASSERT_NOT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(&expected_value, q.front->obj);
    TEST_ASSERT_EQUAL(expected_value, *((int*)q.front->obj));
    TEST_ASSERT_EQUAL(expected_size, q.size);
    TEST_ASSERT(queue__pop(&q, (void**)&actual_value));
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(expected_value, *actual_value);
    TEST_ASSERT_EQUAL(expected_size-1, q.size);
}

UnityTestFunction test_series_of_random_values_push_and_pop(void)
{
    queue_s q;
    const unsigned int number_of_values = 1024;
    int expected_values[number_of_values];
    int *actual_value;

    TEST_ASSERT(queue__init(&q, NULL));
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_EQUAL(0, q.size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        expected_values[i] = rand();
        TEST_ASSERT(queue__push(&q, &expected_values[i]));
        TEST_ASSERT_NOT_EQUAL(NULL, q.front);
        TEST_ASSERT_NOT_EQUAL(NULL, q.back);
        TEST_ASSERT_EQUAL(i+1, q.size);
    }

    TEST_ASSERT_EQUAL(number_of_values, q.size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        *actual_value = expected_values[i]+32;
        TEST_ASSERT(queue__pop(&q, (void**)&actual_value));
        TEST_ASSERT_EQUAL(expected_values[i], *actual_value);
        TEST_ASSERT_EQUAL(number_of_values-1-i, q.size);
    }

    TEST_ASSERT_EQUAL(0, q.size);
    TEST_ASSERT_EQUAL(NULL, q.front);
    TEST_ASSERT_EQUAL(NULL, q.back);
    TEST_ASSERT_FALSE(queue__pop(&q, (void**)&actual_value));
}
