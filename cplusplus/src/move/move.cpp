/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-02-25 16:31:26
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-02-25 22:53:15
 * FilePath     : \\cplusplus\\src\\move\\move.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <utility>
#include <vector>


struct MyType
{
    MyType(const MyType& val) = default;

    /* explicit */
    MyType(int val)
        : value(val)
    // : vec{val}
    {
        std::cout << this << " MyType()" << std::endl;
        std::cout << this << " value: " << value << std::endl;
    }

    // MyType(const MyType& obj)
    // {
    //     std::cout << this << " MyType(const MyType& obj)" << std::endl;
    //     // *this = obj;
    //     value = obj.value;
    //     std::cout << this << " value: " << value << std::endl;
    // }

    MyType(MyType&& obj)
    {
        std::cout << this << " MyType(MyType&& obj)" << std::endl;
        value = std::move(obj.value);
        std::cout << this << " value: " << value << std::endl;
    }

    ~MyType()
    {
        std::cout << this << " ~MyType()" << std::endl;
        std::cout << this << " value: " << value << std::endl;
    }

    int value;
    // std::vector<int> vec;
};


class Obj
{
  public:
    Obj(int val)
        : m_vec{val}
        , m_val{val}
    {
        std::cout << this << " Obj(int val)" << std::endl;
        std::cout << this << " val: " << m_val << std::endl;
        std::cout << this << " m_vec size: " << m_vec.size() << std::endl;
    }

    // Obj(const Obj& obj)
    // {
    //     std::cout << this << " Obj(const Obj& obj)" << std::endl;
    //     std::cout << this << " val: " << obj.m_val << std::endl;
    //     std::cout << this << " m_vec size: " << obj.m_vec.size() << std::endl;
    //     m_val = obj.m_val;
    //     m_vec = obj.m_vec;
    // }

    // Obj(Obj&& obj)
    // {
    //     std::cout << this << " Obj(Obj&& obj)" << std::endl;
    //     std::cout << this << " val: " << obj.m_val << std::endl;
    //     std::cout << this << " m_vec size: " << obj.m_vec.size() << std::endl;
    //     m_val = obj.m_val;
    //     m_vec = obj.m_vec;
    //     // obj.m_val = 0;
    //     // obj.m_vec.clear();
    //     // *this = std::move(obj);
    // }

    // ~Obj()
    // {
    //     std::cout << this << " ~Obj()" << std::endl;
    //     // std::cout << this << " val: " << m_val << std::endl;
    //     // std::cout << this << " m_vec size: " << m_vec.size() << std::endl;
    // }

    void Show()
    {
        std::cout << this << " val: " << m_val << std::endl;
        std::cout << this << " m_vec size: " << m_vec.size() << std::endl;
    }

    void SetVal(int val)
    {
        m_val = val;
    }

  private:
    int              m_val;
    std::vector<int> m_vec;
    static int       s_cnt;
};

int Obj::s_cnt = 1;

int main(int argc, char* argv[])
{
    {
        // auto e = MyType();
        auto a = MyType(1);
        auto b = std::move(a);
        int  i = 0;
    }

    // {
    //     Obj obj(1);
    //     obj.Show();

    //     // 没有默认移动构造函数，此时就会调用默认的拷贝构造函数
    //     // 默认拷贝构造时如果对每一个成员变量优先使用移动构造，没有移动构造的类型则使用拷贝构造
    //     auto tmp = std::move(obj);
    //     tmp.Show();

    //     tmp.SetVal(2);

    //     tmp.Show();
    //     obj.Show();
    // }


    return 0;
}
