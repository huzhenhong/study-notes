/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-02-26 18:05:45
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-02-28 21:24:55
 * FilePath     : \\cplusplus\\src\\explicit\\explicit.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <vector>


int main(int argc, char* argv[])
{
    {
        class CustomClass
        {
          public:
            CustomClass(int x)
                : value(x)
            {
            }

          private:
            int value;
        };

        std::vector<CustomClass> v = {1, 2, 3};  // OK
    }


    class CustomClass
    {
      public:
        /* explicit */
        CustomClass(int x)
            : value(x)
        {
        }

      private:
        int value;
    };
    // std::vector<CustomClass, std::allocator<CustomClass>> v = std::vector<CustomClass,
    //                                                                       std::allocator<CustomClass>>;
    {
        // std::initializer_list<CustomClass>{
        //     static_cast<const CustomClass>(CustomClass(1)),
        //     static_cast<const CustomClass>(CustomClass(2)),
        //     static_cast<const CustomClass>(CustomClass(3))},
        // static_cast<const std::allocator<CustomClass>>(std::allocator<CustomClass>())};

        // std::vector<CustomClass> v(std::initializer_list<CustomClass>{1, 2, 3});  // OK
        std::vector<CustomClass> v{1, 2, 3};  // OK
        // v.size();

        // CustomClass              c1 = 10;                   // 错误，不能隐式地调用构造函数
        // CustomClass              c2(10);                    // 正确，显式地调用构造函数
        // int                      x = c2;                    // 错误，不能隐式地调用转换函数
        // int                      y = static_cast<int>(c2);  // 正确，显式地调用转换函数
    }

    return 0;
}