/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-02-25 16:31:26
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-02-25 16:57:59
 * FilePath     : \\cplusplus\\src\\vector\\vector.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <iostream>
#include <vector>


int main(int argc, char* argv[])
{
    std::vector<int> vec;
    std::cout << "vec.size(): " << vec.size() << "  vec.capacity(): " << vec.capacity() << std::endl;
    for (int i = 0; i < 10; i++)
    {
        vec.emplace_back(i);
        std::cout << "vec.size(): " << vec.size() << "  vec.capacity(): " << vec.capacity() << std::endl;
    }

    std::cout << std::endl;


    class Obj
    {
      public:
        Obj(int val)
            : m_val(val)
        {
            std::cout << this << " Obj(int val)" << std::endl;
        }

        Obj(const Obj& obj)
        {
            std::cout << this << " Obj(const Obj& obj)" << std::endl;
            m_val = obj.m_val;
        }

        ~Obj()
        {
            std::cout << this << " ~Obj()" << std::endl;
        }

        void Show()
        {
            std::cout << this << " val: " << m_val << std::endl;
        }

        void SetVal(int val)
        {
            m_val = val;
        }

      private:
        int m_val;
    };


    {
        Obj obj(1);
        obj.Show();

        auto tmp = std::move(obj);
        tmp.Show();

        tmp.SetVal(2);
        obj.Show();
    }

    auto tmp1{std::vector<Obj>{1}};
    std::cout << "tmp1.size(): " << tmp1.size() << "  tmp1.capacity(): " << tmp1.capacity() << std::endl;
    std::cout << std::endl;

    auto tmp2{std::vector<Obj>{1, 2}};
    std::cout << "tmp2.size(): " << tmp2.size() << "  tmp2.capacity(): " << tmp2.capacity() << std::endl;
    std::cout << std::endl;

    auto tmp3 = std::move(std::vector<Obj>{1, 2, 3});
    std::cout << "tmp3.size(): " << tmp3.size() << "  tmp3.capacity(): " << tmp3.capacity() << std::endl;
    std::cout << std::endl;

    auto tmp4 = std::vector<Obj>{1, 2, 3, 4};
    std::cout << "tmp4.size(): " << tmp4.size() << "  tmp4.capacity(): " << tmp4.capacity() << std::endl;
    std::cout << std::endl;

    auto tmp5 = std::vector<Obj>{1, 2, 3, 4, 5};
    std::cout << "tmp5.size(): " << tmp5.size() << "  tmp5.capacity(): " << tmp5.capacity() << std::endl;
    std::cout << std::endl;

    return 0;
}
