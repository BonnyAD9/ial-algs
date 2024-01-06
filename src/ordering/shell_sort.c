#include "shell_sort.h"

void stepped_insert_sort(int *arr, size_t len, size_t step);

void shell_sort(int *arr, size_t len) {
    // this loop should compile to ~2 instructions in x86 with optimizatoins
    // enabled
    size_t ms = ~0;
    while (ms > len) {
        ms >>= 1;
    }

    for (size_t step = ms; step > 0; step >>= 1) {
        for (size_t i = 0; i < step; ++i) {
            stepped_insert_sort(arr + i, len - i, step);
        }
    }
}

// insert sort that sorts only every nth element (given in `step`)
void stepped_insert_sort(int *arr, size_t len, size_t step) {
    for (size_t i = step; i < len; i += step) {
        int itm = arr[i];
        size_t j = i - step;
        for (; j < len; j -= step) {
            if (arr[j] <= itm) {
                break;
            }
            arr[j + step] = arr[j];
        }
        arr[j + step] = itm;
    }
}
