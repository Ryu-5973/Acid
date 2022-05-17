/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:32:30
 * @FilePath: /Acid/acid/rpc/rpc_session.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#ifndef ACID_RPC_SESSION_H
#define ACID_RPC_SESSION_H

#include "acid/net/socket_stream.h"
#include "protocol.h"

namespace acid::rpc {
/**
 * @brief rpc session 封装了协议的收发
 */
class RpcSession : public SocketStream {
public:
    using ptr = std::shared_ptr<RpcSession>;
    using MutexType = CoMutex;

    /**
     * @brief 构造函数
     * @param[in] sock Socket类型
     * @param[in] owner 是否托管Socket
     */
    RpcSession(Socket::ptr socket, bool owner = true);
    /**
     * @brief 接收协议
     * @return 如果返回空协议则接收失败
     */
    Protocol::ptr recvProtocol();
    /**
     * @brief 发送协议
     * @param[in] proto 要发送的协议
     * @return 发送大小
     */
    ssize_t sendProtocol(Protocol::ptr proto);
private:
    MutexType m_mutex;
};
}
#endif //ACID_RPC_SESSION_H
