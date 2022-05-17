/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:37:29
 * @FilePath: /Acid/source/rpc/rpc_session.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#include "acid/rpc/rpc_session.h"

namespace acid::rpc {
RpcSession::RpcSession(Socket::ptr socket, bool owner)
    : SocketStream(socket, owner) {
}

Protocol::ptr RpcSession::recvProtocol() {
    Protocol::ptr proto = std::make_shared<Protocol>();
    ByteArray::ptr byteArray = std::make_shared<ByteArray>();
    if (readFixSize(byteArray, proto->BASE_LENGTH) <= 0) {
        return nullptr;
    }

    byteArray->setPosition(0);
    proto->decodeMeta(byteArray);

    if(proto->getMagic() != Protocol::MAGIC) {
        return nullptr;
    }

    if (!proto->getContentLength()) {
        return proto;
    }

    std::string buff;
    buff.resize(proto->getContentLength());

    if (readFixSize(&buff[0], proto->getContentLength()) <= 0) {
        return nullptr;
    }
    proto->setContent(buff);
    return proto;
}

ssize_t RpcSession::sendProtocol(Protocol::ptr proto) {
    ByteArray::ptr byteArray = proto->encode();
    MutexType::Lock lock(m_mutex);
    return writeFixSize(byteArray, byteArray->getSize());
}

}