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
    TEST_ASSERT_NULL(stack__new(0));
}

void test_stack_init_with_value(void)
{
    stack_t *s;
    int expected_value = rand();
    const unsigned int expected_size = 1;
    int actual_value = expected_value+32;

    TEST_ASSERT_NOT_NULL(s=stack__new(sizeof(int)));
    TEST_ASSERT(stack__push(s, &expected_value));
    TEST_ASSERT_NOT_NULL(s->top);
    TEST_ASSERT_EQUAL(expected_size, s->size);
    TEST_ASSERT(stack__pop(s, &actual_value));
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_EQUAL(expected_value, actual_value);
    TEST_ASSERT_EQUAL(expected_size-1, s->size);

    stack__delete(s);
}

void test_series_of_random_values_push_and_pop(void)
{
    stack_t *s;
    const unsigned int number_of_values = 64;
    int expected_values[number_of_values];
    int actual_value;

    TEST_ASSERT_NOT_NULL(s=stack__new(sizeof(int)));
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_EQUAL(0, s->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        expected_values[i] = rand();
        TEST_ASSERT(stack__push(s, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(s->top);
        TEST_ASSERT_EQUAL(i+1, s->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, s->size);

    for (unsigned i = number_of_values; i > 0; --i) {
        actual_value = expected_values[i-1]+32;
        TEST_ASSERT(stack__pop(s, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i-1], actual_value);
        TEST_ASSERT_EQUAL(i-1, s->size);
    }

    TEST_ASSERT_EQUAL(0, s->size);
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_FALSE(stack__pop(s, &actual_value));

    stack__delete(s);
}

void test_series_of_string_array_push_and_pop(void)
{
    stack_t *s;
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

    TEST_ASSERT_NOT_NULL(s=stack__new(number_of_values*sizeof(char)));
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_EQUAL(0, s->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        TEST_ASSERT(stack__push(s, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(s->top);
        TEST_ASSERT_EQUAL(i+1, s->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, s->size);

    for (unsigned i = number_of_values; i > 0; --i) {
        actual_value = '\0';
        TEST_ASSERT(stack__pop(s, &actual_value));
        TEST_ASSERT_EQUAL_STRING(expected_values[i-1], actual_value);
        TEST_ASSERT_EQUAL(i-1, s->size);
    }

    TEST_ASSERT_EQUAL(0, s->size);
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_FALSE(stack__pop(s, &actual_value));

    stack__delete(s);
}

void test_series_of_struct_array_push_and_pop(void)
{
    stack_t *s;
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

    TEST_ASSERT_NOT_NULL(s=stack__new(sizeof(struct test_s)));
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_EQUAL(0, s->size);

    for (unsigned i = 0; i < number_of_values; ++i) {
        TEST_ASSERT(stack__push(s, &expected_values[i]));
        TEST_ASSERT_NOT_NULL(s->top);
        TEST_ASSERT_EQUAL(i+1, s->size);
    }

    TEST_ASSERT_EQUAL(number_of_values, s->size);

    for (unsigned i = number_of_values; i > 0; --i) {
        actual_value.x = -1;
        actual_value.y = -1;
        actual_value.z = -1;
        TEST_ASSERT(stack__pop(s, &actual_value));
        TEST_ASSERT_EQUAL(expected_values[i-1].x, actual_value.x);
        TEST_ASSERT_EQUAL(expected_values[i-1].y, actual_value.y);
        TEST_ASSERT_EQUAL(expected_values[i-1].z, actual_value.z);
        TEST_ASSERT_EQUAL(i-1, s->size);
    }

    TEST_ASSERT_EQUAL(0, s->size);
    TEST_ASSERT_NULL(s->top);
    TEST_ASSERT_FALSE(stack__pop(s, &actual_value));

    stack__delete(s);
}
