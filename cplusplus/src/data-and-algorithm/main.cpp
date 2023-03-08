/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-12 16:21:30
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 18:25:49
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\main.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include "BinaryHeap.hpp"
#include <algorithm>
#include <array>
#include <iostream>


int main(int argc, char* argv[])
{
    // std::array<int, 8> arr{8, 1, 14, 3, 21, 5, 7, 10};
    // std::cout << "origin arr" << std::endl;
    // for (int i = 0; i < arr.size(); ++i)
    // {
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    // auto binaryHeap = BinaryHeap<int, true>(100);
    // // auto binaryHeap = BinaryHeap<int, false>();
    // for (int i = 0; i < arr.size(); ++i)
    // {
    //     binaryHeap.Insert(arr[i]);
    // }

    auto binaryHeap = BinaryHeap<int, false>({8, 1, 14, 3, 21, 5, 7, 10});

    std::cout << "insert finshed" << std::endl;
    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    binaryHeap.Remove(14);

    std::cout << "after remove 14" << std::endl;
    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "after insert 4" << std::endl;
    binaryHeap.Insert(4);

    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    auto idx = binaryHeap.Find(3);
    std::cout << "3 idx is: " << idx << std::endl;

    binaryHeap.Sort();
    std::cout << "after sort" << std::endl;
    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    idx = binaryHeap.BinaryFind(3);
    std::cout << "3 idx is: " << idx << std::endl;

    binaryHeap.Heapify();
    std::cout << "after Heapify" << std::endl;
    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    binaryHeap.Remove(4);
    std::cout << "after remove 4" << std::endl;
    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "after insert 9" << std::endl;
    binaryHeap.Insert(9);

    for (int i = 0; i < binaryHeap.Size(); ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
