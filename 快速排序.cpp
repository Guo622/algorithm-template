#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>

void sort(int a[], int low, int high)
{
	int i = low, j = high, key = a[low], t;
	if (low >= high)
		return;
	while (i != j)
	{
		while (a[j] >= key && i < j)
			j--;
		while (a[i] <= key && i < j)
			i++;
		if (i < j)
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	a[low] = a[i];
	a[i] = key;
	sort(a, low, i - 1);
	sort(a, i + 1, high);
}
int main()
{
	int n, d, a[1000001], i, j, t, count = 0;
	scanf("%d%d", &n, &d);
	for (i = 0; i < n; i++)
		scanf("%d", a + i);
	sort(a, 0, n - 1);
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n && (a[j] - a[i]) <= d; j++)
			count++;
	printf("%d", count);
	return 0;
}

//更牛的
void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
int partition(int a[], int left, int right)
{
	int i, last;						/*last为左边部分最后一个元素的位置*/
	int split = (left + right) / 2;		/*选择中间元素作为切分元素 */
	swap(a, left, split);				/* 移切分元素到最左边位置 */
	last = left;						/* 初始化last */
	for (i = left + 1; i <= right; i++) /* 分区：从左至右扫描 */
		if (a[i] < a[left])				/* 小的数移到左边*/
			swap(a, ++last, i);
	swap(a, left, last); /* 将切分元素移到两部分之间*/
	return last;
}
void QuickSort(int a[], int left, int right)
{
	int split;		  /* 分区位置 */
	if (left < right) /* 待排序数组的元素个数至少为2 */
	{
		split = partition(a, left, right); /* 将数组元素分成两部分*/
		QuickSort(a, left, split - 1);	   /* 对左边部分递归排序 */
		QuickSort(a, split + 1, right);	   /* 对右边部分递归排序 */
	}
}

//更简洁的二分
void quicksort(int left, int right)
{
	if (left >= right)
		return;
	int i = left, j = right, mid = i + j >> 1, key = a[mid], t;
	while (i <= j)
	{
		while (a[j] > key)			j--;
		while (a[i] < key)			i++;
		if (i <= j)
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	}
	quicksort(left, j);
	quicksort(i, right);
}

int randPartition(int A[], int left, int right) {
	int p = (round(1.0 * rand() / RAND_MAX * (right - left) + left));
	swap(A[p], A[left]);
	int temp = A[left];
	while (left < right) {
		while (left<right && A[right]>temp)	right--;
		A[left] = a[right];
		while (left < right && a[left] <= temp)	left++;
		A[right] = a[left];
	}
	a[left] = temp;
	return left;
}