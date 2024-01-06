#include <stdio.h>

#include "ordering/heap_sort.h"

void print_arr(int *arr, size_t len);

int main(void) {
    int arr[] = { 5, 9, 4, 8, 6, 7, 2, 0, 1, 3 };
    const int len = sizeof(arr) / sizeof(*arr);

    print_arr(arr, len);
    heap_sort(arr, len);
    print_arr(arr, len);
}

void print_arr(int *arr, size_t len) {
    while (len--) {
        printf("%d ", *arr++);
    }
    printf("\n");
}
