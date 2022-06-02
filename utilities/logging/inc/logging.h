#pragma once

#include <stdio.h>


typedef enum
{
    NONE,
    STATUS,
    DEBUG,
    WARNING,
    ERROR
} log_level_t;

extern FILE *log_fp;


int logging__open(const char *filepath, const char *mode);
void logging__close(void);
int logging__delete(void);
int logging__read(char *buffer, const size_t buffer_size);
int logging__write(const log_level_t log_level, const char *formatted_string, ...);

/* Filesize helper function */
size_t get_file_size(FILE *fp);
