#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "red_black_tree.h"


#define STR_BUF_SIZE    256

static const char *file_dir = "test_data/red_black_tree";
static const char *input_filename = "input1.txt";
static const char *output_filename = "output1.txt";

static char read_str_buf[STR_BUF_SIZE];
static char write_str_buf[STR_BUF_SIZE];


/**
 * Helper functions
 */
static FILE *get_file_handle(const char *filename);
static void inorder_str_write(rb_node_t *root);

/**
 * Compare function for BST
 */
int cmp(const void *a, const void *b) {

    int a_int = *((int*)a);
    int b_int = *((int*)b);

    return a_int - b_int;
}

/**
 * Test functions
 */
void setUp(void)
{
    memset(read_str_buf, 0, STR_BUF_SIZE);
    memset(write_str_buf, 0, STR_BUF_SIZE);
}

void tearDown(void)
{

}

void test_init_with_insert(void)
{
    const unsigned int expected_init_element_size = 0;
    const compare_function_t expected_init_func_value = NULL;
    const unsigned int expected_init_size = 0;
    rb_t rb = {0};
    int value = 0;

    TEST_ASSERT_EQUAL(expected_init_element_size, rb.element_size);
    TEST_ASSERT_EQUAL(expected_init_func_value, rb.cmp_f);
    TEST_ASSERT_EQUAL(expected_init_size, rb.size);

    TEST_ASSERT_FALSE(red_black_tree__init(&rb, 0, cmp));
    TEST_ASSERT_FALSE(red_black_tree__init(&rb, sizeof(int), NULL));
    TEST_ASSERT(red_black_tree__init(&rb, sizeof(int), cmp));
    TEST_ASSERT(red_black_tree__insert(&rb, &value));
    TEST_ASSERT_FALSE(red_black_tree__init(&rb, sizeof(int), cmp));
    TEST_ASSERT(red_black_tree__delete(&rb, &value));
}

void test_tree_using_predetermined_data(void)
{
    FILE *input_file = get_file_handle(input_filename);
    FILE *output_file = get_file_handle(output_filename);
    char msg_buf[STR_BUF_SIZE];
    size_t loop_iteration = 0;
    char cmd;
    int value;

    rb_t rb = {0};
    rb_node_t *ptr = NULL;

    TEST_ASSERT(red_black_tree__init(&rb, sizeof(int), cmp));

    if (input_file && output_file) {

        while (fgets(read_str_buf, STR_BUF_SIZE, input_file)) {

            ++loop_iteration;
            sscanf(read_str_buf, "%c%i", &cmd, &value);

            switch (cmd)
            {
            case 'i': TEST_ASSERT(red_black_tree__insert(&rb, &value));
                break;

            case 'd': TEST_ASSERT(red_black_tree__delete(&rb, &value));
                break;

            case 'f': TEST_ASSERT(red_black_tree__find(&rb, &value, ptr));
                break;
            
            default:
                break;
            }

            /* actual inorder string */
            inorder_str_write(rb.root);
            write_str_buf[strlen(write_str_buf)-1] = '\0';

            /* expected inorder string */
            memset(read_str_buf, 0, STR_BUF_SIZE);
            fgets(read_str_buf, STR_BUF_SIZE, output_file);
            read_str_buf[strlen(read_str_buf)-1] = '\0';

            snprintf(msg_buf, sizeof(msg_buf), "Failure at line %li of test files", loop_iteration);
            TEST_ASSERT_EQUAL_STRING_MESSAGE(read_str_buf, write_str_buf, msg_buf);
            resetTest();
        }

        fclose(input_file);
        fclose(output_file);
    }
    else {
        TEST_PRINTF("test_tree_using_predetermined_data(): failure to read data files.  input = %p, output = %p\n", input_file, output_file);
        TEST_FAIL();
    }
}


/**
 * Private function definitions
 */
static FILE *get_file_handle(const char *filename)
{    
    const unsigned file_dir_strlen = strlen(file_dir);

    memset(read_str_buf, 0, STR_BUF_SIZE);
    strcat(read_str_buf, file_dir);
    read_str_buf[file_dir_strlen] = '/';
    strcat(read_str_buf+file_dir_strlen+1, filename);

    return fopen(read_str_buf, "r");
}

static void inorder_str_write(rb_node_t *root)
{
    char local_str_buf[STR_BUF_SIZE];

    if (root) {
        inorder_str_write(root->left);

        sprintf(local_str_buf, "%i:%c ", *((int*)root->obj), root->color == RED ? 'R' : 'B');
        strcat(write_str_buf, local_str_buf);

        inorder_str_write(root->right);
    }
}
