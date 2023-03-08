/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-12 17:55:29
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 14:42:41
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\STLheap.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>


int main(int argc, char* argv[])
{
    auto PrintVec = [](const auto& vec)
    {
        for (auto it : vec)
        {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    };


    std::vector<int> vec{8, 1, 14, 3, 21, 5, 7, 10};

    auto             isHeap = std::is_heap(vec.cbegin(), vec.cend());
    std::cout << "is a heap: " << isHeap << std::endl;  // is a heap: 0

    auto iter = std::is_heap_until(vec.begin(), vec.end());
    std::cout << "is a heap before: " << *iter << std::endl;  // is a heap before: 14

    std::make_heap(vec.begin(), vec.end() /* , std::less<int> */);  // 默认将 vector 构建为一个大顶堆
    // std::make_heap(vec.begin(), vec.end(), std::greater<int>());  // 构建为一个小顶堆

    std::cout << "make heap: " << std::endl;
    PrintVec(vec);  // 21 10 14 8 1 5 7 3

    isHeap = std::is_heap(vec.cbegin(), vec.cend());
    std::cout << "is a heap: " << isHeap << std::endl;  // is a heap: 1

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "sort heap: " << std::endl;
    PrintVec(vec);  // 1 3 5 7 8 10 14 21

    // pop_heap 把原来的数组末尾元素放到堆顶，并不断下溯，每次下溯时它会和其两个子节点比较，所以是O(2logN)
    std::pop_heap(vec.begin(), vec.end());  // 取出堆顶元素放在末尾，原来末尾的元素放到堆顶，没有删除元素
    std::cout << "pop heap: " << std::endl;
    PrintVec(vec);  // 21 3 5 7 8 10 14 1

    vec.pop_back();  // 删除末尾元素
    std::cout << "pop back: " << std::endl;
    PrintVec(vec);  // 21 3 5 7 8 10 14

    // 破坏了堆结构，余下元素不再是大顶堆
    isHeap = std::is_heap(vec.cbegin(), vec.cend());
    std::cout << "is a heap: " << isHeap << std::endl;

    std::sort_heap(vec.begin(), vec.end());  // 内部应该是调用了 std::make_heap 先构建堆
    std::cout << "sort heap: " << std::endl;
    PrintVec(vec);  // 3 5 7 8 10 14 21，删除元素后排序不影响

    // 添加元素
    vec.emplace_back(9);  // 添加一个元素
    std::cout << "emplace back 9: " << std::endl;
    PrintVec(vec);  // 3 5 7 8 10 14 21 9

    // push_heap 是把数字加到末尾，并不断上溯，每次上溯时它只和其父节点比较，复杂度为 O(logN)
    std::push_heap(vec.begin(), vec.end());  // 插入位于位置 last-1 的元素到范围 [first, last-1) 所定义的最大堆（默认）中
    std::cout << "push heap: " << std::endl;
    PrintVec(vec);  // 9 3 7 5 10 14 21 8

    auto vecWithoutHeap = vec;
    std::sort_heap(vecWithoutHeap.begin(), vecWithoutHeap.end());
    std::cout << "sort without make heap: " << std::endl;
    PrintVec(vecWithoutHeap);  // 3 5 7 10 14 21 8 9

    std::make_heap(vec.begin(), vec.end() /* , std::less<int> */);
    std::cout << "make heap: " << std::endl;
    PrintVec(vec);  // 21 10 14 8 3 9 7 5

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "sort with make heapsort: " << std::endl;
    PrintVec(vec);  // 3 5 7 8 9 10 14 21

    return 0;
}