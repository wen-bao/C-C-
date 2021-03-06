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

## 更新

实现了桶排序(backetsort)，将数据按照一定的划分（通过除以某个值归一化）放入事先固定大小的桶中，在每个桶中再排序（插入排序），适用于分布均匀的数据，这样可以使得每个桶中的数据均匀，避免堆积。其中充满哲学的是桶的大小和除以的值的选择，类似hash算法中如何设计“完美哈希”

稳定排序

在处理大量数据的时候往往可以利用桶排序的思想解决，例如在10G个数字中找出中位数，内存限制2G

```c++
void bucketsort(int *arr, int size, int numOfbucket);
```

类似基数排序、桶排序等都不是基于比较的排序算法（这里说法不太严谨，桶排序内部排序是基于比较的）所以复杂度很迷。

刚刚接触STL的时候很郁闷，为什么sort中没有使用性能优良的基数排序，原因正是因为它不是基于比较的。实际应用中需要排序的往往不单单是数值的排序，还有字符串、结构体等等的排序，而基于比较的排序只要给出 > （或者<，与实现排序的使用符号有关）的定义（重载）就可以排序