/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-08 13:46:41
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-07-08 15:06:58
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\heap-sort1.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <algorithm>
#include <type_traits>

/* 当数组中有相等元素时，堆排序算法对这些元素的处理方法不止一种，故是不稳定的。 */

void Heapify(int arr[], int size, int idx)
{
    int curRootIdx    = idx;
    int leftChildIdx  = 2 * idx + 1;  // 想想根节点的第一个左孩子
    int rightChildIdx = 2 * idx + 2;  // 想想根节点的第一个右孩子（不一定有）
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
    // 整个过程其实就是将最大值放在了根节点位置，并保证了节点链路有序
    // 从下往上调整，上浮
    for (int i = size / 2 - 1; i >= 0; --i)
    {
        Heapify(arr, size, i);
    }

    // sort
    // 将当前根节点的最大元素放到数组末尾（从小到大排序）
    // 破坏了堆结构，重新找到最大元素并放在根节点，如此往复直到只剩下一个未排序元素
    // 从上往下调整，下沉
    for (int i = size - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}


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