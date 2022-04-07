#include "stack.h"

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


void test_empty_stack_init(void)
{
    stack_s s;

    TEST_ASSERT_FALSE(stack__init(&s, 0));
}

void test_stack_init_with_value(void)
{
    stack_s s;
    int expected_value = rand();
    const unsigned int expected_size = 1;
    int *actual_value = expected_value+32;

    TEST_ASSERT(stack__init(&s, sizeof(int)));
    TEST_ASSERT(stack__push(&s, &expected_value));
    TEST_ASSERT_NOT_EQUAL(NULL, s.top);
    TEST_ASSERT_EQUAL(expected_size, s.size);
    TEST_ASSERT(stack__pop(&s, &actual_value));
    TEST_ASSERT_EQUAL(NULL, s.top);
    TEST_ASSERT_EQUAL(expected_value, actual_value);
    TEST_ASSERT_EQUAL(expected_size-1, s.size);
}

void test_series_of_random_values_push_and_pop(void)
{
    stack_s s;
    const unsigned int number_of_values = 64;
    int expected_values[number_of_values];
    int actual_value;

    TEST_ASSERT(stack__init(&s, sizeof(int)));
    TEST_ASSERT_EQUAL(NULL, s.top);
    TEST_ASSERT_EQUAL(0, s.size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        expected_values[i] = rand();
        TEST_ASSERT(stack__push(&s, &expected_values[i]));
        TEST_ASSERT_NOT_EQUAL(NULL, s.top);
        TEST_ASSERT_EQUAL(i+1, s.size);
    }

    TEST_ASSERT_EQUAL(number_of_values, s.size);

    for (unsigned i = number_of_values; i > 0; --i) {
        actual_value = expected_values[i-1]+32;
        TEST_ASSERT(stack__pop(&s, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i-1], actual_value);
        TEST_ASSERT_EQUAL(i-1, s.size);
    }

    TEST_ASSERT_EQUAL(0, s.size);
    TEST_ASSERT_EQUAL(NULL, s.top);
    TEST_ASSERT_FALSE(stack__pop(&s, &actual_value));
}
