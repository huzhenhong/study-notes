/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-01 10:53:22
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-07-08 13:51:23
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\heap-sort.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <algorithm>
#include <type_traits>

/* 当数组中有相等元素时，堆排序算法对这些元素的处理方法不止一种，故是不稳定的。 */


// 递归找到最大元素并放在根节点（递归可能栈溢出吧）
void Heapify(int arr[], int size, int idx)
{
    int maxIdx        = idx;
    int leftChildIdx  = 2 * idx + 1;  // 想想根节点的第一个左孩子
    int rightChildIdx = 2 * idx + 2;  // 想想根节点的第一个右孩子（不一定有）

    // 大顶堆
    // leftChildIdx < size 排序处理叶子节点的时候，没有孩子节点，索引会越界
    if (leftChildIdx < size && arr[leftChildIdx] > arr[maxIdx])
    {
        maxIdx = leftChildIdx;
    }

    if (rightChildIdx < size && arr[rightChildIdx] > arr[maxIdx])
    {
        maxIdx = rightChildIdx;
    }

    // 如果当前节点不是最大节点
    if (maxIdx != idx)
    {
        // 交换当前节点和最大子节点
        std::swap(arr[maxIdx], arr[idx]);

        // 当前节点继续下沉
        // maxIdx 现在代表原先的 idx 了
        Heapify(arr, size, maxIdx);
    }
}


void HeapSort(int arr[], int size)
{
    // build heap
    // 从最后一个非叶子节点（size / 2 - 1）开始调整每一个非叶子节点
    // 整个过程其实就是将最大值放在了根节点位置，并保证了节点链路有序
    for (int i = size / 2 - 1; i >= 0; --i)
    {
        Heapify(arr, size, i);
    }

    // sort
    // 将当前根节点的最大元素放到数组末尾（从小到大排序）
    // 破坏了堆结构，重新找到最大元素并放在根节点，如此往复直到只剩下一个未排序元素

    for (int i = size - 1; i >= 1; --i)
    {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


// void Insert(int arr[], int idx)
// {
//     int parentIdx = idx / 2;
//     if (arr[idx] > arr[parentIdx])
//     {
//         std::swap(arr[idx], arr[parentIdx]);
//         Insert(arr, parentIdx);
//     }
// }

// void Del(int arr[], int)


int main(int argc, char* argv[])
{
    int arr[8]{8, 1, 14, 3, 21, 5, 7, 10};

    std::cout << "before sort" << std::endl;
    for (auto it : arr)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    HeapSort(arr, 8);

    std::cout << "after sort" << std::endl;
    for (auto it : arr)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}