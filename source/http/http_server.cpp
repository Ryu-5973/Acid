/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:35:55
 * @FilePath: /Acid/source/http/http_server.cpp
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#include "acid/http/http_server.h"
#include "acid/http/parse.h"
#include "acid/http/servlet.h"
#include "acid/log.h"
namespace acid::http {
static Logger::ptr g_logger = ACID_LOG_NAME("system");
HttpServer::HttpServer(bool keepalive, IOManager *worker, IOManager *accept_worker)
    : TcpServer(worker, accept_worker)
    , m_isKeepalive(keepalive){
    m_dispatch.reset(new ServletDispatch);

}

void HttpServer::handleClient(Socket::ptr client) {
    ACID_LOG_DEBUG(g_logger) << "handleClient: " << client->toString();
    HttpRequestParser::ptr parser(new HttpRequestParser);
    HttpSession::ptr session(new HttpSession(client));
    while (true) {
        HttpRequest::ptr request = session->recvRequest();
        if (!request) {
            session->close();
            ACID_LOG_DEBUG(g_logger) << "recv http request fail, errno="
                                      << errno << " errstr=" << strerror(errno)
                                      << " cliet:" << client->toString()
                                      << " keep_alive=" << m_isKeepalive;
            break;
        }
        HttpResponse::ptr response(new HttpResponse(request->getVersion(), request->isClose() || !m_isKeepalive));
        response->setHeader("Server" ,getName());

        if (m_dispatch->handle(request, response, session) == 0) {
            session->sendResponse(response);
        }

        if (request->isClose() || !m_isKeepalive) {
            break;
        }
    }
    session->close();
}

void HttpServer::setName(const std::string& name) {
    TcpServer::setName(name);
    m_dispatch->setDefault(NotFoundServlet::ptr(new NotFoundServlet(name)));
}

}