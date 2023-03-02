/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-03-02 16:49:18
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-02 18:11:39
 * FilePath     : \\cplusplus\\src\\fmt_enc_dec\\fmt_enc_dec_complex.cpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
#include "fmtutil.h"
#include "fmt/ranges.h"


struct Unmovable
{
    // explicit 会阻止编译器自动地调用构造函数或转换函数来创建对象或改变类型
    /* explicit */ Unmovable(int val)
        : value(val)
    {
        fmt::print("{} -> Unmovable(int val), value: {}\n", (void*)this, val);  // placement new 时会自动使用 value 代替 val
    }

    Unmovable(const Unmovable& obj)
    {
        fmt::print("{} -> Unmovable(const Unmovable& obj), value: {}\n", (void*)this, obj.value);
        value = obj.value;
    }

    // 自定义析构函数后, 对象不可移动
    ~Unmovable()
    {
        dtorCnt++;
        fmt::print("{} -> ~Unmovable(), dtorCnt: {}\n", (void*)this, dtorCnt);
    }

    int        value;
    static int dtorCnt;
};

int Unmovable::dtorCnt = 0;


template<>
struct fmt::formatter<Unmovable> : formatter<int>
{
    template<typename FormatContext>
    auto format(const Unmovable& val, FormatContext& ctx) const
    {
        return formatter<int>::format(val.value, ctx);
    }
};


struct Movable
{
  public:
    explicit Movable(int val = 0)
        : valueVec{val}  // 拷贝构造, 完成后会调一次 ~Unmovable()
    {
        fmt::print("{} -> Movable(int val = 0), valueVec contain : {}\n", (void*)this, val);
        // placement new 时会调用 Unmovable 的拷贝构造
    }

    // 默认移动构造函数生成条件：
    // 1、没有 默认移动构造函数 = default, 这个相当于自己定义了
    // 2、没有自定义拷贝构造函数, 编译器认为你希望手动去拷贝
    // 3、没有自定义赋值构造函数, 编译器认为你希望手动去拷贝
    // 4、没有自定义析构函数, , 编译器认为你希望自己释放资源
    // 另外如果是POD之类的简单类型, 移动构造函数内部应该调用的就是拷贝构造函数
    // ~Movable()

    std::vector<Unmovable> valueVec;
};

template<>
struct fmt::formatter<Movable> : formatter<int>
{
    template<typename FormatContext>
    auto format(const Movable& val, FormatContext& ctx)
    {
        return formatter<int>::format(val.valueVec[0].value, ctx);
    }
};


template<typename FMT, typename... Args>
void Test(const FMT& fmt, Args&&... args)
{
    fmt::detail::check_format_string<Args...>(fmt);
    auto        fmtStr        = fmt::string_view(fmt);
    size_t      formattedSize = fmt::formatted_size(fmt::runtime(fmtStr), std::forward<Args>(args)...);
    std::string formatedStr   = fmt::format(fmt::runtime(fmtStr), std::forward<Args>(args)...);
    assert(formatedStr.size() == formattedSize);

    // 命名参数会以参数索引替代
    // "Hello, {name}! The answer is {number}. Goodbye, {name}.", "number"_a = 42, "name"_a = "World" 会处理成
    // "Hello, {1}! The answer is {0}. Goodbye, {1}."
    auto        unnamedFormatStr = UnNameFormat<false>(fmtStr, nullptr, args...);  // 移除命名参数
    size_t      cstringSizes[1000];                                                // 记录每个 cstring 的长度, 因为其没有类似 size() 的接口获取 自身长度
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
}


int main()
{
    int g_dtorCnt{0};

    fmt::print("=========\n");
    {
        // 构造时先构造一个 Unmovable 对象, 然后调用拷贝构造函数, 然后释放 Unmovable 对象, Unmovable::dtorCnt = 1
        Movable obj(123);
        g_dtorCnt = Unmovable::dtorCnt;

        // Format 调用完 DecodeArgs 后会调用 Destruct 函数释放 placement new 对象, 会调用 ~Movable(), 进一步调用 ~Unmovable(), Unmovable::dtorCnt = 2
        Test("test copy: {}", obj);
        assert(Unmovable::dtorCnt == g_dtorCnt + 1);

        // 局部变量仍未释放
        assert(obj.valueVec.size() == 1);

        g_dtorCnt = Unmovable::dtorCnt;
    }
    // 此时调用 Unmovable 析构函数, Unmovable::dtorCnt = 3
    assert(Unmovable::dtorCnt == g_dtorCnt + 1);
    fmt::print("=========\n");

    fmt::print("=========\n");
    {
        // 构造时先构造一个 Unmovable 对象, 然后调用拷贝构造函数, 然后释放 Unmovable 对象, Unmovable::dtorCnt = 4
        Movable val(456);
        g_dtorCnt = Unmovable::dtorCnt;

        // Format 调用完 DecodeArgs 后会调用 Destruct 函数释放 placement new 对象, 会调用 ~Movable(), 进一步调用 ~Unmovable(), Unmovable::dtorCnt = 5
        Test("test move: {}", std::move(val));
        assert(Unmovable::dtorCnt == g_dtorCnt + 1);

        // move 时调用了 Movable 的默认移动构造函数, 进而调用了 std::vector 的默认移动构造函数, 其内部执行
        // __x.__begin_ = __x.__end_ = __x.__end_cap() = nullptr;
        // 对被移动东西进行了“清空”
        assert(val.valueVec.size() == 0);

        g_dtorCnt = Unmovable::dtorCnt;
    }
    assert(Unmovable::dtorCnt == g_dtorCnt);  // move 还是会调用析构, 只是因为 valueVec 现在为空, 所以不会再调用 ~Unmovable()
    fmt::print("=========\n");

    fmt::print("=========\n");
    {
        // Movable(3) 构造时先构造一个 Unmovable 对象, 然后调用拷贝构造函数, 然后释放 Unmovable 对象, Unmovable::dtorCnt = 6
        // Format 调用完 DecodeArgs 后会调用 Destruct 函数释放 placement new 对象
        // 会调用 ~Unmovable()、~Unmovable() 和 ~Movable()->~Unmovable(), Unmovable::dtorCnt = 9 (注意调用 ~Movable() 时已将 valueVec 清空)
        Test("test custom types: {}, {}, {}", Unmovable(1), Unmovable(2), Movable(3));
        // 析构 Unmovable(1) 和 Unmovable(2) 两个临时对象, Unmovable::dtorCnt = 11
        // Movable(3) value vector 已经被清空
    }

    fmt::print("=========\n");
    {
        // Format 调用完 DecodeArgs 后会调用 Destruct 函数释放 placement new 对象, 会调用 ~Unmovable(), Unmovable::dtorCnt = 14
        Test("test ranges: {}, {}", std::vector<int>{1, 2, 3}, std::vector<Unmovable>{4, 5, 6});
        // 析构 3 个 Unmovable 临时对象, Unmovable::dtorCnt = 17
    }
    fmt::print("=========\n");

    fmt::print("Unmovable size: {}\n", sizeof(Unmovable));
    fmt::print("Movable size: {}\n", sizeof(Movable));                    // 三根指针
    fmt::print("Movable size: {}\n", sizeof(std::vector<Unmovable>{1}));  // 三根指针

    fmt::print("tests passed\n");

    return 0;

    /*
        =========
        0x7ff7bde252d0 -> Unmovable(int val), value: 123
        0x7f8d01f05a70 -> Unmovable(const Unmovable& obj), value: 123
        0x7ff7bde252d0 -> ~Unmovable(), dtorCnt: 1
        0x7ff7bde25678 -> Movable(int val = 0), valueVec contain : 123
        0x7f8d01f05a80 -> Unmovable(const Unmovable& obj), value: 123
        0x7f8d01f05a80 -> ~Unmovable(), dtorCnt: 2
        encDecStr: test copy: 123
        formatedStr: test copy: 123
        0x7f8d01f05a70 -> ~Unmovable(), dtorCnt: 3
        =========
        =========
        0x7ff7bde252d0 -> Unmovable(int val), value: 456
        0x7f8d01f05a70 -> Unmovable(const Unmovable& obj), value: 456
        0x7ff7bde252d0 -> ~Unmovable(), dtorCnt: 4
        0x7ff7bde25630 -> Movable(int val = 0), valueVec contain : 456
        // move 操作后不再需要对 vector 里的每个成员调用拷贝构造
        0x7f8d01f05a70 -> ~Unmovable(), dtorCnt: 5
        encDecStr: test move: 456
        formatedStr: test move: 456
        // move 后 vector 为空
        =========
        =========
        0x7ff7bde25608 -> Unmovable(int val), value: 1
        0x7ff7bde25600 -> Unmovable(int val), value: 2
        0x7ff7bde252d0 -> Unmovable(int val), value: 3
        0x7f8d01f05a70 -> Unmovable(const Unmovable& obj), value: 3
        0x7ff7bde252d0 -> ~Unmovable(), dtorCnt: 6
        0x7ff7bde255e8 -> Movable(int val = 0), valueVec contain : 3
        0x7ff7bde22fc0 -> Unmovable(const Unmovable& obj), value: 1
        0x7ff7bde22fc4 -> Unmovable(const Unmovable& obj), value: 2
        0x7ff7bde22fc0 -> ~Unmovable(), dtorCnt: 7
        0x7ff7bde22fc4 -> ~Unmovable(), dtorCnt: 8
        0x7f8d01f05a70 -> ~Unmovable(), dtorCnt: 9
          encDecStr: test custom types: 1, 2, 3
        formatedStr: test custom types: 1, 2, 3
        0x7ff7bde25600 -> ~Unmovable(), dtorCnt: 10
        0x7ff7bde25608 -> ~Unmovable(), dtorCnt: 11
        =========
        0x7ff7bde26130 -> Unmovable(int val), value: 4
        0x7ff7bde26134 -> Unmovable(int val), value: 5
        0x7ff7bde26138 -> Unmovable(int val), value: 6
        0x7f8d01f05aa0 -> Unmovable(const Unmovable& obj), value: 4
        0x7f8d01f05aa4 -> Unmovable(const Unmovable& obj), value: 5
        0x7f8d01f05aa8 -> Unmovable(const Unmovable& obj), value: 6
        0x7f8d01f05aa8 -> ~Unmovable(), dtorCnt: 12
        0x7f8d01f05aa4 -> ~Unmovable(), dtorCnt: 13
        0x7f8d01f05aa0 -> ~Unmovable(), dtorCnt: 14
          encDecStr: test ranges: [1, 2, 3], [4, 5, 6]
        formatedStr: test ranges: [1, 2, 3], [4, 5, 6]
        0x7ff7bde26138 -> ~Unmovable(), dtorCnt: 15
        0x7ff7bde26134 -> ~Unmovable(), dtorCnt: 16
        0x7ff7bde26130 -> ~Unmovable(), dtorCnt: 17
        =========
        Unmovable size: 4
        Movable size: 24
        Movable size: 24
        tests passed
    */
}
