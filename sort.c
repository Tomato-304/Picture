#include <stdio.h>
#include <string.h>

#define SIZE 30

void swap(int *px, int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void Adjustdown(int arr[], int parent, int n)
{
    int child = parent * 2 + 1;
    while (child < n)
    {
        if (child + 1 < n && arr[child + 1] > arr[child])
            ++child;

        if (arr[child] > arr[parent])
        {
            swap(&arr[child], &arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void heap_sort(int arr[], int n)
{
    for (int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
        Adjustdown(arr, i, n);
    }

    int end = n - 1;
    while (end > 0)
    {
        swap(&arr[0], &arr[end]);
        Adjustdown(arr, 0, end);
        end--;
    }
}

void select_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[min] > arr[j])
            {
                min = j;
            }
        }

        swap(&arr[i], &arr[min]);
    }
}

void InsertSort(int *a, int n)
{
    // assert(a);

    for (int i = 0; i < n - 1; i++)
    {
        int end = i;
        int x = a[end + 1];
        while (end >= 0)
        {
            if (a[end] > x)
            {
                a[end + 1] = a[end];
                end--;
            }
            else
                break;
        }
        a[end + 1] = x;
    }
}

int Getmid(int *a, int left, int right)
{ // 得到快速排序中比较中间的key，保证快排的速度
    int mid = (left + right) / 2;
    if (a[mid] > a[left])
    {
        if (a[mid] < a[right])
            return mid;
        else if (a[left] > a[right])
            return left;
        else
            return right;
    }
    else // a[right]>a[mid]
    {

        if (a[mid] > a[left])
            return mid;
        else if (a[left] > a[right])
            return right;
        else
            return left;
    }
}

int Partion1(int *a, int left, int right)
{ // 第一种排序，最经典的， hoare版本

    int i = Getmid(a, left, right);
    if (i != left)
        Swap(&a[i], &a[left]);

    int keyi = left;

    while (left < right)
    {
        while (left < right && a[right] >= a[keyi])
            --right;
        while (left < right && a[left] <= a[keyi])
            ++left;
        Swap(&a[left], &a[right]);
    }
    Swap(&a[left], &a[keyi]);

    return left;
}

int Partion2(int *a, int left, int right)
{ // 第二种方法，挖坑法
    int i = Getmid(a, left, right);
    if (i != left)
        Swap(&a[i], &a[left]);

    int key = a[left];
    int pivot = left;

    while (left < right)
    {
        // 右边找小，放到左边的坑里面
        while (left < right && a[right] >= key)
            --right;

        a[pivot] = a[right];
        pivot = right;

        // 左边找大，放到右边的坑里面
        while (left < right && a[left] <= key)
            ++left;

        a[pivot] = a[left];
        pivot = left;
    }

    a[pivot] = key;
    return pivot;
}

int Partion3(int *a, int left, int right)
{ // 前后指针法
    int i = Getmid(a, left, right);
    if (i != left)
        Swap(&a[i], &a[left]);

    int key = left;
    int prev = left;
    int cur = prev + 1;

    while (cur <= right)
    {
        if (a[cur] < a[key] && ++prev != cur)
        {
            Swap(&a[cur], &a[prev]);
        }
        ++cur;
    }

    Swap(&a[prev], &a[key]);
    return prev;
}

void QuickSort(int *a, int left, int right)
{
    if (left >= right)
        return;

    int key = Partion1(a, left, right);

    QuickSort(a, left, key - 1);
    QuickSort(a, key + 1, right);
}

int main()
{
    int a;
    scanf("%d", &a);
    int b[SIZE];
    for (int i = 0; i < a; ++i)
    {
        scanf("%d", &b[i]);
    }
    heap_sort(b, a);
    for (int i = 0; i < a; ++i)
    {
        printf("%d ->", b[i]);
    }
    printf("\n");

    return 0;
}

