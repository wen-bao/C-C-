#ifndef _SORT_H_
#define _SORT_H_

#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

// bubbleSort
// selectSort
// insertSort
// shellSort
// mergeSort
// quickSort
// heapSort
// radixSort
// sort

namespace MyAlg {

#define INSERTLIMIT 16
#define HEAPLIMIT 1e6

// swap
template <typename T>
inline void swap(T &a, T &b) {
    T temp;
    temp = a, a = b, b = temp;
}

// bubbleSort
template <typename T>
inline void bubbleSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        for (int i = 1; i < len; ++i) {
            int pos = lo + i;
            if (arr[pos - 1] > arr[pos]) {
                sorted = false;
                swap(arr[pos - 1], arr[pos]);
            }
        }

        if (sorted) {
            break;
        }
    }
}

// selectSort
template <typename T>
inline void selectSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    for (int i = 0; i < len - 1; ++i) {
        int posi = lo + i;
        for (int j = i + 1; j < len; ++j) {
            int posj = lo + j;
            if (arr[posi] > arr[posj]) {
                swap(arr[posi], arr[posj]);
            }
        }
    }
}

// insertSort
template <typename T>
inline void insertSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    for (int i = 1; i < len; ++i) {
        int posi = lo + i;
        for (int j = posi; j > lo; --j) {
            if (arr[j - 1] > arr[j]) {
                swap(arr[j - 1], arr[j]);
            } else {
                break;
            }
        }
    }
}

// shellSort
template <typename T>
inline void shellSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    int h = 1;

    while (h < (len / 3)) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (int i = h; i < len; ++i) {
            for (int j = i; j >= h && arr[lo + j - h] > arr[lo + j]; j -= h) {
                swap(arr[lo + j], arr[lo + j - h]);
            }
        }

        h = h / 3;
    }
}

// mergSort
template <typename T>
inline void merg(T *arr, int lo, int mid, int hi) {
    assert(lo >= 0 && lo < mid && mid < hi);

    T *tmp = new T[hi - lo];

    int llen = mid - lo, rlen = hi - mid;

    int li = 0, ri = 0, index = 0;
    while ((li < llen) && (ri < rlen)) {
        if (arr[lo + li] > arr[mid + ri]) {
            tmp[index++] = arr[mid + ri++];
        } else {
            tmp[index++] = arr[lo + li++];
        }
    }

    while (li < llen) {
        tmp[index++] = arr[lo + li++];
    }

    while (ri < rlen) {
        tmp[index++] = arr[mid + ri++];
    }

    for (int i = lo; i < hi; ++i) {
        arr[i] = tmp[i - lo];
    }

    delete[] tmp;
}

template <typename T>
inline void mergeSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    if (1 < len) {
        int mid = len >> 1;
        mergeSort(arr, lo, mid);
        mergeSort(arr, lo + mid, len - mid);
        merg(arr, lo, lo + mid, lo + len);
    }
}

// quickSort
template <typename T>
inline void quickSort(T &arr, int lo, int len) {
    if(len <= 1) return;

    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    srand(static_cast<unsigned int>(time(NULL)));
    int index = rand() % len + lo;

    swap(arr[lo], arr[index]);
    int l = lo, r = lo + len - 1;

    while (l < r) {
        while (l < r && arr[r] > arr[lo]) r--;
        while(l < r) {
            if(arr[l] > arr[lo]) {
                break;
            } else {
                l ++;
            }
        }
        if(l !=  r) {
            swap(arr[l], arr[r]);
        }
    }
    if(l != lo) {
        swap(arr[lo], arr[l]);
    }

    quickSort(arr, lo, l - lo);
    quickSort(arr, l + 1, len - (l - lo) - 1);
}

// heapSort
template <typename T>
inline void update(T *arr, int lo, int no, int n) {
    int mano = no, ln = (no << 1), rn = (no << 1 | 1);

    if (ln <= n) {
        mano = (arr[ln + lo - 1] > arr[mano + lo - 1] ? ln : mano);
    }
    if (rn <= n) {
        mano = (arr[rn + lo - 1] > arr[mano + lo - 1] ? rn : mano);
    }

    if (mano != no) {
        swap(arr[no + lo - 1], arr[mano + lo - 1]);
        update(arr, lo, mano, n);
    }
}

template <typename T>
inline void buildHeap(T *arr, int lo, int n) {
    int len = n / 2;

    for (int no = len; no > 0; --no) {
        update(arr, lo, no, n);
    }
}

template <typename T>
inline void heapSort(T &arr, int lo, int len) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && lo + len <= size);

    buildHeap(arr, lo, len);

    for (int i = len; i > 0; --i) {
        swap(arr[lo], arr[lo + i - 1]);
        update(arr, lo, 1, i - 1);
    }
}

// sort
template <typename T>
void sort(T &arr, int lo, int len) {
    if (len <= INSERTLIMIT) {
        insertSort(arr, lo, len);
    } else if (len >= HEAPLIMIT) {
        heapSort(arr, lo, len);
    } else {
        quickSort(arr, lo, len);
    }
}

// radixSort
int maxBit(int *arr, int lo, int hi) {
    int ma = arr[lo];
    for (int i = lo + 1; i < hi; ++i) {
        ma = (arr[i] > ma ? arr[i] : ma);
    }

    int d = 1, p = 10;
    while (ma >= p) {
        ma /= p;
        ++d;
    }
    return d;
}

void radixSort(int *arr, int lo, int len) {
    int d = maxBit(arr, lo, lo + len);

    int *tmp = new int[len];
    int *count = new int[10];
    int radix = 1;

    for (int i = 1; i <= d; ++i) {
        for (int j = 0; j < 10; ++j) {
            count[j] = 0;
        }
        for (int j = 0; j < len; ++j) {
            int k = (arr[lo + j] / radix) % 10;
            count[k]++;
        }
        //cool begin
        for (int j = 1; j < 10; ++j) {
            count[j] = count[j - 1] + count[j];
        }
        for (int j = len - 1; j >= 0; --j) {
            int k = (arr[lo + j] / radix) % 10;
            tmp[count[k] - 1] = arr[lo + j];
            count[k]--;
        }
        //cool end
        for (int j = 0; j < len; ++j) {
            arr[lo + j] = tmp[j];
        }
        radix *= 10;
    }

    delete[] tmp;
    delete[] count;
}

}  // namespace MyAlg

#endif  //!_SORT_H_