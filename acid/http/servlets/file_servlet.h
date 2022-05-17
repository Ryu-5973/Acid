/*
 * @Author: Ryu-5973 l15218537285@outlook.com
 * @Date: 2022-05-17 11:01:20
 * @LastEditors: Ryu-5973 l15218537285@outlook.com
 * @LastEditTime: 2022-05-17 11:29:38
 * @FilePath: /Acid/acid/http/servlets/file_servlet.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ryu-5973 l15218537285@outlook.com, All Rights Reserved. 
 */

#ifndef ACID_FILE_SERVLET_H
#define ACID_FILE_SERVLET_H
#include "../servlet.h"
namespace acid::http {
class FileServlet : public Servlet {
public:
    using ptr = std::shared_ptr<FileServlet>;
    FileServlet(const std::string &path);
    int32_t handle(HttpRequest::ptr request, HttpResponse::ptr response, HttpSession::ptr session) override;
private:
    std::string m_path;
};

}
#endif //ACID_FILE_SERVLET_H
