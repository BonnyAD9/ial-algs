#include "brent.h"

#include <stdlib.h>
#include <string.h>

#include "../hash.h"
#include "../fail.h"
#include "../primes.h"

TBrent tb_new(size_t size) {
    size = get_prime(size);
    TBrent res = {
        .items = calloc(size, sizeof(*res.items)),
        .size = size,
    };

    if (!res.items) {
        error("Failed to allocate");
        return (TBrent) {};
    }

    return res;
}

int *tb_get(TBrent *tb, Str key) {
    size_t hash = djb_hash(key.data, key.len);
    size_t pos = hash % tb->size;

    TBItem *first = tb->items + pos;
    if (!first->key.data) {
        return NULL;
    }

    if (str_eq(STR(first->key), key) == 0) {
        return &first->value;
    }

    size_t step = hash % (tb->size - 1) + 1;
    TBItem *end = tb->items + tb->size;
    TBItem *item = first;

    while (1) {
        item += step;
        if (item >= end) {
            item -= tb->size;
        }

        if (item == first || !item->key.data) {
            return NULL;
        }

        if (str_eq(STR(item->key), key)) {
            return &item->value;
        }
    }
}

int *tb_set(TBrent *tb, Str key, int value) {
    size_t hash = djb_hash(key.data, key.len);
    size_t pos = hash % tb->size;

    TBItem *first = tb->items + pos;
    if (!first->key.data) {
        first->key = STRING(key);
        first->value = value;
        return &first->value;
    }

    if (str_eq(STR(first->key), key) == 0) {
        first->value = value;
        return &first->value;
    }

    size_t step = hash % (tb->size - 1) + 1;
    TBItem *end = tb->items + tb->size;
    TBItem *item = first;

    while (1) {
        item += step;
        if (item >= end) {
            item -= tb->size;
        }

        if (item == first) {
            // The table is full
            return NULL;
        }

        if (!item->key.data) {
            break;
        }

        if (str_eq(STR(item->key), key)) {
            item->value = value;
            return &item->value;
        }
    }

    // TODO
}
