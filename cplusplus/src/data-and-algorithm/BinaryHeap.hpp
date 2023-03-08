/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-08 16:12:42
 * LastEditors  : huzhenhong
 * LastEditTime : 2023-03-08 18:24:46
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\BinaryHeap.hpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#pragma once
#include <sys/_types/_size_t.h>
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
    {
        if (capacity < 0) throw std::invalid_argument("capacity must be a non-negative number");

        m_dataVec.reserve(capacity);
    }

    BinaryHeap(T* arr, int size)
        : BinaryHeap(size)
    {
        if (arr == nullptr || size == 0) throw std::invalid_argument("arr is nullptr or size is 0");

        for (size_t i = 0; i < size; ++i)
        {
            Insert(arr[i]);
        }
    }

    BinaryHeap(const std::vector<T>& vec)
        : BinaryHeap(vec.size())
    {
        if (vec.size() == 0) throw std::invalid_argument("vec is empty");

        m_dataVec = vec;
        Heapify();
    }

    BinaryHeap(std::vector<T>&& vec)
    {
        if (vec.size() == 0) throw std::invalid_argument("vec is empty");

        m_dataVec = std::move(vec);
        Heapify();
    }

    BinaryHeap(const BinaryHeap& other)
    {
        *this = other;  // 浅拷贝
    }

    BinaryHeap(BinaryHeap&& other)
    {
        *this = std::move(other);
    }

    BinaryHeap& operator=(const BinaryHeap& other)
    {
        *this = other;  // 浅拷贝
    }

    BinaryHeap& operator=(BinaryHeap&& other)
    {
        *this = std::move(other);
    }

    ~BinaryHeap()
    {
    }

    T& operator[](int i)
    {
        if (i < 0 || i >= m_dataVec.size()) throw std::range_error("out of index");

        return m_dataVec[i];
    }

    int Insert(const T& data)
    {
        m_dataVec.emplace_back(data);  // 末尾插入
        Upflow(m_dataVec.size() - 1);  // 从末尾开始上浮

        return m_dataVec.size();
    }

    int Remove(const T& data)
    {
        // 此时堆没有排序，但是已经是堆化结构
        int idx = Find(data);
        if (idx < 0) return -1;

        m_dataVec[idx] = m_dataVec.back();  // 用最后面的元素填补
        m_dataVec.pop_back();
        Downflow(idx, m_dataVec.size());  // 从idx位置开始下沉

        return 0;
    }

    int Find(const T& data)
    {
        for (int i = 0; i < m_dataVec.size(); ++i)
        {
            if (data == m_dataVec[i]) return i;
        }

        return -1;
    }

    void Heapify()
    {
        for (int i = m_dataVec.size() / 2 - 1; i >= 0; --i)
        {
            Downflow(i, m_dataVec.size());
        }
    }

    // 需要先堆化
    void Sort()
    {
        for (int i = m_dataVec.size() - 1; i > 0; --i)
        {
            std::swap(m_dataVec[0], m_dataVec[i]);
            Downflow(0, i);
        }
    }

    // 需要先排序
    int BinaryFind(const T& data)
    {
        int low  = 0;
        int high = m_dataVec.size() - 1;
        int mid;

        while (low <= high)
        {
            mid = low + (high - low) / 2;  // 防止溢出

            if (m_dataVec[mid] > data)
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
            else if (m_dataVec[mid] < data)
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

    // 允许进行修改，但是修改完成后需要再次调用 Heapify() 进行堆化
    std::vector<T>& Data()
    {
        return m_dataVec;
    }

    size_t Size()
    {
        return m_dataVec.size();
    }

  private:
    void Upflow(int start)
    {
        // 从当前节点一直上浮到根节点
        int curIdx       = start;
        int curParentIdx = (curIdx - 1) / 2;
        T   cur          = m_dataVec[curIdx];

        while (curIdx > 0)
        {
            if constexpr (IsLargeTop)
            {
                if (cur <= m_dataVec[curParentIdx])
                {
                    break;
                }
            }
            else
            {
                if (cur >= m_dataVec[curParentIdx])
                {
                    break;
                }
            }

            m_dataVec[curIdx] = m_dataVec[curParentIdx];  // 交换子节点和父节点
            curIdx            = curParentIdx;
            curParentIdx      = (curIdx - 1) / 2;
        }

        m_dataVec[curIdx] = cur;  // 结束上浮，已找到合适位置存放start
    }

    void Downflow(int start, int size)
    {
        int curRootIdx = start;
        int childIdx   = 2 * curRootIdx + 1;  // 左孩子idx
        T   cur        = m_dataVec[curRootIdx];

        while (childIdx < size)
        {
            if constexpr (IsLargeTop)
            {
                // 有右孩子、且右孩子比左孩子大
                if (childIdx + 1 < size &&  // childIdx + 1 为右孩子
                    m_dataVec[childIdx] < m_dataVec[childIdx + 1])
                {
                    ++childIdx;  // 选择较大的
                }

                if (cur < m_dataVec[childIdx])
                {
                    m_dataVec[curRootIdx] = m_dataVec[childIdx];
                    curRootIdx            = childIdx;
                    childIdx              = 2 * curRootIdx + 1;
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
                    m_dataVec[childIdx] > m_dataVec[childIdx + 1])
                {
                    ++childIdx;  // 选择较小的
                }

                if (cur > m_dataVec[childIdx])
                {
                    m_dataVec[curRootIdx] = m_dataVec[childIdx];
                    curRootIdx            = childIdx;
                    childIdx              = 2 * curRootIdx + 1;
                }
                else
                {
                    break;
                }
            }
        }

        m_dataVec[curRootIdx] = cur;
    }

  private:
    std::vector<T> m_dataVec;
};
