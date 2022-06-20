#include "vector.h"

#include "unity.h"


#define PI      3.14159265358979323846264338327950


void setUp(void)
{

}

void tearDown(void)
{

}

void test_2d_mag(void)
{
    const double expected_output = 5;
    const vector2d_t a = {.i = 3, .j = 4};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector2d__mag(a));
}

void test_2d_distance(void)
{
    const double expected_output = 2;
    const vector2d_t a = {.i = -1, .j = 1};
    const vector2d_t b = {.i = 1, .j = 1};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector2d__distance(a, b));
}

void test_2d_add(void)
{
    const vector2d_t expected_output = {.i = 5, .j = 5};
    const vector2d_t a = {.i = 1, .j = 2};
    const vector2d_t b = {.i = 4, .j = 3};

    const vector2d_t actual_out = vector2d__add(a, b);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
}

void test_2d_sub(void)
{
    const vector2d_t expected_output = {.i = -3, .j = -1};
    const vector2d_t a = {.i = 1, .j = 2};
    const vector2d_t b = {.i = 4, .j = 3};

    const vector2d_t actual_out = vector2d__sub(a, b);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
}

void test_2d_scale(void)
{
    const vector2d_t expected_output = {.i = 3, .j = 6};
    const vector2d_t a = {.i = 1, .j = 2};
    const double scalar = 3;;

    const vector2d_t actual_out = vector2d__scale(a, scalar);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
}

void test_2d_dot_product(void)
{
    const double expected_output = 10;
    const vector2d_t a = {.i = 1, .j = 2};
    const vector2d_t b = {.i = 4, .j = 3};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector2d__dot_product(a, b));
}

void test_3d_mag(void)
{
    const double expected_output = 5.3851648071345;
    const vector3d_t a = {.i = 3, .j = 4, .k = 2};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector3d__mag(a));
}

void test_3d_distances(void)
{
    const double expected_output = 2.82842712474619;
    const vector3d_t a = {.i = -1, .j = 1, .k = 1};
    const vector3d_t b = {.i = 1, .j = 1, .k = -1};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector3d__distance(a, b));
}

void test_3d_add(void)
{
    const vector3d_t expected_output = {.i = 5, .j = 5, .k = 5};
    const vector3d_t a = {.i = 1, .j = 2, .k = 7};
    const vector3d_t b = {.i = 4, .j = 3, .k = -2};

    const vector3d_t actual_out = vector3d__add(a, b);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.k, actual_out.k);
}

void test_3d_sub(void)
{
    const vector3d_t expected_output = {.i = -3, .j = -1, .k = 9};
    const vector3d_t a = {.i = 1, .j = 2, .k = 7};
    const vector3d_t b = {.i = 4, .j = 3, .k = -2};

    const vector3d_t actual_out = vector3d__sub(a, b);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.k, actual_out.k);
}

void test_3d_scale(void)
{
    const vector3d_t expected_output = {.i = 3, .j = 6, .k = 21};
    const vector3d_t a = {.i = 1, .j = 2, .k = 7};
    const double scalar = 3;

    const vector3d_t actual_out = vector3d__scale(a, scalar);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.k, actual_out.k);
}

void test_3d_dot_product(void)
{
    const double expected_output = -4;
    const vector3d_t a = {.i = 1, .j = 2, .k = 7};
    const vector3d_t b = {.i = 4, .j = 3, .k = -2};

    TEST_ASSERT_EQUAL_DOUBLE(expected_output, vector3d__dot_product(a, b));
}

void test_3d_cross_product(void)
{
    const vector3d_t expected_output = {.i = -2, .j = 4, .k = -2};
    const vector3d_t a = {.i = 1, .j = 2, .k = 3};
    const vector3d_t b = {.i = 3, .j = 4, .k = 5};

    const vector3d_t actual_out = vector3d__cross_product(a, b);

    TEST_ASSERT_EQUAL_DOUBLE(expected_output.i, actual_out.i);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.j, actual_out.j);
    TEST_ASSERT_EQUAL_DOUBLE(expected_output.k, actual_out.k);
}
