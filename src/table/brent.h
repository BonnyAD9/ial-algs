#ifndef TABLE_STATIC_BRENT_H_INCLUDED
#define TABLE_STATIC_BRENT_H_INCLUDED

#include <stddef.h>

#include "../str.h"

typedef struct {
    String key;
    int value;
} TBItem;

/// Brent hash table
/// static size flat hash table with implicitly chained items using double hash
/// functions and item reconfiguration when inserting for better search
/// performance
///
/// Pros:
/// - Fast search for existing items
/// - Is flat
/// - Unlimited number of conflicts (limited only by table size)
///
/// Cons:
/// - Limited number of items before resize
/// - Slow insert
/// - Slowish search for non existing items
/// - Very slow delete
/// - Starts to get very slow when it is filled with more than 70%
/// - Very slow resize
/// - Has to have prime size
/// - Complicated to implement
typedef struct {
    size_t size;
    TBItem *items;
} TBrent;

TBrent tb_new(size_t size);

int *tb_get(TBrent *tb, Str key);

int *tb_set(TBrent *tb, Str key, int value);

#endif // TABLE_STATIC_BRENT_H_INCLUDED
