#pragma once

#include <stdio.h>


typedef enum {

    LOG_NONE,
    LOG_INFO,
    LOG_STATUS,
    LOG_DEBUG,
    LOG_DATA,
    LOG_WARNING,
    LOG_ERROR

} log_level_t;

typedef struct {

    FILE *log_fp;
    char *filepath;

} log_t;


log_t *log__open(const char *filepath, const char *mode);
void log__close(const log_t *log_handle);
void log__delete(log_t *log_handle);
int log__read(const log_t *log_handle, char *buffer, const size_t buffer_size);
int log__write(log_t *log_handle, const log_level_t log_level, const char *format, ...);

/* Filesize helper function */
size_t get_file_size(FILE *fp);