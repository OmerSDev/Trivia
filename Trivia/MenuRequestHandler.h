#pragma once
#include "RequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

#define JOINED 42
#define FAILED_TO_JOIN 50
#define ROOM_CREATED 61
#define ROOM_NOT_CREATED 62

class RequestHandlerFactory;

class MenuRequestHandler : public RequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& Factory, LoggedUser user);
	~MenuRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	string getUsername() override;

private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);
};