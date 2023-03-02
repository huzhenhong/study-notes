/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-02-08 15:36:12
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-02-08 15:49:54
 * FilePath     : \\cplusplus\\src\\memory_align\\memory_align.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>


struct Object
{
    char  a;  // 1 byte
              // padding 3 bytes
    int   b;  // 4 bytes
    short c;  // 2 bytes
              // no padding
    char  d;  // 1 byte
              // padding 3 bytes
} obj[3];


int main(int argc, char* argv[])
{
    std::cout << "sizeof(Object): " << sizeof(Object) << std::endl;
    std::cout << "alignof(Object): " << alignof(Object) << std::endl;

    return 0;
}