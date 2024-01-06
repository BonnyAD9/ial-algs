#include "sequence_merge_sort.h"

#include <string.h>
#include <stdlib.h>

static inline void merge(int **srca, int **srcb, int **dst, int dst_step, int *src, int *dstarr);

bool sequence_merge_sort(int *arr, size_t len) {
    if (len < 2) {
        return true;
    }

    int *help = malloc(sizeof(*arr) * len);
    if (!help) {
        return false;
    }

    // this will be swapped on the start of the first iteration
    int *src = help;
    int *dst = arr;

    bool cont = true;

    while (cont) {
        int *h = src;
        src = dst;
        dst = h;

        int *srca = src;
        int *srcb = src + len - 1;

        int *dsta = dst;
        int *dstb = dst + len - 1;

        cont = false;

        while (srca <= srcb) {
            merge(&srca, &srcb, &dsta, 1, src, dst);
            if (srca > srcb) {
                break;
            }
            cont = true;
            merge(&srca, &srcb, &dstb, -1, src, dst);
        }
    }

    if (dst != arr) {
        memcpy(arr, dst, len * sizeof(*arr));
    }
    free(help);
    return true;
}

void merge(int **srca, int **srcb, int **dst, int dst_step, int *src, int *dstarr) {
    int *sa = *srca;
    int *sb = *srcb;
    int *d = *dst;

    while (sa <= sb) {
        if (*sa <= *sb) {
            *d = *sa;
            ++sa;
            d += dst_step;
            if (sa[-1] > *sa) {
                if (sa > sb) {
                    break;
                }
                do {
                    *d = *sb;
                    d += dst_step;
                    --sb;
                } while (sa < sb && sb[1] < *sb);
                break;
            }
        } else {
            *d = *sb;
            d += dst_step;
            --sb;
            if (sb[1] > *sb) {
                if (sa > sb) {
                    break;
                }
                do {
                    *d = *sa;
                    d += dst_step;
                    ++sa;
                } while (sa < sb && sa[-1] < *sa);
                break;
            }
        }
    }

    *srca = sa;
    *srcb = sb;
    *dst = d;
}
