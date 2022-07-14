/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-12 16:21:30
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-07-12 18:57:13
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\main.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include "BinaryHeap.h"
#include <iostream>


int main(int argc, char* argv[])
{
    auto binaryHeap = BinaryHeap<int, true>(100);

    int  arr[8]{8, 1, 14, 3, 21, 5, 7, 10};

    for (int i = 0; i < 8; ++i)
    {
        binaryHeap.Insert(arr[i]);
    }

    std::cout << "insert finshed" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    binaryHeap.Remove(14);

    std::cout << "after remove 14" << std::endl;
    for (int i = 0; i < 7; ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "after insert 4" << std::endl;
    binaryHeap.Insert(4);

    for (int i = 0; i < 8; ++i)
    {
        std::cout << binaryHeap[i] << " ";
    }
    std::cout << std::endl;


    auto idx = binaryHeap.Find(3);
    std::cout << "3 idx is: " << idx << std::endl;

    return 0;
}