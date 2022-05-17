/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-15 17:39:40
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-15 17:51:48
 * @FilePath: /Acid/acid/noncopyable.h
 * @Description: 不可复制类
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */
#ifndef ACID_NONCOPYABLE_H
#define ACID_NONCOPYABLE_H

class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable& noncopyable) = delete;
    Noncopyable& operator=(const Noncopyable& noncopyable) = delete;
};
#endif //ACID_NONCOPYABLE_H
