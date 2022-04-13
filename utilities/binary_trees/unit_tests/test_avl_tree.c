#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"

#include "avl_tree.h"


#define STR_BUF_SIZE    256

static const char *file_dir = "test_data/avl_tree";
static const char *input_filename = "input1.txt";
static const char *output_filename = "output1.txt";

static char read_str_buf[STR_BUF_SIZE];
static char write_str_buf[STR_BUF_SIZE];


/**
 * Helper functions
 */
static FILE *get_file_handle(const char *filename);
static void inorder_str_write(avl_node_s *root);

/**
 * Compare function for BST
 */
int compare_function(const void *a, const void *b) {

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
    avl_s avl = {0};
    int value = 0;

    TEST_ASSERT_EQUAL(expected_init_element_size, avl.element_size);
    TEST_ASSERT_EQUAL(expected_init_func_value, avl.compare_function);
    TEST_ASSERT_EQUAL(expected_init_size, avl.size);

    TEST_ASSERT_FALSE(avl_tree__init(&avl, 0, compare_function));
    TEST_ASSERT_FALSE(avl_tree__init(&avl, sizeof(int), NULL));
    TEST_ASSERT(avl_tree__init(&avl, sizeof(int), compare_function));
    TEST_ASSERT(avl_tree__insert(&avl, &value));
    TEST_ASSERT_FALSE(avl_tree__init(&avl, sizeof(int), compare_function));
    TEST_ASSERT(avl_tree__delete(&avl, &value));
}

void test_tree_using_predetermined_data(void)
{
    FILE *input_file = get_file_handle(input_filename);
    FILE *output_file = get_file_handle(output_filename);
    char cmd;
    int value;

    avl_s avl = {0};
    avl_node_s *ptr = NULL;

    TEST_ASSERT(avl_tree__init(&avl, sizeof(int), compare_function));

    if (input_file && output_file) {

        while (fgets(read_str_buf, STR_BUF_SIZE, input_file)) {

            sscanf(read_str_buf, "%c%i", &cmd, &value);

            switch (cmd)
            {
            case 'i': TEST_ASSERT(avl_tree__insert(&avl, &value));
                break;

            case 'd': TEST_ASSERT(avl_tree__delete(&avl, &value));
                break;

            case 'f': TEST_ASSERT(avl_tree__find(&avl, &value, ptr));
                break;
            
            default:
                break;
            }

            /* actual inorder string */
            inorder_str_write(avl.root);
            write_str_buf[strlen(write_str_buf)-1] = '\0';

            /* expected inorder string */
            memset(read_str_buf, 0, STR_BUF_SIZE);
            fgets(read_str_buf, STR_BUF_SIZE, output_file);
            read_str_buf[strlen(read_str_buf)-1] = '\0';

            TEST_ASSERT_EQUAL_STRING(read_str_buf, write_str_buf);

            memset(read_str_buf, 0, STR_BUF_SIZE);
            memset(write_str_buf, 0, STR_BUF_SIZE);
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

static void inorder_str_write(avl_node_s *root)
{
    char local_str_buf[STR_BUF_SIZE];

    if (root) {
        inorder_str_write(root->left);

        sprintf(local_str_buf, "%i:%i ", *((int*)root->obj), root->height);
        strcat(write_str_buf, local_str_buf);

        inorder_str_write(root->right);
    }
}
