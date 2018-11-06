# sort

## 实现常用排序算法

```c++
template <typename T>
void bubbleSort(T *arr, int lo, int len);
//冒泡排序，相邻元素交换，最好o(n)，最坏O(n^2)
void selectSort(T *arr, int lo, int len);
//选择排序，每次选取最小（大）元素，交换，O(n^2)
void insertSort(T *arr, int lo, int len);
//插入排序，从右向左依次插入，最好O(n)，最坏O(n^2)
void shellSort(T *arr, int lo, int len);
//希尔排序，插入排序的优化，克服插入排序处理均匀分布数据的弱点，按照指定长度分组，使数据堆积，O(n^(1.3—2))
void mergeSort(T *arr, int lo, int len);
//归并排序，对半划分子问题，排序，合并，需要额外空间，O(nlog(n))
void quickSort(T *arr, int lo, int len);
//快速排序，找到关键数（随机化）进行划分，确定关键数最终位置，对子序列进行排序，递归次数过多(虽然可以非递归实现，但是为了简洁，通常递归实现)，O(nlong(n))(n)
void heapSort(T *arr, int lo, int len);
//堆排序，利用二叉树性质，建立大根堆（小根堆），经过交换，再平衡，O(nlong(n))
void radixSort(int *arr, int lo, int len);
//基数排序，从低位到高位进行排序，需要额外空间，O(kn)k表示最大数字位数
void sort(T *arr, int lo, int len);
//借鉴STL sort，划分，数据少插入排序，数据多快排，递归层数多换堆排序（只实现九牛一毛）
```

## 总结

冒泡、插入、归并、基数是稳定的
选择、希尔、快排、堆是不稳定的

## 其他

各种算法都有各自的利弊，目前没有一种算法在任何情况下都是最优的，所以寻找更好的算法这个行动一直在继续。。。

实现以上算法的过程中，最让我欣喜的是基数排序，排序效率暂且不谈，但是里面的思想很棒，推荐细读源码