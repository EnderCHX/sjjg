#include <bits/stdc++.h>
using namespace std;

void print(int a[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void insert_sort(int a[], int n) //直接插入排序
{
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        for (j = i - 1; j >= 0; j--) //为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
            if (a[j] < a[i])
                break;
        if (j != i - 1) //如找到了一个合适的位置
        {
            int temp = a[i];  //将比a[i]大的数据向后移
            for (k = i - 1; k > j; k--)
                a[k + 1] = a[k];
            a[k + 1] = temp; //将a[i]放到正确位置上
        }
    }
}

void QuickSort(int a[], int low, int high) //快速排序
{
    int i = low;
    int j = high;
    int key = a[low];
    if (low >= high)  //如果low >= high说明排序结束了
    {
        return ;
    }
    while (low < high) //该while循环结束一次表示比较了一轮
    {
        while (low < high && key <= a[high])
        {
            --high; //向前寻找
        }
        if (key > a[high])
        {
            swap(a[low], a[high]);
            ++low;
        }
        while (low < high && key >= a[low])
        {
            ++low; //向后寻找
        }
        if (key < a[low])
        {
            swap(a[low], a[high]);
            --high;
        }
    }
    QuickSort(a, i, low-1); //用同样的方式对分出来的左边的部分进行同上的做法
    QuickSort(a, low+1, j); //用同样的方式对分出来的右边的部分进行同上的做法
}

void SelectionSort(int a[], int n) //直接选择排序
{
    int i,j,min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i + 1; j < n; j++) 
        {
            if (a[j] < a[min]) min = j;
        }
        swap(a[min], a[i]);
    }
}

int main()
{
    int arr[8] = {9,3,6,2,8,1,6,4};
    // cout << "直接插入排序" << endl;
    // insert_sort(arr, 8);
    // cout << "快速排序" << endl;
    // QuickSort(arr, 0, 7);
    //cout << "直接选择/*排序" << endl;
    //SelectionSort(arr, 8);
    print(arr, 8);
}
