/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-03-01 18:15:48
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-02 18:14:08
 * FilePath     : \\cplusplus\\src\\fmt_enc_dec\\fmt_enc_dec.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <cassert>
#include "fmtutil.h"


template<typename FMT, typename... Args>
void Test(const FMT& fmt, Args&&... args)
{
    fmt::print("=========\n");

    fmt::detail::check_format_string<Args...>(fmt);
    auto        fmtStr        = fmt::string_view(fmt);
    size_t      formattedSize = fmt::formatted_size(fmt::runtime(fmtStr), std::forward<Args>(args)...);
    std::string formatedStr   = fmt::format(fmt::runtime(fmtStr), std::forward<Args>(args)...);
    assert(formatedStr.size() == formattedSize);

    // 命名参数会以参数索引替代
    // "Hello, {name}! The answer is {number}. Goodbye, {name}.", "number"_a = 42, "name"_a = "World" 会处理成
    // "Hello, {1}! The answer is {0}. Goodbye, {1}."
    auto unnamedFormatStr = UnNameFormat<false>(fmtStr, nullptr, args...);  // 移除命名参数
    fmt::print("  namedFormatStr: {}\n", fmtStr);
    fmt::print("unnamedFormatStr: {}\n", unnamedFormatStr);

    size_t      cstringSizes[1000];  // 记录每个 cstring 的长度，因为其没有类似 size() 的接口获取 自身长度
    size_t      totalArgSize = GetArgSize<0>(cstringSizes, args...);

    char        argSaveBuf[1024];
    const char* pRet = EncodeArgs<0>(cstringSizes, argSaveBuf, std::forward<Args>(args)...);
    assert(pRet - argSaveBuf == totalArgSize);

    fmt::basic_memory_buffer<char, 10000>                   decBuf;
    int                                                     argIdx = -1;
    std::vector<fmt::basic_format_arg<fmt::format_context>> extraArgVec;  // 额外需要格式化的参数

    pRet = Format<Args...>(unnamedFormatStr, argSaveBuf, decBuf, argIdx, extraArgVec);  // 返回拷贝执行到 buf 的哪里了
    assert(pRet - argSaveBuf == totalArgSize);

    std::string_view encDecStr(decBuf.data(), decBuf.size());
    fmt::print("  encDecStr: {}\n", encDecStr);
    fmt::print("formatedStr: {}\n", formatedStr);
    assert(encDecStr == formatedStr);

    fmt::print("=========\n");
}


int main()
{
    char        cstr[100] = "hello ";
    const char* pCstr     = "world";
    const char* pCstring  = cstr;
    std::string str("xlog");
    char        ch       = 'f';
    char&       chRef    = ch;
    int         i        = 5;
    int&        iRef     = i;
    double      d        = 3.45;
    float       f        = 55.2;
    uint16_t    shortInt = 2222;

    Test("test basic types: {}, {}, {}, {}, {}, {}, {}, {}, {:.1f}, {}, {}, {}, {}, {}, {}, {}",
         cstr,
         pCstr,
         pCstring,
         "say",
         'x',
         5,
         str,
         std::string_view(str),
         1.34,
         ch,
         chRef,
         i,
         iRef,
         d,
         f,
         shortInt);

    // {two:>5} : 右对齐，总宽度为5
    // {0:.1f} : 保留一位小数，没有小树补0
    using namespace fmt::literals;
    Test("test positional, {one}, {two:>5}, {three}, {four}, {0:.1f}",
         5.012,
         "three"_a = 3,
         "two"_a   = "two",
         "one"_a   = std::string("one"),
         "four"_a  = std::string("4"));

    // {:*^30} : 内容居中，两边补*
    Test("test dynamic spec: {:.{}f}, {:*^30}", 3.14, 1, "centered");

    Test("test positional spec: int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42);

    fmt::print("tests passed\n");

    return 0;
}

/*
=========
  namedFormatStr: test basic types: {}, {}, {}, {}, {}, {}, {}, {}, {:.1f}, {}, {}, {}, {}, {}, {}, {}
unnamedFormatStr: test basic types: {}, {}, {}, {}, {}, {}, {}, {}, {:.1f}, {}, {}, {}, {}, {}, {}, {}
  encDecStr: test basic types: hello , world, hello , say, x, 5, xlog, xlog, 1.3, f, f, 5, 5, 3.45, 55.2, 2222
formatedStr: test basic types: hello , world, hello , say, x, 5, xlog, xlog, 1.3, f, f, 5, 5, 3.45, 55.2, 2222
=========
=========
  namedFormatStr: test positional, {one}, {two:>5}, {three}, {four}, {0:.1f}
unnamedFormatStr: test positional, {3}, {2:>5}, {1}, {4}, {0:.1f}
  encDecStr: test positional, one,   two, 3, 4, 5.0
formatedStr: test positional, one,   two, 3, 4, 5.0
=========
=========
  namedFormatStr: test dynamic spec: {:.{}f}, {:*^30}
unnamedFormatStr: test dynamic spec: {:.{}f}, {:*^30}
  encDecStr: test dynamic spec: 3.1, ***********centered***********
formatedStr: test dynamic spec: 3.1, ***********centered***********
=========
=========
  namedFormatStr: test positional spec: int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}
unnamedFormatStr: test positional spec: int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}
  encDecStr: test positional spec: int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010
formatedStr: test positional spec: int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010
=========
tests passed
*/