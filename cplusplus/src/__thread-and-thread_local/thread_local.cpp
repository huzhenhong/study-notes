/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-06-29 14:07:03
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-06-29 15:42:59
 * FilePath     : \\cplusplus\\src\\__thread_and_thread_local\\thread_local.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <thread>


class Object
{
  public:
    Object()
    {
        std::cout << "th_" << std::this_thread::get_id() << " Object()\n";
    }

    ~Object()
    {
        std::cout << "th_" << std::this_thread::get_id() << " ~Object()\n";
    }

    void SayHello()
    {
        std::cout << "th_" << std::this_thread::get_id() << " Hello\n";
    }
};


// #define GLOBAL
#ifdef GLOBAL
thread_local Object obj;
#endif


void Func()
{
    std::cout << "th_" << std::this_thread::get_id() << " [child] thread, start...\n";

#ifdef GLOBAL
    obj.SayHello();
#else
    thread_local Object obj;
#endif
    std::cout << "th_" << std::this_thread::get_id() << " [child] thread, stop...\n";
}


int main(int argc, char* argv[])
{
    std::cout << "th_" << std::this_thread::get_id() << " [main] thread, start...\n";

#ifdef GLOBAL
    auto thr = std::thread(&Func);
    thr.join();

    obj.SayHello();
#else
    auto                thr1 = std::thread(&Func);
    auto                thr2 = std::thread(&Func);
    thr1.join();
    thr2.join();
#endif

    std::cout << "th_" << std::this_thread::get_id() << " [main] thread, stop...\n";

    return 0;
}