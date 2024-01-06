#ifndef ORDERING_SHELL_SORT_H_INCLUDED
#define ORDERING_SHELL_SORT_H_INCLUDED

#include <stddef.h>

// time:    O(n^(3/2))
// space:   O(1)
// stable:  no
// natural: yes
void shell_sort(int *arr, size_t len);

#endif // ORDERING_SHELL_SORT_H_INCLUDED
