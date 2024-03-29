/*************************************************************************************
 * Description  :
 * Version      : 1.0
 * Author       : huzhenhong
 * Date         : 2022-08-09 13:56:46
 * LastEditors  : huzhenhong
 * LastEditTime : 2022-10-18 18:53:56
 * FilePath     : \\FmtLog\\src\\logger.h
 * Copyright (C) 2022 huzhenhong. All rights reserved.
 *************************************************************************************/
#pragma once
#include "fmtlog.h"
// #include "TSCNS.h"

#define __FMTLOG_S1(x) #x
#define __FMTLOG_S2(x) __FMTLOG_S1(x)
#define __FMTLOG_LOCATION __FILE__ ":" __FMTLOG_S2(__LINE__)


// 注意这里logId是局部静态变量，所以同一条日志只会初始化一次
#define FMTLOG(level, format, ...)                                     \
    do                                                                 \
    {                                                                  \
        static uint32_t logId = 0;                                     \
                                                                       \
        if (!fmtlogWrapper::impl.checkLogLevel(level))                 \
            break;                                                     \
                                                                       \
        fmtlogWrapper::impl.log(logId,                                 \
                                TimeStampCounterWarpper::impl.Rdtsc(), \
                                __FMTLOG_LOCATION,                     \
                                level,                                 \
                                format,                                \
                                ##__VA_ARGS__);                        \
    } while (0)

#define FMTLOG_LIMIT(min_interval, level, format, ...)                                        \
    do                                                                                        \
    {                                                                                         \
        static uint32_t logId   = 0;                                                          \
        static int64_t  limitNs = 0;                                                          \
        if (!fmtlogWrapper::impl.checkLogLevel(level))                                        \
            break;                                                                            \
        int64_t tsc = TimeStampCounterWarpper::impl.Rdtsc();                                  \
        int64_t ns  = TimeStampCounterWarpper::impl.Tsc2ns(tsc);                              \
        if (ns < limitNs)                                                                     \
            break;                                                                            \
        limitNs = ns + min_interval;                                                          \
        fmtlogWrapper::impl.log(logId, tsc, __FMTLOG_LOCATION, level, format, ##__VA_ARGS__); \
    } while (0)

#define FMTLOG_ONCE(level, format, ...)                                               \
    do                                                                                \
    {                                                                                 \
        if (!fmtlogWrapper::impl.checkLogLevel(level))                                \
            break;                                                                    \
        fmtlogWrapper::impl.logOnce(__FMTLOG_LOCATION, level, format, ##__VA_ARGS__); \
    } while (0)


#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_DBG
    #define logd(format, ...) FMTLOG(DBG, format, ##__VA_ARGS__)
    #define logdo(format, ...) FMTLOG_ONCE(DBG, format, ##__VA_ARGS__)
    #define logdl(min_interval, format, ...) FMTLOG_LIMIT(min_interval, DBG, format, ##__VA_ARGS__)
#else
    #define logd(format, ...) (void)0
    #define logdo(format, ...) (void)0
    #define logdl(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_INF
    #define logi(format, ...) FMTLOG(INF, format, ##__VA_ARGS__)
    #define logio(format, ...) FMTLOG_ONCE(INF, format, ##__VA_ARGS__)
    #define logil(min_interval, format, ...) FMTLOG_LIMIT(min_interval, INF, format, ##__VA_ARGS__)
#else
    #define logi(format, ...) (void)0
    #define logio(format, ...) (void)0
    #define logil(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_WRN
    #define logw(format, ...) FMTLOG(WRN, format, ##__VA_ARGS__)
    #define logwo(format, ...) FMTLOG_ONCE(WRN, format, ##__VA_ARGS__)
    #define logwl(min_interval, format, ...) FMTLOG_LIMIT(min_interval, WRN, format, ##__VA_ARGS__)
#else
    #define logw(format, ...) (void)0
    #define logwo(format, ...) (void)0
    #define logwl(min_interval, format, ...) (void)0
#endif

#if FMTLOG_ACTIVE_LEVEL <= FMTLOG_LEVEL_ERR
    #define loge(format, ...) FMTLOG(ERR, format, ##__VA_ARGS__)
    #define logeo(format, ...) FMTLOG_ONCE(ERR, format, ##__VA_ARGS__)
    #define logel(min_interval, format, ...) FMTLOG_LIMIT(min_interval, ERR, format, ##__VA_ARGS__)
#else
    #define loge(format, ...) (void)0
    #define logeo(format, ...) (void)0
    #define logel(min_interval, format, ...) (void)0
#endif
