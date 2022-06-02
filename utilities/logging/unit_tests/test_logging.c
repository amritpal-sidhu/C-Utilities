#include "logging.h"

#include "unity.h"


void setUp(void)
{

}

void tearDown(void)
{

}


void test_open_close_and_delete(void)
{
    const char test_filename[] = "test_file.txt";
    const char mode[] = "w";

    TEST_ASSERT(logging__open(test_filename, mode));

    logging__close();

    TEST_ASSERT(logging__delete());
}

void test_write_log_level_none(void)
{
    const char expected[] = "Testing writing";
    const char test_filename[] = "test_file.txt";
    const char mode[] = "w+";
    char actual[128];

    TEST_ASSERT(logging__open(test_filename, mode));
    TEST_ASSERT(logging__write(NONE, "Testing writing"));
    TEST_ASSERT(logging__read(actual, sizeof(actual)));
    TEST_ASSERT_EQUAL_STRING(expected, actual);

    logging__close();

    TEST_ASSERT(logging__delete());
}
