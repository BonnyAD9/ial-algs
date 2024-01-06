#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ordering/heap_sort.h"
#include "ordering/insert_sort.h"
#include "ordering/shell_sort.h"
#include "ordering/sequence_merge_sort.h"

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

int main2(void) {
    int arr[] = { 5, 7, 8, 6, 4, 9, 2, 3, 1, 0 };
    const int len = sizeof(arr) / sizeof(*arr);

    print_arr(arr, len);
    sequence_merge_sort(arr, len);
    print_arr(arr, len);
}

void cqsort(int *arr, size_t len) {
    qsort(arr, len, sizeof(*arr), ord);
}

int main(void) {
    //return main2();

    const size_t len = 1000000000;
    int *safe = malloc(sizeof(*safe) * len);
    int *arr = malloc(sizeof(*safe) * len);
    int *cmp = NULL; //malloc(sizeof(*safe) * len);

    if (!arr || !safe) {
        free(arr);
        free(safe);
        free(cmp);
        printf("Failed to allocate\n");
        return EXIT_FAILURE;
    }

    printf("Generating random numbers... ");
    fflush(stdout);
    time_t start = clock();
    gen_arr(safe, len);
    double secs = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Done! in %lf\n", secs);

    /*
    printf("Creating copy... ");
    fflush(stdout);
    start = clock();
    memcpy(cmp, safe, len * sizeof(*safe));
    secs = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Done! in %lf\n", secs);

    printf("Soring to check correctness... ");
    fflush(stdout);
    start = clock();
    qsort(cmp, len, sizeof(*cmp), ord);
    secs = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Done! in %lf\n", secs);
    */


    test_sort(arr, safe, cmp, len, cqsort, "C qsort");
    printf("\n");
    test_sort(
        arr,
        safe,
        cmp,
        len,
        (void (*)(int *, size_t))sequence_merge_sort,
        "sequence merge"
    );
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
    printf("%s\n", name);
    for (size_t size = 1; size <= len; size *= 10) {
        memcpy(arr, safe, size * sizeof(*safe));
        printf("  %zu: ", size);
        fflush(stdout);

        time_t start = clock();
        sort(arr, size);
        time_t end = clock();
        double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%lf s", secs);

        if (cmp) {
            for (size_t i = 0; i < size; ++i) {
                if (cmp[i] != arr[i]) {
                    printf(" failed\n");
                    return;
                }
            }
        }
        printf("\n");

        if (secs > 10) {
            break;
        }
    }
}
