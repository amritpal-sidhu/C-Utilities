#pragma once

#include <stdio.h>


typedef enum {

    NONE,
    STATUS,
    DEBUG,
    WARNING,
    ERROR

} log_level_t;

typedef struct {

    FILE *log_fp;
    char *filepath;

} log_t;


log_t *logging__open(const char *filepath, const char *mode);
void logging__close(const log_t *log_handle);
void logging__delete(log_t *log_handle);
int logging__read(const log_t *log_handle, char *buffer, const size_t buffer_size);
int logging__write(log_t *log_handle, const log_level_t log_level, const char *format, ...);

/* Filesize helper function */
size_t get_file_size(FILE *fp);
