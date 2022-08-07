/*
 * @Author: Ryu-59073
 * @Date: 2022-06-12 08:01:05
 * @LastEditors: Ryu-59073
 * @LastEditTime: 2022-08-07 02:23:55
 * @FilePath: /Acid/tests/test_log.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-59073, All Rights Reserved. 
 */


#include "acid/log.h"
#include "acid/util.h"
#include <iostream>
#include <memory>
using namespace std;
int main(){
//source::Logger::ptr logger(std::make_shared<source::Logger>());
    auto logger = acid::LogMgr::GetInstance()->getLogger("system");
    ACID_LOG_INFO(logger)   <<  "info log";
    ACID_LOG_DEBUG(logger)  <<  "debug log";
    ACID_LOG_WARN(logger)   <<  "warn log"; 
    ACID_LOG_ERROR(logger)  <<  "error log";
    ACID_LOG_FATAL(logger)  <<  "fatal log";
    
  //cout<<"hello";
}
