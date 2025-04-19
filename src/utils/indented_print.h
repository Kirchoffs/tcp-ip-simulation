#ifndef INDENT_PRINT_H
#define INDENT_PRINT_H

#include <stdio.h>
#include <stdarg.h>

void indented_printf(int indent, const char *format, ...) {
    for (int i = 0; i < indent; i++) {
        putchar(' ');
    }

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#endif
