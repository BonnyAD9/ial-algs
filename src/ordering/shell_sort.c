#include "shell_sort.h"

void shell_sort(int *arr, size_t len) {
    for (size_t step = len / 2; step > 0; step /= 2) {
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
