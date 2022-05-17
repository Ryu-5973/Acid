/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:34:48
 * @FilePath: /Acid/acid/sync.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */


#ifndef ACID_SYNC_H
#define ACID_SYNC_H

/**
 * @brief 包含了协程同步原语
 * CoMutex      协程锁
 * CoCondvar    协程条件变量
 * CoSemaphore  协程信号量
 * Channel      消息通道
 */

#include "sync/channel.h"
#include "sync/co_condvar.h"
#include "sync/co_semaphore.h"
#include "sync/mutex.h"

#endif //ACID_SYNC_H
