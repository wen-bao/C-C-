#ifndef _SORT_H_
#define _SORT_H_

#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

//bubbleSort
//selectSort
//insertSort
//shellSort
//mergeSort
//quickSort
//heapSort
//sort

namespace MyAlg {

#define INSERTLIMIT 16
#define HEAPLIMIT 1e6

//swap
template <typename T>
inline void swap(T &a, T &b) {
    T temp;
    temp = a, a = b, b = temp;
}

// bubbleSort
template <typename T>
inline void bubbleSort(T &arr, int lo, int hi) {
    int size = sizeof(arr) / sizeof(arr[0]);
    assert(lo >= 0 && hi <= size && lo < hi);

    bool sorted = false;
    while (!sorted) {
        sorted = true;

        for (int i = lo + 1; i < hi; ++i) {
            if (arr[i - 1] > arr[i]) {
                sorted = false;
                swap(arr[i - 1], arr[i]);
            }
        }

        if (sorted) {
            break;
        }
    }
}

// selectSort
template <typename T>
inline void selectSort(T *arr, int lo, int hi) {
    assert(lo >= 0 && lo < hi);

    for (int i = lo; i < hi - 1; ++i) {
        T mi = arr[i];
        int index = i;
        for (int j = i + 1; j < hi; ++j) {
            if (mi > arr[j]) {
                mi = arr[j];
                index = j;
            }
        }

        swap(arr[index], arr[i]);
    }
}

// insertSort
template <typename T>
inline void insertSort(T *arr, int lo, int hi) {
    assert(lo >= 0 && lo < hi);

    for (int i = lo + 1; i < hi; ++i) {
        for (int j = i; j > lo; --j) {
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
inline void shellSort(T *arr, int lo, int hi) {
    assert(lo >= 0 && lo < hi);

    for (int i = ((hi - lo) / 2 + 1); i > 0; i /= 2) {
        for (int j = lo; j + i < hi; ++j) {
            if (arr[j] > arr[j + i]) {
                swap(arr[j], arr[j + i]);
            }
        }
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
inline void mergeSort(T *arr, int lo, int hi) {
    assert(lo >= 0 && lo < hi);

    if (1 < (hi - lo)) {
        int mid = (lo + hi) >> 1;
        mergeSort(arr, lo, mid);
        mergeSort(arr, mid, hi);
        merg(arr, lo, mid, hi);
    }
}

// quickSort
template <typename T>
inline void quickSort(T *arr, int lo, int hi) {
    if (lo >= hi || lo + 1 == hi) return;

    srand(static_cast<unsigned int>(time(NULL)));
    int index = rand() % (hi - lo) + lo;

    T aim = arr[index];
    swap(arr[lo], arr[index]);
    int l = lo, r = hi - 1;

    while (l < r) {
        while (l < r && arr[r] > aim) r--;
        arr[l] = arr[r];
        while (l < r) {
            if(arr[l] > aim) {
                break;
            } else {
                l++;
            }
        }
        arr[r] = arr[l];
    }

    arr[l] = aim;
    quickSort(arr, lo, l);
    quickSort(arr, l + 1, hi);
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
inline void heapSort(T *arr, int lo, int hi) {
    buildHeap(arr, lo, hi - lo);

    for (int i = hi - lo; i > 0; --i) {
        swap(arr[lo], arr[lo + i - 1]);
        update(arr, lo, 1, i - 1);
    }
}

// sort
template <typename T>
void sort(T *arr, int lo, int hi) {
    if (hi - lo <= INSERTLIMIT) {
        insertSort(arr, lo, hi);
    } else if (hi - lo >= HEAPLIMIT) {
        heapSort(arr, lo, hi);
    } else {
        quickSort(arr, lo, hi);
    }
}

}  // namespace MyAlg

#endif  //!_SORT_H_