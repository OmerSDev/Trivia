#pragma once
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestHandler.h"
#include "json.hpp"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public RequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& factory);
	~LoginRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	string getUsername() override;
private:
	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
	RequestResult error();
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;
};