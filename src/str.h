#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Creates `Str` from one of:
// - string literal
// - null terminated c string
// - Str
// - Str *
// - String
// - String -
#define STR(str) (_Generic(str, \
    char *: sizeof(str) == sizeof(char *) \
        ? _cstr(&str) \
        : _str_lit(&str, sizeof(str) - 1), \
    String: _str_ing(&str), \
    String *: _pstr_ing(&str), \
    Str: _str(&str), \
    Str *: _pstr(&str) \
))

// Copies into new `String` from one of:
// - string literal
// - null terminated c string
// - Str
// - Str *
// - String
// - String -
#define STRING(str) str_clone(STR(str))

typedef struct {
    char *data;
    size_t len;
} Str;

typedef struct {
    char *data;
    size_t len;
    size_t allocated;
} String;

static inline Str _str_lit(void *lit, size_t size) {
    return (Str) { .data = lit, .len = size };
}

static inline Str _str_ing(void *string) {
    String *str = string;
    return (Str) { .data = str->data, .len = str->len };
}

static inline Str _str(void *str) {
    return *(Str*)str;
}

static inline Str _pstr(void *str) {
    return **(Str**)str;
}

static inline Str _pstr_ing(void *string) {
    String *str = *(String**)string;
    return (Str) { .data = str->data, .len = str->len };
}

static inline Str _cstr(void *str) {
    char *s = *(char**)str;
    return (Str) { .data = s, .len = strlen(s) };
}

bool str_eq(Str a, Str b);

String str_clone(Str s);

void str_free(String *s);

#endif // STR_H_INCLUDED
