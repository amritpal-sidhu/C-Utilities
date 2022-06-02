#include "logging.h"

#include <stdarg.h>
#include <string.h>
#include <time.h>


FILE *log_fp;
static char current_filepath[128];


int logging__open(const char *filepath, const char *mode)
{
    int success = 0;

    if (log_fp=fopen(filepath, mode)) {
        strcpy(current_filepath, filepath);
        success = 1;
    }

    return success;
}

void logging__close(void)
{
    current_filepath[0] = '\0';
    fclose(log_fp);
}

int logging__delete(void)
{
    int success = 0;

    if (log_fp && !remove(current_filepath))
        success = 1;

    return success;
}

int logging__read(char *buffer, const size_t buffer_size)
{
    int success = 0;
    const size_t file_size = get_file_size(log_fp);

    /**
     * TODO: check file mode
     */
    if (buffer_size >= file_size)
        success = fread(buffer, sizeof(char), file_size, log_fp);

    return success;
}

int logging__write(const log_level_t log_level, const char *formatted_string, ...)
{
    int success = 0;

    if (log_fp) {

        va_list vl;
        va_start(vl, formatted_string);

        switch (log_level) {

            case NONE:
                fprintf(log_fp, "[%f seconds]: ", (float)clock()/CLOCKS_PER_SEC);
                fprintf(log_fp, formatted_string, vl);
                fprintf(log_fp, "\n");
                success = 1;
                break;
            
            case STATUS:
                fprintf(log_fp, "[%f seconds] STATUS: ", (float)clock()/CLOCKS_PER_SEC);
                fprintf(log_fp, formatted_string, vl);
                fprintf(log_fp, "\n");
                success = 1;
                break;

            case DEBUG:
                fprintf(log_fp, "[%f seconds] DEBUG: ", (float)clock()/CLOCKS_PER_SEC);
                fprintf(log_fp, formatted_string, vl);
                fprintf(log_fp, "\n");
                success = 1;
                break;

            case WARNING:
                fprintf(log_fp, "[%f seconds] WARNING: ", (float)clock()/CLOCKS_PER_SEC);
                fprintf(log_fp, formatted_string, vl);
                fprintf(log_fp, "\n");
                success = 1;
                break;

            case ERROR:
                fprintf(log_fp, "[%f seconds] ERROR: ", (float)clock()/CLOCKS_PER_SEC);
                fprintf(log_fp, formatted_string, vl);
                fprintf(log_fp, "\n");
                success = 1;
                break;

            default:
                break;
        }
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
