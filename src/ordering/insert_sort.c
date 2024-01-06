#include "insert_sort.h"

void insert_sort(int *arr, size_t len) {
    for (size_t i = 1; i < len; ++i) {
        int itm = arr[i];
        size_t j = i - 1;
        for (; j < len; --j) {
            if (arr[j] <= itm) {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = itm;
    }
}
