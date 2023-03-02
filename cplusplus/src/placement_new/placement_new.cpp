/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-02-25 15:46:01
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-02-25 16:22:13
 * FilePath     : \\cplusplus\\src\\placement_new\\placement_new.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>


class Obj
{
  public:
    Obj(int val)
        : m_val(val)
    {
        std::cout << this << " Obj()" << std::endl;
    }

    ~Obj()
    {
        std::cout << this << " ~Obj()" << std::endl;
    }

    void Show()
    {
        std::cout << this << " val: " << m_val << std::endl;
    }

  private:
    int m_val;
};


int main(int argc, char* argv[])
{
    {
        int  i{1};

        int* ptr{nullptr};

        std::cout << "i: " << i << std::endl;
        ptr  = new (&i) int;
        *ptr = 2;
        std::cout << "i: " << i << std::endl;
    }

    std::cout << std::endl;

    {
        Obj obj(1);
        obj.Show();

        auto ptr = new (&obj) Obj(2);
        ptr->Show();
        ptr->~Obj();
    }

    std::cout << std::endl;

    {
        char buf[sizeof(Obj)];
        buf[0] = 'a';
        buf[1] = 'b';
        buf[2] = 'c';
        buf[3] = 'd';
        std::cout << buf[0] << std::endl;
        std::cout << buf[1] << std::endl;
        std::cout << buf[2] << std::endl;
        std::cout << buf[3] << std::endl;

        auto ptr = new (buf) Obj(3);  // 此时内存已经被修改
        ptr->Show();
        ptr->~Obj();

        std::cout << buf[0] << std::endl;  // '\x03' 不可见
        std::cout << buf[1] << std::endl;  // '\0 不可见
        std::cout << buf[2] << std::endl;  // '\0 不可见
        std::cout << buf[3] << std::endl;  // '\0 不可见
    }

    std::cout << std::endl;

    {
        auto buf = new char[sizeof(Obj)];
        buf[0]   = 'a';
        buf[1]   = 'b';
        buf[2]   = 'c';
        buf[3]   = 'd';
        std::cout << buf[0] << std::endl;
        std::cout << buf[1] << std::endl;
        std::cout << buf[2] << std::endl;
        std::cout << buf[3] << std::endl;

        auto ptr = new (buf) Obj(3);  // 此时内存已经被修改
        ptr->Show();
        ptr->~Obj();

        std::cout << buf[0] << std::endl;  // '\x03' 不可见
        std::cout << buf[1] << std::endl;  // '\0 不可见
        std::cout << buf[2] << std::endl;  // '\0 不可见
        std::cout << buf[3] << std::endl;  // '\0 不可见

        delete[] buf;
    }

    std::cout << std::endl;

    {
        auto ptr = new Obj(1);
        ptr->Show();

        // ptr1 == ptr
        auto ptr1 = new (ptr) Obj(3);  // 此时内存已经被修改
        ptr1->Show();
        ptr1->~Obj();

        delete ptr;
    }

    std::cout << std::endl;

    return 0;
}
