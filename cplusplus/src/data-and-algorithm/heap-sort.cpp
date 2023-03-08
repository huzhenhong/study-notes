/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-01 10:53:22
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 16:47:30
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\heap-sort.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <algorithm>
#include <type_traits>

/* 当数组中有相等元素时，堆排序算法对这些元素的处理方法不止一种，故是不稳定的。 */


// 递归调整当前节点以及其叶子结点，找到最大元素并放在该节点（递归可能栈溢出吧）
void HeapifyWithRecursion(int arr[], int size, int idx)
{
    int maxIdx        = idx;
    int leftChildIdx  = 2 * idx + 1;  // 当前节点的第一个左孩子
    int rightChildIdx = 2 * idx + 2;  // 当前节点的第一个右孩子（最后一个非叶子结点不一定有）

    // leftChildIdx < size 是因为下一轮递归时，maxIdx = size - 1，那么 leftChildIdx 会越界
    if (leftChildIdx < size && arr[leftChildIdx] > arr[maxIdx])
    {
        maxIdx = leftChildIdx;
    }

    // rightChildIdx < size 是因为下一轮递归时，maxIdx = size - 1，那么 rightChildIdx 会越界
    if (rightChildIdx < size && arr[rightChildIdx] > arr[maxIdx])
    {
        maxIdx = rightChildIdx;
    }

    if (maxIdx != idx)  // 当前节点比孩子节点小
    {
        // 交换当前节点和最大叶子节点
        std::swap(arr[maxIdx], arr[idx]);

        // maxIdx 现在为 leftChildIdx 或者 rightChildIdx，所以不一定是沿着一条直线一直下沉
        HeapifyWithRecursion(arr, size, maxIdx);
    }
}


void HeapifyWithLoop(int arr[], int size, int idx)
{
    int curRootIdx    = idx;
    int leftChildIdx  = 2 * idx + 1;  // 当前节点的第一个左孩子
    int rightChildIdx = 2 * idx + 2;  // 当前节点的第一个右孩子（最后一个非叶子结点不一定有）
    int bigChildIdx   = 0;

    // int arr[8]{8, 1, 14, 3, 21, 5, 7, 10};
    while (leftChildIdx < size)
    {
        // 有右孩子且右孩子比左孩子大
        if (rightChildIdx < size && arr[rightChildIdx] > arr[leftChildIdx])
        {
            bigChildIdx = rightChildIdx;
        }
        else
        {
            bigChildIdx = leftChildIdx;
        }

        // 已经有序则无需继续下沉
        if (arr[curRootIdx] >= arr[bigChildIdx])
        {
            return;
        }
        else
        {
            std::swap(arr[curRootIdx], arr[bigChildIdx]);
            curRootIdx    = bigChildIdx;
            leftChildIdx  = 2 * curRootIdx + 1;
            rightChildIdx = 2 * curRootIdx + 2;
        }
    }
}

void HeapSort(int arr[], int size)
{
    // build heap
    // 从最后一个非叶子节点（size / 2 - 1）开始调整每一个非叶子节点
    // 整个过程保证每一个非叶子结点都比其叶子结点大
    // 从下往上调整，大值上浮
    for (int i = size / 2 - 1; i >= 0; --i)
    {
        HeapifyWithRecursion(arr, size, i);
        // HeapifyWithLoop(arr, size, i);
    }

    // sort
    // 将当前根节点的最大元素放到数组末尾（从小到大排序）
    // 破坏了堆结构，重新找到最大元素并放在根节点，如此往复直到只剩下一个未排序元素
    // 从上往下调整，小值下沉
    for (int i = size - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        HeapifyWithRecursion(arr, i, 0);
        // HeapifyWithLoop(arr, i, 0);
    }
}


int main(int argc, char* argv[])
{
    int arr[7]{8, 1, 14, 3, 21, 5, 7};
    // int arr[8]{8, 1, 14, 3, 21, 5, 7, 10};

    std::cout << "before sort" << std::endl;
    for (auto it : arr)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    HeapSort(arr, 7);
    // HeapSort(arr, 8);

    std::cout << "after sort" << std::endl;
    for (auto it : arr)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    return 0;
}