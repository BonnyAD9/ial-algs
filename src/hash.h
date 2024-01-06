#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stddef.h>

static inline size_t djb_hash(char *data, size_t len) {
    size_t hash = 5381;
    if (len) {
        while (len--) {
            hash = ((hash << 5) + hash) + *data++;
        }
    } else {
        do {
            hash = ((hash << 5) + hash) + *data;
        } while (*++data);
    }
    return hash;
}

#endif // HASH_H_INCLUDED
