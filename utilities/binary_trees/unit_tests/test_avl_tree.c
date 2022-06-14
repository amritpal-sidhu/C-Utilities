#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "avl_tree.h"


#define STR_BUF_SIZE    256


enum data_type {

    INTEGER,
    STRING,
    STRUCT

};

static const char *file_dir = "test_data/avl_tree";

static char read_str_buf[STR_BUF_SIZE];
static char write_str_buf[STR_BUF_SIZE];


/**
 * Helper functions
 */
static FILE *get_file_handle(const char *filename);
static void inorder_str_write(avl_node_t *root, const enum data_type dt);

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
    avl_t *avl;
    int value = 0;

    TEST_ASSERT_NULL(avl_tree__new(0, cmp));
    TEST_ASSERT_NULL(avl_tree__new(sizeof(int), NULL));
    TEST_ASSERT_NOT_NULL(avl=avl_tree__new(sizeof(int), cmp));
    TEST_ASSERT(avl_tree__insert(avl, &value));
    TEST_ASSERT(avl_tree__remove(avl, &value));

    avl_tree__delete(avl);
}

void test_tree_using_predetermined_integer_data(void)
{
    FILE *input_file = get_file_handle("input1.txt");
    FILE *output_file = get_file_handle("output1.txt");
    char msg_buf[STR_BUF_SIZE];
    size_t loop_iteration = 0;
    char cmd;
    int value;

    avl_t *avl;
    avl_node_t *ptr = NULL;

    TEST_ASSERT_NOT_NULL(avl=avl_tree__new(sizeof(int), cmp));

    if (input_file && output_file) {

        while (fgets(read_str_buf, STR_BUF_SIZE, input_file)) {

            ++loop_iteration;
            sscanf(read_str_buf, "%c%i", &cmd, &value);

            switch (cmd)
            {
            case 'i': TEST_ASSERT(avl_tree__insert(avl, &value));
                break;

            case 'd': TEST_ASSERT(avl_tree__remove(avl, &value));
                break;

            case 'f': TEST_ASSERT(avl_tree__find(avl, &value, ptr));
                break;
            
            default:
                break;
            }

            /* actual inorder string */
            inorder_str_write(avl->root, INTEGER);
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

    avl_tree__delete(avl);
}

void test_tree_using_predetermined_string_data(void)
{
    const unsigned int max_str_size = 16;
    FILE *input_file = get_file_handle("input2.txt");
    FILE *output_file = get_file_handle("output2.txt");
    char msg_buf[STR_BUF_SIZE];
    size_t loop_iteration = 0;
    char cmd;
    char value[max_str_size];

    avl_t *avl;
    avl_node_t *ptr = NULL;

    TEST_ASSERT_NOT_NULL(avl=avl_tree__new(max_str_size*sizeof(char), (compare_function_t)strcmp));

    if (input_file && output_file) {

        while (fgets(read_str_buf, STR_BUF_SIZE, input_file)) {

            ++loop_iteration;
            sscanf(read_str_buf, "%c%s", &cmd, value);

            switch (cmd)
            {
            case 'i': TEST_ASSERT(avl_tree__insert(avl, value));
                break;

            case 'd': TEST_ASSERT(avl_tree__remove(avl, value));
                break;

            case 'f': TEST_ASSERT(avl_tree__find(avl, value, ptr));
                break;
            
            default:
                break;
            }

            /* actual inorder string */
            inorder_str_write(avl->root, STRING);
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

    avl_tree__delete(avl);
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

static void inorder_str_write(avl_node_t *root, const enum data_type dt)
{
    char local_str_buf[STR_BUF_SIZE];

    if (root) {
        inorder_str_write(root->left, dt);

        switch (dt) {

            case INTEGER:
                sprintf(local_str_buf, "%i:%i ", *((int*)root->obj), root->height);
                break;
            
            case STRING:
                sprintf(local_str_buf, "%s:%i ", ((char*)root->obj), root->height);
                break;

            case STRUCT:
                break;

            default:
                break;
        }
        
        strcat(write_str_buf, local_str_buf);

        inorder_str_write(root->right, dt);
    }
}
