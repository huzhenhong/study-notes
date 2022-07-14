/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-12 17:55:29
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-07-12 18:49:43
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
    std::cout << "is a heap: " << isHeap << std::endl;
    // is a heap: 0

    auto iter = std::is_heap_until(vec.begin(), vec.end());
    std::cout << "is a heap before: " << *iter << std::endl;
    // is a heap before: 14

    std::make_heap(vec.begin(), vec.end() /* , std::less<int> */);  // 默认将 vector 构建为一个大顶堆
    // std::make_heap(vec.begin(), vec.end(), std::greater<int>());  // 构建为一个小顶堆

    isHeap = std::is_heap(vec.cbegin(), vec.cend());
    std::cout << "is a heap: " << isHeap << std::endl;
    // is a heap: 1

    std::cout << "before sort" << std::endl;
    PrintVec(vec);
    // 21 10 14 8 1 5 7 3

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "after sort" << std::endl;
    PrintVec(vec);
    // 1 3 5 7 8 10 14 21

    // 删除元素
    std::pop_heap(vec.begin(), vec.end());  // 取出堆顶元素放在末尾，原来末尾的元素放到堆顶
    vec.pop_back();                         // 删除末尾元素，余下元素还是大顶堆
    std::cout << "after pop back" << std::endl;
    PrintVec(vec);
    // 21 3 5 7 8 9 10 14

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "sort" << std::endl;
    PrintVec(vec);
    // 3 5 7 8 9 10 14 21，删除元素后排序不影响

    // 添加元素
    vec.emplace_back(9);                     // 添加一个元素
    std::push_heap(vec.begin(), vec.end());  // 此时仅仅是堆化，并没有排序
    std::cout << "after push 9" << std::endl;
    PrintVec(vec);
    // 9 3 7 5 10 14 21 8，这里比较诡异，不知道为啥

    // std::make_heap(vec.begin(), vec.end() /* , std::less<int> */);
    // std::cout << "make heap" << std::endl;
    // PrintVec(vec);
    // // 21 10 14 8 3 9 7 5

    std::sort_heap(vec.begin(), vec.end());
    std::cout << "sort" << std::endl;
    PrintVec(vec);
    // 3 5 8 10 14 21 7 9，注释掉上面后排序出错
    // 3 5 7 8 9 10 14 21，取消上面注释则排序正确，说明添加元素后需要手动重新堆化


    return 0;
}