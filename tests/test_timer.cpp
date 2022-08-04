/*
 * @Author: Ryu-59073
 * @Date: 2022-06-12 08:01:05
 * @LastEditors: Ryu-59073
 * @LastEditTime: 2022-08-04 07:49:05
 * @FilePath: /Acid/tests/test_timer.cpp
 * @Description: 计时器测试
 * 
 * Copyright (c) 2022 by Ryu-59073, All Rights Reserved. 
 */

#include "acid/acid.h"
#include <iostream>
#include "sys/time.h"
static acid::Logger::ptr g_logger = ACID_LOG_ROOT();
void test5(){
    acid::IOManager ioManager{3};

    acid::Timer::ptr timer1 = ioManager.addTimer(5000,[&timer1]{
        static int i =0;
        i++;
        if(i==3){
            //timer1->reset(2000, true);
            //timer1->refresh();
        }
        ACID_LOG_INFO(g_logger) << i <<" seconds 3";
    }, true);
    acid::Timer::ptr timer = ioManager.addTimer(2000,[&timer,&timer1]{
        static int i =0;
        i++;
        if(i==3){
            //timer->reset(1000, true);
            //timer->cancel();
            //timer1->refresh();
        }
        ACID_LOG_INFO(g_logger) << i <<" seconds 2";
    }, true);
    getchar();
}
acid::Timer::ptr s_timer;
void test1(){
    acid::IOManager ioManager{};
    ACID_LOG_INFO(g_logger) << "start counting";
    s_timer = ioManager.addTimer(1, []{
        static int i =0;
        i ++;
        if(i%5000==0){
            s_timer->cancel();
            ACID_LOG_INFO(g_logger) << "finsh counting, 5 second";
        }
    }, true);
}
int main(){
    // test5();
    test1();
}