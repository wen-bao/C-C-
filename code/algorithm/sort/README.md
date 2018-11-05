# sort

## 实现常用排序算法

```c++
template <typename T>
void bubbleSort(T *arr, int lo, int hi);
//冒泡排序，相邻元素交换，最好n，最坏n^2
void selectSort(T *arr, int lo, int hi);
//选择排序，每次选取最小（大）元素，交换，n^2
void insertSort(T *arr, int lo, int hi);
//插入排序，从右向左依次插入，最好n，最坏n^2
void shellSort(T *arr, int lo, int hi);
//希尔排序，插入排序的优化，克服插入排序处理均匀分布数据的弱点，使数据堆积，nlong(n)
void mergeSort(T *arr, int lo, int hi);
//归并排序，对半划分子问题，排序，合并，需要额为空间，nlog(n)
void quickSort(T *arr, int lo, int hi);
//快速排序，找到关键数（随机化）进行划分，确定关键数最终位置，对子序列进行排序，递归次数过多(虽然可以非递归实现，但是为了简洁，通常递归实现)，nlong(n)
void heapSort(T *arr, int lo, int hi);
//堆排序，利用二叉树性质，建立大根堆（小根堆），经过交换，再平衡，nlong(n)
void sort(T *arr, int lo, int hi);
//借鉴STL sort，划分，数据少插入排序，数据多快排，递归层数多换堆排序（只实现九牛一毛）
```