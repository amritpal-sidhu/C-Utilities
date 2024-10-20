#include "log.h"

#include "unity.h"

#include <string.h>


#define STR_BUF_SIZE    256

const char test_filepath[] = "test_file.txt";
const char ignore_suffix[] = "seconds]";


void setUp(void)
{

}

void tearDown(void)
{
    remove(test_filepath);
}


void test_open_close_and_delete(void)
{
    const char mode[] = "w";
    
    log_t *log_handle;
    char msg_buf[STR_BUF_SIZE];

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    for (size_t i = 0; i < LOG_LEVEL_ENUM_ITEMS; ++i) {
        snprintf(msg_buf, sizeof(msg_buf), "at loop %u", i);
        TEST_ASSERT_EQUAL_MESSAGE(LOG_LEVEL_ENUM_ITEMS, log_handle->disabled_log_levels[i], msg_buf);
    }
    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_none(void)
{
    const char expected[] = ": Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_NONE, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_none_va(void)
{
    const char expected[] = ": Testing writing va count is 2\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_NONE, "Testing writing %s %i", "va count is", 2));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_info(void)
{
    const char expected[] = " INFO: Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_INFO, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_status(void)
{
    const char expected[] = " STATUS: Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_STATUS, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_debug(void)
{
    const char expected[] = " DEBUG: Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_DEBUG, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_warning(void)
{
    const char expected[] = " WARNING: Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_WARNING, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_write_log_level_error(void)
{
    const char expected[] = " ERROR: Testing writing\n";
    const char mode[] = "w+";
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__write(log_handle, LOG_ERROR, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    actual_corrected = strstr(actual_corrected, ignore_suffix)+strlen(ignore_suffix);
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_disable_log_level_debug(void)
{
    const char expected[] = "";
    const char mode[] = "w+";
    const log_level_t level = LOG_DEBUG;
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__disable_log_levels(log_handle, &level, 1));
    TEST_ASSERT_FALSE(log__write(log_handle, LOG_DEBUG, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_disable_log_level_debug_and_data(void)
{
    const char expected[] = "";
    const char mode[] = "w+";
    const log_level_t levels[] = {LOG_DEBUG, LOG_DATA};
    const size_t disabled_level_count = 2;
    
    log_t *log_handle;
    char actual[STR_BUF_SIZE];
    char msg_buf[STR_BUF_SIZE];

    memset(actual, 0, sizeof(actual));

    TEST_ASSERT_NOT_NULL(log_handle=log__open(test_filepath, mode));
    TEST_ASSERT(log__disable_log_levels(log_handle, levels, disabled_level_count));
    TEST_ASSERT_FALSE(log__write(log_handle, LOG_DEBUG, "Testing writing"));
    TEST_ASSERT_FALSE(log__write(log_handle, LOG_DATA, "Testing writing"));
    TEST_ASSERT(log__read(log_handle, actual, sizeof(actual)));

    // ignore first line and the timestamp
    char *actual_corrected = strstr(actual, "\n")+1;
    snprintf(msg_buf, sizeof(msg_buf), "filename is %s", log_handle->filepath);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expected, actual_corrected, msg_buf);

    log__close(log_handle);
    log__delete(log_handle);
}

void test_get_file_size(void)
{
    FILE *test_fp = fopen(test_filepath, "w+");
    const char str[] = "A test string of some length";
    const size_t expected = strlen(str);

    fprintf(test_fp, str);
    TEST_ASSERT_EQUAL(expected, get_file_size(test_fp));
    fclose(test_fp);
}
