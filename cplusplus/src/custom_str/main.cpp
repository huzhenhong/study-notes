/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-03-07 19:21:45
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-07 20:46:55
 * FilePath     : \\cplusplus\\src\\custom_str\\main.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include "CustomStr.h"
#include "fmt/core.h"
#include <chrono>


int main(int argc, char* argv[])
{
    Str<10> str;

    str.fromi(1234567890);

    const size_t RECORD = 100'000'000'000;

    auto         time1 = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < RECORD; ++i)
    {
        fmt::string_view strv(str.Ptr(), 10);
    }

    auto   time2 = std::chrono::high_resolution_clock::now();

    double span = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1).count();
    fmt::print("str.Ptr() cost {:.1f} ns\n", span * 1e9);

    auto time3 = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < RECORD; ++i)
    {
        fmt::string_view strv(str.charArr, 10);
    }

    auto time4 = std::chrono::high_resolution_clock::now();

    span = std::chrono::duration_cast<std::chrono::duration<double>>(time4 - time3).count();
    fmt::print("str.charArr cost {:.1f} ns\n", span * 1e9);

    return 0;
}
