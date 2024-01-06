#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ordering/heap_sort.h"
#include "ordering/insert_sort.h"
#include "ordering/shell_sort.h"

void print_arr(int *arr, size_t len);
void gen_arr(int *arr, size_t len);
void test_sort(
    int *arr,
    int *safe,
    int *cmp,
    size_t len,
    void (*sort)(int *arr, size_t len),
    char *name
);

int ord(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main(void) {
    const size_t len = 1000000;
    int *safe = malloc(sizeof(*safe) * len);
    int *arr = malloc(sizeof(*safe) * len);
    int *cmp = malloc(sizeof(*safe) * len);

    if (!arr || !safe || !cmp) {
        free(arr);
        free(safe);
        free(cmp);
        printf("Failed to allocate\n");
        return EXIT_FAILURE;
    }

    gen_arr(safe, len);
    memcpy(cmp, safe, len * sizeof(*safe));
    qsort(cmp, len, sizeof(*cmp), ord);

    test_sort(arr, safe, cmp, len, heap_sort, "heap");
    test_sort(arr, safe, cmp, len, shell_sort, "shell");
    test_sort(arr, safe, cmp, len, insert_sort, "insert");

    free(safe);
    free(arr);
    free(cmp);
}

void print_arr(int *arr, size_t len) {
    while (len--) {
        printf("%d ", *arr++);
    }
    printf("\n");
}

void gen_arr(int *arr, size_t len) {
    srand(time(NULL));
    while (len--) {
        *arr++ = rand();
    }
}

void test_sort(
    int *arr,
    int *safe,
    int *cmp,
    size_t len,
    void (*sort)(int *arr, size_t len),
    char *name
) {
    memcpy(arr, safe, len * sizeof(*safe));
    printf("%s: ", name);
    time_t start = clock();
    sort(arr, len);
    time_t end = clock();
    printf("%lf s", (double)(end - start) / CLOCKS_PER_SEC);

    for (size_t i = 0; i < len; ++i) {
        if (cmp[i] != arr[i]) {
            printf(" failed\n");
            return;
        }
    }
    printf("\n");
}
