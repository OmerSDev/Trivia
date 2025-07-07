#pragma once

#include "Helper.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>

class Server
{
public:
    Server();
    ~Server();
    void serve();


private:
    void bindAndListen();
    void acceptClient();
    void clientHandler(const SOCKET client_socket);
    void safeDeleteUser(const SOCKET id);

    RequestInfo* build_receive_message(const SOCKET client_socket);

    void getCommands();
    void closeAll();

    SOCKET _socket;

    std::map<SOCKET, RequestHandler*> _clients;
    std::queue<RequestInfo*> _messages;
    RequestHandlerFactory m_handlerFactory;
    IDatabase* m_database;
    
};