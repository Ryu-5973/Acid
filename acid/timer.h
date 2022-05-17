/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:35:15
 * @FilePath: /Acid/acid/timer.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#ifndef ACID_TIMER_H
#define ACID_TIMER_H
#include <functional>
#include <memory>
#include <set>
#include "log.h"
#include "sync.h"
namespace acid{
class TimeManager;
class Timer : public std::enable_shared_from_this<Timer>{
friend class TimeManager;
public:
    using ptr = std::shared_ptr<Timer>;
    bool cancel();
    bool refresh();
    bool reset(uint64_t ms, bool from_now);
private:
    Timer(uint64_t ms, std::function<void()> cb, bool recurring, TimeManager* timeManager);
    Timer(uint64_t next);

private:
    uint64_t m_ms = 0;          //执行周期
    uint64_t m_next = 0;        //精确的执行时间
    std::function<void()> m_cb;   //定时器回调
    bool m_recurring = false;   //是否循环
    TimeManager* m_manager = nullptr;
private:
    struct Compare{
        bool operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const;
    };
};

class TimeManager{
friend class Timer;
public:
    using MutexType = Mutex;
    TimeManager();
    virtual ~TimeManager();
    Timer::ptr addTimer(uint64_t ms, std::function<void()> cb, bool recurring = false);
    Timer::ptr addConditionTimer(uint64_t ms, std::function<void()> cb,
                                 std::weak_ptr<void> cond,
                                 bool recurring = false);
    uint64_t getNextTimer();
    void getExpiredCallbacks(std::vector<std::function<void()>>& cbs);
    bool hasTimer();
protected:
    virtual void onInsertAtFront() = 0;
    void addTimer(Timer::ptr timer, MutexType::Lock & lock);
private:
    MutexType m_mutex;
    std::set<Timer::ptr, Timer::Compare> m_timers;
    bool m_tickled = false;
};




}
#endif //ACID_TIMER_H
