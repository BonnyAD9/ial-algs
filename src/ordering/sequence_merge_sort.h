#ifndef ORDERING_SEQUENCE_MERGE_SORT_H_INCLUDED
#define ORDERING_SEQUENCE_MERGE_SORT_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>

// time:    O(n log n)
// space:   O(n)
// stable:  no
// natural: no (it is fast for both ordered and reversed)
bool sequence_merge_sort(int *arr, size_t len);

#endif // ORDERING_SEQUENCE_MERGE_SORT_H_INCLUDED
