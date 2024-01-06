#include "str.h"

#include <string.h>
#include <stdlib.h>

bool str_eq(Str a, Str b) {
    if (a.len != b.len) {
        return false;
    }

    if (a.data == b.data) {
        return true;
    }

    while (a.len--) {
        if (*a.data++ != *b.data++) {
            return false;
        }
    }
    return true;
}

String str_clone(Str s) {
    String res = {
        .allocated = s.len,
        .len = s.len,
        .data = malloc(s.len + 1),
    };

    if (!res.data) {
        return (String) {};
    }

    memcpy(res.data, s.data, s.len);
    res.data[res.len] = 0;
    return res;
}

void str_free(String *s) {
    free(s->data);
    *s = (String) {};
}
