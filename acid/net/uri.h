/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:31:41
 * @FilePath: /Acid/acid/net/uri.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */
#ifndef ACID_URI_H
#define ACID_URI_H
#include <memory>
#include <ostream>
#include "acid/coroutine.h"
#include "address.h"

namespace acid {

/**
 * @brief URI类，支持大部分协议包括 HTTP，HTTPS，FTP，FILE，磁力链接等等
 */
class Uri{
public:
    using ptr = std::shared_ptr<Uri>;
    Uri();

    /**
     * @brief 创建Uri对象
     * @param uri uri字符串
     * @return 解析成功返回Uri对象否则返回nullptr
     */
    static Uri::ptr Create(const std::string& uri);

    Address::ptr createAddress();
    const std::string& getScheme() const { return m_scheme;}
    const std::string& getUserinfo() const { return m_userinfo;}
    const std::string& getHost() const { return m_host;}
    const std::string& getPath() const;
    const std::string& getQuery() const { return m_query;}
    const std::string& getFragment() const { return m_fragment;}
    uint32_t getPort() const;

    void setScheme(const std::string& scheme) { m_scheme = scheme;}
    void setUserinfo(const std::string& userinfo) { m_userinfo = userinfo;}
    void setHost(const std::string& host) { m_host = host;}
    void setPath(const std::string& path) { m_path = path;}
    void setQuery(const std::string& query) { m_query = query;}
    void setFragment(const std::string& fragment) { m_fragment = fragment;}

    std::ostream& dump(std::ostream& ostream);
    std::string toString();

private:
    Task<bool> parse();
    bool isDefaultPort() const;
private:
    std::string m_scheme;
    std::string m_userinfo;
    std::string m_host;
    std::string m_path;
    std::string m_query;
    std::string m_fragment;
    uint32_t m_port;
    const char* m_cur;
    bool m_error;
};

}
#endif //ACID_URI_H
