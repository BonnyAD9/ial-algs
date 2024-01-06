#include "fail.h"

#include <stdio.h>
#include <stdarg.h>

void error(char *str, ...) {
    fprintf(stderr, "error: ");

    va_list args;
    va_start(args, str);
    vfprintf(stderr, str, args);
    va_end(args);

    fprintf(stderr, "\n");
}
