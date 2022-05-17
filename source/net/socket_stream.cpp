/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:36:40
 * @FilePath: /Acid/source/net/socket_stream.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#include "acid/net/socket_stream.h"

namespace acid {

SocketStream::SocketStream(Socket::ptr socket, bool owner)
    : m_socket(socket)
    , m_isOwner(owner){

}

SocketStream::~SocketStream() {
    if(m_socket && m_isOwner) {
        m_socket->close();
    }
}

ssize_t SocketStream::read(void *buffer, size_t length) {
    if (!isConnected()) {
        return -1;
    }
    return m_socket->recv(buffer, length);
}

ssize_t SocketStream::read(ByteArray::ptr buffer, size_t length) {
    if (!isConnected()) {
        return -1;
    }
    std::vector<iovec> iovs;
    buffer->getWriteBuffers(iovs, length);
    ssize_t n =m_socket->recv(&iovs[0], iovs.size());
    if(n > 0) {
        buffer->setPosition(buffer->getPosition() + n);
    }
    return n;
}

ssize_t SocketStream::write(const void *buffer, size_t length) {
    if (!isConnected()) {
        return -1;
    }
    return m_socket->send(buffer, length);
}

ssize_t SocketStream::write(ByteArray::ptr buffer, size_t length) {
    if (!isConnected()) {
        return -1;
    }
    std::vector<iovec> iovs;
    buffer->getReadBuffers(iovs, length);
    ssize_t n = m_socket->send(&iovs[0], iovs.size());
    if(n > 0) {
        buffer->setPosition(buffer->getPosition() + n);
    }
    return n;
}

void SocketStream::close() {
    if (m_socket) {
        m_socket->close();
    }
}


}