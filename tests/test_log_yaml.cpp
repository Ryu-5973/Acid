/*
 * @Author: Ryu-59073
 * @Date: 2022-06-12 08:01:05
 * @LastEditors: Ryu-59073
 * @LastEditTime: 2022-07-11 09:37:52
 * @FilePath: /Acid/tests/test_log_yaml.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-59073, All Rights Reserved. 
 */
//
// Created by zavier on 2021/11/2.
//
#include <iostream>
#include <fstream>
#include "acid/log.h"
#include "yaml-cpp/yaml.h"
#include "acid/config.h"
auto port = acid::Config::Lookup("system.port",8080,"bind port");

int main(){
    try{
        acid::Config::LoadFromFile("config/log.yaml");
    }catch(YAML::BadFile &e) {
        std::ofstream oFile;
        oFile.open("config/log.yaml", std::ios::app);
        if (!oFile) {
            std::cout << "fail" << std::endl;
            throw e;
        }else {
            acid::Config::LoadFromFile("config/log.yaml");
        }
    }

    ACID_LOG_ROOT()->setFormatter("%n -- %m --%n ");
    //std::cout << acid::LogMgr::GetInstance()->toString()<<std::endl;
    ACID_LOG_ERROR(ACID_LOG_ROOT())<<"aaa";
}