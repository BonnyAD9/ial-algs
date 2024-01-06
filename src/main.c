#include <stdio.h>
#include <string.h>

#include "ordering/heap_sort.h"
#include "ordering/insert_sort.h"

void print_arr(int *arr, size_t len);

int main(void) {
    int safe[] = { 5, 9, 4, 8, 6, 7, 2, 0, 1, 3 };
    const int len = sizeof(safe) / sizeof(*safe);
    int arr[len];

    print_arr(safe, len);

    memcpy(arr, safe, len * sizeof(*safe));
    printf("heap: \n");
    heap_sort(arr, len);
    print_arr(arr, len);

    memcpy(arr, safe, len * sizeof(*safe));
    printf("insert: \n");
    insert_sort(arr, len);
    print_arr(arr, len);
}

void print_arr(int *arr, size_t len) {
    while (len--) {
        printf("%d ", *arr++);
    }
    printf("\n");
}
