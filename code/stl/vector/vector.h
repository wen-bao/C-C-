#pragma once
#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace MyStl {

const int DEFAULT_CAPACITY = 5;

template <typename T>
class vector {
   public:
    template <class TT>
    friend std::ostream &operator<<(std::ostream &os, const vector<TT> &v);

   public:
    // Constructor and Destructor
    vector(int cap = DEFAULT_CAPACITY, int sz = 0, const T v = T());
    vector(const T *arr, int n) { copyFrom(arr, 0, n); }
    vector(const T *arr, int lo, int hi) { copyFrom(arr, lo, hi); }
    vector(const vector<T> &v) { copyFrom(v.w_data, 0, v.w_size); }
    vector(const vector<T> &v, int lo, int hi) { copyFrom(v.w_data, lo, hi); }
    ~vector() { delete[] w_data; }
    vector<T> &operator=(const vector<T> &v);

    // Read-only function
    int capacity() const { return w_capacity; }
    int size() const { return w_size; }
    bool empty() const { return !w_size; }
    int find(const T &v) const { return find(v, 0, w_size); }
    int find(const T &v, int lo, int hi) const;
    int serach(const T &v) const { return serach(v, 0, w_size); }
    int serach(const T &v, int lo, int hi) const {
        return binSerach(v, lo, hi);
    }
    int disordered() const;

    // Access function
    void push_back(const T &v) { insert(v); }
    void pop_back() { remove(w_size - 1); }
    T &operator[](int r);
    int insert(int r, const T &v);
    int insert(const T &v) { return insert(w_size, v); }
    const T remove(int r);
    int remove(int lo, int hi);
    void clear() { remove(0, w_size); }
    int deduplicate();
    int uniquify() { return uniquify_impl2(); }
    void sort(int lo, int hi);
    void sort() { sort(0, w_size); }

   protected:
    void copyFrom(const T *data, int lo, int hi);
    void expand();
    void shrink();
    void bubbleSort(int lo, int hi);
    void selectSort(int lo, int hi);
    void insertSort(int lo, int hi);
    void mergeSort(int lo, int hi);
    void merge(int lo, int mid, int hi);
    int binSerach(const T &v, int lo, int hi) const;
    int binSerach_impl1(const T &v, int lo, int hi) const;
    int binSerach_impl2(const T &v, int lo, int hi) const;
    int binSerach_impl3(const T &v, int lo, int hi) const;

   private:
    int uniquify_impl2();
    static void swap(T &a, T &b);

   protected:
    int w_capacity;
    int *w_data;
    int w_size;
};

template <class TT>
std::ostream &operator<<(std::ostream &os, const vector<TT> &v) {
    for (int i = 0; i < v.w_size; ++i) {
        os << v.w_data[i] << " ";
    }
    if(v.w_size == 0) {
        os << "Empty!";
    }
    return os;
}

template <typename T>
vector<T>::vector(int cap, int sz, T v) : w_capacity(cap), w_size(sz) {
    w_data = new T[w_capacity];
    for (int i = 0; i < w_size; ++i) {
        w_data[i] = v;
    }
}

template <typename T>
inline vector<T> &vector<T>::operator=(const vector<T> &v) {
    if (w_data == v.w_data) {
        return *this;
    }

    delete[] w_data;
    copyFrom(v, 0, v.w_size);
    return *this;
}

template <typename T>
inline int vector<T>::find(const T &v, int lo, int hi) const {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    while (--hi >= lo) {
        if (v == w_data[hi]) {
            return hi;
        }
    }

    return -1;
}

template <typename T>
inline int vector<T>::disordered() const {
    int count = 0;

    for (int i = 1; i < w_size; ++i) {
        if (w_data[i - 1] > w_data[i]) {
            count++;
        }
    }

    return count;
}

template <typename T>
inline T &vector<T>::operator[](int r) {
    assert(r >= 0 && r < w_size);

    return w_data[r];
}

template <typename T>
inline int vector<T>::insert(int r, const T &v) {
    assert(r >= 0 && r <= w_size);

    expand();

    for (int i = w_size; i > r; --i) {
        w_data[i] = w_data[i + 1];
    }

    w_data[r] = v;
    ++w_size;

    return r;
}

template <typename T>
inline const T vector<T>::remove(int r) {
    assert(r >= 0 && r < w_size);

    T rem = w_data[r];

    remove(r, r + 1);

    return rem;
}

template <typename T>
inline int vector<T>::remove(int lo, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    int remlen = hi - lo;

    for (int i = hi; i < w_size; ++i) {
        w_data[lo++] = w_data[i];
    }

    w_size -= remlen;
    shrink();

    return remlen;
}

template <typename T>
inline int vector<T>::deduplicate() {
    int old_size = w_size;

    for (int i = 1; i < size();) {
        if (find(w_data[i], 0, i) != -1) {
            remove(i);
        } else {
            ++i;
        }
    }

    return old_size - w_size;
}

template <typename T>
inline void vector<T>::sort(int lo, int hi) {
    srand(static_cast<unsigned int>(time(nullptr)));

    switch (rand() % 4) {
        case 0:
            bubbleSort(lo, hi);
            break;
        case 1:
            selectSort(lo, hi);
            break;
        case 2:
            insertSort(lo, hi);
            break;
        case 3:
        default:
            mergeSort(lo, hi);
            break;
    }
}

template <typename T>
void vector<T>::copyFrom(const T *data, int lo, int hi) {
    w_data = new T[w_capacity = ((hi - lo) << 1)];
    w_size = 0;

    while (lo < hi) {
        w_data[w_size++] = data[lo++];
    }
}

template <typename T>
inline void vector<T>::expand() {
    if (w_size == w_capacity) {
        T *old_data = w_data;

        if (w_capacity < DEFAULT_CAPACITY) {
            w_capacity = DEFAULT_CAPACITY;
        }

        w_data = new T[w_capacity <<= 1];
        copyFrom(old_data, 0, w_size);
        delete[] old_data;
    }
}

template <typename T>
inline void vector<T>::shrink() {
    if (w_size * 5 < w_capacity) {
        T *old_data = w_data;
        w_capacity = (w_capacity / 2 < DEFAULT_CAPACITY ? DEFAULT_CAPACITY
                                                        : w_capacity >> 1);
        w_data = new T[w_capacity];

        for (int i = 0; i < w_size; ++i) {
            w_data[i] = old_data[i];
        }

        delete[] old_data;
    }
}

template <typename T>
inline void vector<T>::bubbleSort(int lo, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (int i = lo + 1; i < hi; ++i) {
            if (w_data[i - 1] > w_data[i]) {
                swap(w_data[i - 1], w_data[i]);
                sorted = false;
            }
        }

        --hi;
    }
}

template <typename T>
inline void vector<T>::selectSort(int lo, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    for (int i = 0; i < w_size - 1; ++i) {
        T mi = w_data[i];
        int index = i;

        for (int j = i + 1; j < w_size; ++j) {
            if (w_data[j] < mi) {
                mi = w_data[j];
                index = j;
            }
        }

        swap(w_data[i], w_data[index]);
    }
}

template <typename T>
inline void vector<T>::insertSort(int lo, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    for (int i = lo + 1; i < hi; ++i) {
        for (int j = i; j > lo; --j) {
            if (w_data[j - 1] > w_data[j]) {
                swap(w_data[j - 1], w_data[j]);
            } else {
                break;
            }
        }
    }
}

template <typename T>
inline void vector<T>::mergeSort(int lo, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    if (1 < (hi - lo)) {
        int mid = (hi + lo) >> 1;
        mergeSort(lo, mid);
        mergeSort(mid, hi);
        merge(lo, mid, hi);
    }
}

template <typename T>
inline void vector<T>::merge(int lo, int mid, int hi) {
    assert(lo >= 0 && hi <= w_size && lo < mid && mid < hi);

    T *l = w_data + lo;
    int llen = mid - lo;
    T *tmp = new T[llen];
    T *r = w_data + mid;
    int rlen = hi - mid;

    for (int i = 0; i < llen; ++i) {
        tmp[i] = l[i];
    }

    int i = 0, j = 0, k = 0;

    while ((j < llen) && (k < rlen)) {
        if (tmp[j] < r[k]) {
            l[i++] = tmp[j++];
        } else {
            l[i++] = r[k++];
        }
    }

    while (j < llen) {
        l[i++] = tmp[j++];
    }

    while (k < rlen) {
        l[i++] = r[k++];
    }

    delete[] tmp;
}

template <typename T>
inline int vector<T>::binSerach(const T &v, int lo, int hi) const {
    srand(static_cast<unsigned int>(time(nullptr)));

    switch (rand() % 2) {
        case 0:
            return binSerach_impl1(v, lo, hi);
            break;
        case 1:
            return binSerach_impl2(v, lo, hi);
            break;
        case 2:
        default:
            return binSerach_impl3(v, lo, hi);
            break;
    }
}

template <typename T>
inline int vector<T>::binSerach_impl1(const T &v, int lo, int hi) const {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    while (lo < hi) {
        int mid = (hi + lo) >> 1;

        if (v == w_data[mid]) {
            return mid;
        } else if (v < w_data[mid]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return -1;
}

template <typename T>
inline int vector<T>::binSerach_impl2(const T &v, int lo, int hi) const {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    while (1 < (hi - lo)) {
        int mid = (hi + lo) >> 1;
        if (v < w_data[mid]) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    return (v == w_data[lo] ? lo : -1);
}

template <typename T>
inline int vector<T>::binSerach_impl3(const T &v, int lo, int hi) const {
    assert(lo >= 0 && hi <= w_size && lo < hi);

    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        (v < w_data[mid]) ? hi = mid : lo = mid + 1;
    }

    return --lo;
}

template <typename T>
inline int vector<T>::uniquify_impl2() {
    int i = 0, j = 0;

    while (++j < w_size) {
        if (w_data[i] != w_data[j]) {
            w_data[++i] = w_data[j];
        }
    }

    w_size = ++i;
    shrink();
    return j - i;
}

template <typename T>
void vector<T>::swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
}  // namespace MyStl

#endif  //! _MYVECTOR_H_