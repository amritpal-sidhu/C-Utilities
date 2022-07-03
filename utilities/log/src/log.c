#include "log.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define LOG_LEVEL_ENUM_ITEMS    7


const char *log_level_str[LOG_LEVEL_ENUM_ITEMS] = {
    "",
    " INFO",
    " STATUS",
    " DEBUG",
    " DATA",
    " WARNING",
    " ERROR"
};


log_t *log__open(const char *filepath, const char *mode)
{
    int success = 0;
    const size_t path_strlen = strlen(filepath);
    log_t *log_handle = malloc(sizeof(log_t));

    if (log_handle &&
        (log_handle->log_fp=fopen(filepath, mode)) &&
        (log_handle->filepath=malloc(path_strlen+1))) {
        
        strncpy(log_handle->filepath, filepath, path_strlen);
        log_handle->filepath[path_strlen] = '\0';

        time_t rawtime;
        time(&rawtime);
        fprintf(log_handle->log_fp, "[%f seconds]: %s opened on %s", (float)clock()/CLOCKS_PER_SEC, log_handle->filepath, asctime(localtime(&rawtime)));
        success = 1;
    }
    else
        log_handle = NULL;

    return log_handle;
}

void log__close(const log_t *log_handle)
{
    if (log_handle) {
        time_t rawtime;
        time(&rawtime);
        fprintf(log_handle->log_fp, "[%f seconds]: %s closed on %s", (float)clock()/CLOCKS_PER_SEC, log_handle->filepath, asctime(localtime(&rawtime)));
        
        fclose(log_handle->log_fp);
    }
}

void log__delete(log_t *log_handle)
{
    if (log_handle)
        free(log_handle);
}

int log__read(const log_t *log_handle, char *buffer, const size_t buffer_size)
{
    int success = 0;
    const size_t file_size = get_file_size(log_handle->log_fp);

    /**
     * TODO: check file mode
     */
    if (log_handle && buffer_size >= file_size)
        success = fread(buffer, sizeof(char), file_size, log_handle->log_fp);

    return success;
}

int log__write(log_t *log_handle, const log_level_t log_level, const char *format, ...)
{
    int success = 0;

    if (log_handle) {

        va_list args;
        va_start(args, format);

        fprintf(log_handle->log_fp, "[%f seconds]%s: ", (float)clock()/CLOCKS_PER_SEC, log_level_str[log_level]);
        vfprintf(log_handle->log_fp, format, args);
        fprintf(log_handle->log_fp, "\n");
        success = 1;

        va_end(args);
    }

    return success;
}

size_t get_file_size(FILE *fp)
{
    size_t size;

    fseek(fp, 0, SEEK_END);
    size = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}
