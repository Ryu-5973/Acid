/*
 * @Author: Ryu-59073
 * @Date: 2022-07-11 00:48:05
 * @LastEditors: Ryu-59073
 * @LastEditTime: 2022-07-11 08:40:09
 * @FilePath: /Acid/acid/dict_tree.h
 * @Description: 字典树类，提供O(len(key))复杂度的数据串键值对查找、插入的数据结构
 * 
 * Copyright (c) 2022 by Ryu-59073, All Rights Reserved. 
 */
#ifndef ACID_TREE_H
#define ACID_TREE_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <cstdlib>


namespace acid {
class Logger;
class DictTree: public std::enable_shared_from_this<DictTree>{
public:
    using ptr = std::shared_ptr<DictTree>;

    DictTree(bool end = false): m_end(end){
    }
    ~DictTree() = default;

    bool check(char c) {
        return m_children.find(c) != m_children.end();
    } 
    bool isEnd() {
        return m_end;
    }
    void setChild(char c) {
        m_children[c] = std::make_shared<DictTree>();
    }
    void setEnd(bool end = true) {
        m_end = end;
    }
    void setLogger(std::shared_ptr<Logger> logger) {
        m_logger = logger;
    }
    const std::unordered_map<char, DictTree::ptr>& getChildren() {
        return m_children;
    } 
    std::shared_ptr<Logger> getLogger() {
        return m_logger;
    }
    DictTree::ptr getNext(char c) {
        return m_children[c];
    }
    const std::vector<std::shared_ptr<Logger>> getAllLoggers() {
        std::vector<std::shared_ptr<Logger>> ret;
        std::function<void(DictTree::ptr)> dfs;
        dfs = [&](DictTree::ptr t) {
            if(t == nullptr) {
                return ;
            }
            if(t->isEnd()) {
                ret.push_back(t->getLogger());
            }
            for(const auto &[key, val] : t->getChildren()) {
                dfs(val);
            }
        };
        dfs(shared_from_this());
        return ret;
    }

    std::pair<bool, std::shared_ptr<Logger>> find(const std::string& name) {
        int32_t n = name.size();
        DictTree::ptr cur = shared_from_this();
        for(int32_t i = 0; i < n; ++ i) {
            if(cur->check(name[i]) == false) {
                return {false, nullptr};
            }
            cur = cur->getNext(name[i]);
        }
        if(cur->isEnd() == true) {
            return {true, cur->getLogger()};
        }
        return {false, nullptr};
    }

    void insert(const std::string& name, std::shared_ptr<Logger> logger) {
        int32_t n = name.size();
        DictTree::ptr cur;
        cur = shared_from_this();
        for(int32_t i = 0; i < n; ++ i) {
            if(cur->check(name[i]) == false) {
                cur->setChild(name[i]);
            }
            cur = cur->getNext(name[i]);
        }
        cur->setEnd();
        cur->setLogger(logger);
    }

public:
    std::unordered_map<char, DictTree::ptr> m_children;
    bool m_end;
    std::shared_ptr<Logger> m_logger;
};
    
} // namespace acid


#endif // ACID_TREE