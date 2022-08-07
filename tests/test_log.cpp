/*
 * @Author: Ryu-59073
 * @Date: 2022-06-12 08:01:05
 * @LastEditors: Ryu-59073
 * @LastEditTime: 2022-08-07 08:48:42
 * @FilePath: /Acid/tests/test_log.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-59073, All Rights Reserved. 
 */


#include "acid/log.h"
#include "acid/util.h"
#include <iostream>
#include <memory>
#include <string>
#include <thread>
using namespace std;
int main(){
//source::Logger::ptr logger(std::make_shared<source::Logger>());
    auto logger = acid::LogMgr::GetInstance()->getLogger("system");
    ACID_LOG_INFO(logger)   <<  "info log";
    ACID_LOG_DEBUG(logger)  <<  "debug log";
    ACID_LOG_WARN(logger)   <<  "warn log"; 
    ACID_LOG_ERROR(logger)  <<  "error log";
    ACID_LOG_FATAL(logger)  <<  "fatal log";
    
    auto loggerTest = [](string& loggerName) {
        auto logger = acid::LogMgr::GetInstance()->getLogger(loggerName);
        for(int i = 0; i < 10; ++ i) {
            if(i % 5 == 0) {
                ACID_LOG_INFO(logger)   <<  "info log";
            }else if(i % 5 == 1) {
                ACID_LOG_DEBUG(logger)  <<  "debug log";
            }else if(i % 5 == 2) {
                ACID_LOG_WARN(logger)   <<  "warn log"; 
            }else if(i % 5 == 3) {
                ACID_LOG_ERROR(logger)  <<  "error log";
            }else if(i % 5 == 4) {
                ACID_LOG_FATAL(logger)  <<  "fatal log";
            }
        }
    };
    string name1 = "logger1", name2 = "logger2";
    thread t1(loggerTest, std::ref(name1));
    thread t2(loggerTest, std::ref(name2));
    t1.join();
    t2.join();
    return 0;
  //cout<<"hello";
}
