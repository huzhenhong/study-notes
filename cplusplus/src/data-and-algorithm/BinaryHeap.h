/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-07-08 16:12:42
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-07-12 18:55:59
 * FilePath     : \\cplusplus\\src\\data-and-algorithm\\BinaryHeap.h
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#pragma once


#include <stdexcept>
template<typename T, bool isLargeTop = true>
class BinaryHeap
{
  public:
    BinaryHeap(int capacity /* , bool isLargeTop = true */);
    BinaryHeap(const BinaryHeap& other)            = default;
    BinaryHeap(BinaryHeap&& other)                 = default;
    BinaryHeap& operator=(const BinaryHeap& other) = default;
    BinaryHeap& operator=(BinaryHeap&& other)      = default;
    ~BinaryHeap();

    T&  operator[](int i);
    int Insert(const T& data);
    int Remove(const T& data);
    int BinaryFind(const T& data);
    int Find(const T& data);

  private:
    void Upflow(int start);
    void Downflow(int start);


  private:
    T*  m_pData;
    int m_capacity;
    int m_size;
    /*     bool m_isLargeTop; */
};


template<typename T, bool isLargeTop>
BinaryHeap<T, isLargeTop>::BinaryHeap(int capacity /* , bool isLargeTop */)
    : m_pData(nullptr)
    , m_capacity(capacity)
    , m_size(0)
/*     , m_isLargeTop(isLargeTop) */
{
    m_pData = new T[m_capacity];
}

template<typename T, bool isLargeTop>
BinaryHeap<T, isLargeTop>::~BinaryHeap()
{
    if (m_pData)
    {
        delete[] m_pData;
    }
}

template<typename T, bool isLargeTop>
T& BinaryHeap<T, isLargeTop>::operator[](int i)
{
    if (0 == m_size) throw std::range_error("out of index");

    return m_pData[i];
}


// 每次插入仅仅是做了堆化，没有排序
template<typename T, bool isLargeTop>
int BinaryHeap<T, isLargeTop>::Insert(const T& data)
{
    if (m_size == m_capacity) return -1;

    m_pData[m_size] = data;  // 末尾插入
    Upflow(m_size);
    ++m_size;

    return m_size;
}

template<typename T, bool isLargeTop>
int BinaryHeap<T, isLargeTop>::Remove(const T& data)
{
    if (0 == m_size) return -1;

    // 此时堆没有排序
    int idx = Find(data);
    if (idx < 0) return -2;

    m_pData[idx] = m_pData[--m_size];  // 用最后面的元素填补
    Downflow(idx);                     // 从idx位置开始下沉

    return 0;
}

// 二分查找，要求有序
template<typename T, bool isLargeTop>
int BinaryHeap<T, isLargeTop>::BinaryFind(const T& data)
{
    int low  = 0;
    int high = m_size - 1;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;  // 防止溢出

        if (m_pData[mid] > data)
        {
            if constexpr (isLargeTop)
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
            if constexpr (isLargeTop)
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


template<typename T, bool isLargeTop>
int BinaryHeap<T, isLargeTop>::Find(const T& data)
{
    for (int i = 0; i < m_size; ++i)
    {
        if (data == m_pData[i]) return i;
    }

    return -1;
}


template<typename T, bool isLargeTop>
void BinaryHeap<T, isLargeTop>::Upflow(int start)
{
    // 从当前节点一直上浮到根节点
    int curIdx       = start;
    int curParentIdx = (curIdx - 1) / 2;
    // int curParentIdx = curIdx / 2 - 1;
    T   cur          = m_pData[curIdx];

    while (curIdx > 0)
    {
        if constexpr (isLargeTop)
        {
            if (cur <= m_pData[curParentIdx])
            {
                break;
            }
            else
            {
                m_pData[curIdx] = m_pData[curParentIdx];  // 交换子节点和父节点
                curIdx          = curParentIdx;
                curParentIdx    = (curIdx - 1) / 2;
            }
        }
        else
        {
            if (cur >= m_pData[curParentIdx])
            {
                break;
            }
            else
            {
                m_pData[curIdx] = m_pData[curParentIdx];  // 交换子节点和父节点
                curIdx          = curParentIdx;
                curParentIdx    = (curIdx - 1) / 2;
            }
        }
    }

    m_pData[curIdx] = cur;  // 结束上浮，已找到合适位置存放start
}

template<typename T, bool isLargeTop>
void BinaryHeap<T, isLargeTop>::Downflow(int start)
{
    int curRootIdx = start;
    int childIdx   = 2 * curRootIdx + 1;  // 左孩子idx
    T   curRoot    = m_pData[curRootIdx];

    while (childIdx < m_size)
    {
        if constexpr (isLargeTop)
        {
            // childIdx + 1 为右孩子
            if (childIdx + 1 < m_size &&
                m_pData[childIdx] < m_pData[childIdx + 1])
            {
                ++childIdx;  // 选择较大的
            }

            if (curRoot < m_pData[childIdx])
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
            // childIdx + 1 为右孩子
            if (childIdx + 1 < m_size &&
                m_pData[childIdx] > m_pData[childIdx + 1])
            {
                ++childIdx;  // 选择较小的
            }

            if (curRoot > m_pData[childIdx])
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

    m_pData[curRootIdx] = curRoot;
}
