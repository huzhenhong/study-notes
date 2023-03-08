/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2023-03-08 17:49:14
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 17:49:15
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\BinaryHeap copy.hpp
 * Copyright (C) 2023 huzhenhong. All rights reserved.
 *************************************************************************************/
/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-08 16:12:42
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 17:49:02
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\BinaryHeap.hpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#pragma once
// #include <cstddef>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <vector>


template<typename T, bool IsLargeTop = true>
class BinaryHeap
{
  public:
    BinaryHeap()
        : BinaryHeap(100)
    {
    }

    BinaryHeap(int capacity)
        : m_pData(nullptr)
        , m_capacity(capacity)
        , m_size(0)
    {
        if (m_capacity < 0) throw std::invalid_argument("capacity must be a non-negative number");

        m_pData = new T[m_capacity];
    }

    BinaryHeap(T* arr, int size)
    {
        if (arr == nullptr || size == 0) throw std::invalid_argument("arr is nullptr or size is 0");

        m_pData = new T[size];

        for (size_t i = 0; i < size; ++i)
        {
            Insert(arr[i]);
        }
    }

    BinaryHeap(const std::vector<T>& vec)
    {
        if (vec.size() == 0) throw std::invalid_argument("vec is empty");

        m_pData = new T[vec.size()];

        for (auto it : vec)
        {
            Insert(*it);
        }
    }

    BinaryHeap(const BinaryHeap& other)
    {
        *this = other;  // 浅拷贝
    }

    BinaryHeap(BinaryHeap&& other)
    {
        *this            = other;
        other.m_pData    = nullptr;
        other.m_size     = 0;
        other.m_capacity = 0;
    }

    BinaryHeap& operator=(const BinaryHeap& other)
    {
        *this = other;  // 浅拷贝
    }

    BinaryHeap& operator=(BinaryHeap&& other)
    {
        *this            = other;
        other.m_pData    = nullptr;
        other.m_size     = 0;
        other.m_capacity = 0;
    }

    ~BinaryHeap()
    {
        delete[] m_pData;
    }

    T& operator[](int i)
    {
        if (0 == m_size) throw std::range_error("out of index");

        return m_pData[i];
    }

    int Insert(const T& data)
    {
        if (m_size == m_capacity) return -1;

        m_pData[m_size] = data;  // 末尾插入
        Upflow(m_size);          // 从末尾开始上浮
        ++m_size;

        return m_size;
    }

    int Remove(const T& data)
    {
        if (0 == m_size) return -1;

        // 此时堆没有排序，但是已经是堆化结构
        int idx = Find(data);
        if (idx < 0) return -2;

        m_pData[idx] = m_pData[--m_size];  // 用最后面的元素填补
        Downflow(idx, m_size);             // 从idx位置开始下沉

        return 0;
    }

    int Find(const T& data)
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (data == m_pData[i]) return i;
        }

        return -1;
    }

    void Heapify()
    {
        for (int i = m_size / 2 - 1; i >= 0; --i)
        {
            Downflow(i, m_size);
        }
    }

    void Sort()
    {
        for (int i = m_size - 1; i > 0; --i)
        {
            std::swap(m_pData[0], m_pData[i]);
            Downflow(0, i);
        }
    }

    int BinaryFind(const T& data)
    {
        int low  = 0;
        int high = m_size - 1;
        int mid;

        while (low <= high)
        {
            mid = low + (high - low) / 2;  // 防止溢出

            if (m_pData[mid] > data)
            {
                if constexpr (IsLargeTop)
                {
                    high = mid - 1;  // 从小达到
                }
                else
                {
                    low = mid + 1;  // 从大到小
                }
            }
            else if (m_pData[mid] < data)
            {
                if constexpr (IsLargeTop)
                {
                    low = mid + 1;  // 从小达到
                }
                else
                {
                    high = mid - 1;  // 从大到小
                }
            }
            else
            {
                return mid;
            }
        }

        return -1;
    }

    T* Ptr()
    {
        return m_pData;
    }

    int Size()
    {
        return m_size;
    }

    int Capacity()
    {
        return m_capacity;
    }

  private:
    void Upflow(int start)
    {
        // 从当前节点一直上浮到根节点
        int curIdx       = start;
        int curParentIdx = (curIdx - 1) / 2;
        T   cur          = m_pData[curIdx];

        while (curIdx > 0)
        {
            if constexpr (IsLargeTop)
            {
                if (cur <= m_pData[curParentIdx])
                {
                    break;
                }
            }
            else
            {
                if (cur >= m_pData[curParentIdx])
                {
                    break;
                }
            }

            m_pData[curIdx] = m_pData[curParentIdx];  // 交换子节点和父节点
            curIdx          = curParentIdx;
            curParentIdx    = (curIdx - 1) / 2;
        }

        m_pData[curIdx] = cur;  // 结束上浮，已找到合适位置存放start
    }

    void Downflow(int start, int size)
    {
        int curRootIdx = start;
        int childIdx   = 2 * curRootIdx + 1;  // 左孩子idx
        T   cur        = m_pData[curRootIdx];

        while (childIdx < size)
        {
            if constexpr (IsLargeTop)
            {
                // 有右孩子、且右孩子比左孩子大
                if (childIdx + 1 < size &&  // childIdx + 1 为右孩子
                    m_pData[childIdx] < m_pData[childIdx + 1])
                {
                    ++childIdx;  // 选择较大的
                }

                if (cur < m_pData[childIdx])
                {
                    m_pData[curRootIdx] = m_pData[childIdx];
                    curRootIdx          = childIdx;
                    childIdx            = 2 * curRootIdx + 1;
                }
                else
                {
                    break;
                }
            }
            else
            {
                // 有右孩子、且右孩子比左孩子小
                if (childIdx + 1 < size &&  // childIdx + 1 为右孩子
                    m_pData[childIdx] > m_pData[childIdx + 1])
                {
                    ++childIdx;  // 选择较小的
                }

                if (cur > m_pData[childIdx])
                {
                    m_pData[curRootIdx] = m_pData[childIdx];
                    curRootIdx          = childIdx;
                    childIdx            = 2 * curRootIdx + 1;
                }
                else
                {
                    break;
                }
            }
        }

        m_pData[curRootIdx] = cur;
    }

  private:
    T*  m_pData;
    int m_capacity;
    int m_size;
};
