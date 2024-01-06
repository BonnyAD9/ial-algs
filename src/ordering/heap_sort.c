#include "heap_sort.h"

void shift(int *arr, size_t len, size_t root);

void heap_sort(int *arr, size_t len) {
    if (len < 2) {
        return;
    }

    // establish heap
    for (int i = len / 2; i < len; --i) {
        shift(arr, len, i);
    }

    // sort the array
    while (--len) {
        int h = arr[0];
        arr[0] = arr[len];
        arr[len] = h;

        shift(arr, len, 0);
    }
}

// fixes heap in `arr` with incorrect node at `arr[root]`
// it is a O(log n) operation
void shift(int *arr, size_t len, size_t root) {
    size_t child = root * 2 + 1;

    int r = arr[root];
    while (child < len) {
        int c = arr[child];

        if (child + 1 == len) {
            // the only child
            if (r < c) {
                arr[root] = c;
                root = child;
            }
            break;
        }

        // find the larger child
        int c2 = arr[child + 1];
        if (c2 > c) {
            c = c2;
            ++child;
        }

        if (r >= c) {
            // the node is sorted
            break;
        }

        arr[root] = c;
        root = child;
        child = root * 2 + 1;
        continue;
    }

    arr[root] = r;
}
