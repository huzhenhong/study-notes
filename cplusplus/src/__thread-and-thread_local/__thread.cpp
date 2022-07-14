/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-06-29 15:11:53
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-06-29 15:47:11
 * FilePath     : \\cplusplus\\src\\__thread_and_thread_local\\__thread.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <pthread.h>
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


// non-local variable声明为__thread需要动态初始化
__thread Object* pObj = nullptr;
// 需要动态初始化，__thread是不支持非函数本地变量的
// __thread可以被用于类的全局静态、文件作用域静态、函数作用域静态或静态数据成员。它可能不适用于块作用域自动或非静态数据成员。

void             Func()
{
    std::cout << "th_" << std::this_thread::get_id() << " [child] thread, start...\n";

    if (!pObj)
    {
        pObj = new Object();
        std::cout << "th_" << std::this_thread::get_id() << " [child] thread, pObj [" << pObj << "]\n";
    }

    pObj->SayHello();

    if (pObj)
    {
        delete pObj;
    }

    std::cout << "th_" << std::this_thread::get_id() << " [child] thread, stop...\n";
}


int main(int argc, char* argv[])
{
    std::cout << "th_" << std::this_thread::get_id() << " [main] thread, start...\n";

    if (!pObj)
    {
        pObj = new Object();
        std::cout << "th_" << std::this_thread::get_id() << " [main] thread, pObj [" << pObj << "]\n";
    }

    auto thr = std::thread(&Func);
    thr.join();

    pObj->SayHello();

    if (pObj)
    {
        delete pObj;
    }

    std::cout << "th_" << std::this_thread::get_id() << " [main] thread, stop...\n";

    return 0;
}