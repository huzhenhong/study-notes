/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-06-24 11:43:57
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-06-24 11:43:58
 * FilePath     : \\cplusplus\\src\\condition-variables-and-semaphore\\one-producer-and-one-consumer copy.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-06-24 11:30:31
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-06-24 11:30:32
 * FilePath     : \\cplusplus\\condition-variables-and-semaphore\\main.cpp
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#include <condition_variable>
#include <mutex>
#include <thread>
#include <deque>
#include <iostream>


std::mutex              g_cvMtx;
std::condition_variable g_cv;
std::deque<int>         g_dataDeq;
const int               MAX_NUM   = 30;
int                     g_nextNum = 0;
bool                    g_bFinished{false};

// 生产者，消费者线程个数
const int               PRODUCER_THREAD_NUM = 1;
const int               CONSUMER_THREAD_NUM = 1;

void                    Producer(int threadID)
{
    while (true)
    // while (!g_bFinished)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::unique_lock<std::mutex> lk(g_cvMtx);

        // 条件满足 return true; 释放锁
        // 条件不满足 return false; 持有锁
        // wait 函数对互斥量进行解锁，同时线程进入阻塞或者等待状态
        g_cv.wait(lk, []()
                  { return g_dataDeq.size() <= MAX_NUM; });  // 队列大小大于 MAX_NUM 时释放锁，直到队列大小不大于 MAX_NUM 时重新获得锁并继续执行

        g_nextNum++;

        if (g_nextNum > 3)
        {
            g_bFinished = true;
            std::notify_all_at_thread_exit(g_cv, std::move(lk));  // 当调用该函数的线程退出时，全部在 cond 条件变量上等待的线程都会收到通知
            break;
        }

        // if (g_bFinished)
        // {
        //     break;
        // }

        g_dataDeq.push_back(g_nextNum);

        std::cout << "Producer thread-" << threadID << " producer data: " << g_nextNum << " queue size: " << g_dataDeq.size() << std::endl;

        g_cv.notify_all();  // 唤醒其他线程
        // g_cv.notify_one();
    }

    std::cout << "Producer exit\n";
    // g_bFinished = true;

    // g_cv.notify_all();
}

void Consumer(int threadID)
{
    while (true)
    // while (!g_bFinished)
    {
        if (g_bFinished)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        std::unique_lock<std::mutex> lk(g_cvMtx);

        // 条件满足 return true; 释放锁
        // 条件不满足 return false; 持有锁
        // wait 函数对互斥量进行解锁，同时线程进入阻塞或者等待状态
        g_cv.wait(lk, []
                  { return !g_dataDeq.empty(); });  // 队列为空则释放锁，直到队列不为空重新获得锁并继续执行

        int data = g_dataDeq.front();  // 取数据
        g_dataDeq.pop_front();
        std::cout << "\tConsumer thread-" << threadID << " consumer data: " << data << " deque size: " << g_dataDeq.size() << std::endl;

        g_cv.notify_all();  // 唤醒其他线程
        // g_cv.notify_one();
    }

    std::cout << "Consumer exit\n";
    // g_bFinished = true;
    // std::notify_all_at_thread_exit(g_cv, std::move(std::unique_lock<std::mutex>(g_cvMtx)));
    // g_cv.notify_all();
}


int main()
{
    std::thread arrRroducerThread[PRODUCER_THREAD_NUM];
    std::thread arrConsumerThread[CONSUMER_THREAD_NUM];

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        arrRroducerThread[i] = std::thread(Producer, i);
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        arrConsumerThread[i] = std::thread(Consumer, i);
    }

    std::chrono::milliseconds durable{3000};
    std::this_thread::sleep_for(durable);

    // g_bFinished = true;
    // g_cv.notify_all();

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        if (arrRroducerThread[i].joinable())
        {
            arrRroducerThread[i].join();
        }
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        if (arrConsumerThread[i].joinable())
        {
            arrConsumerThread[i].join();
        }
    }
    // producer
    // consumer


    return 0;
}
