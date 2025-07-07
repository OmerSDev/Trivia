#pragma once
#include "RequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"


class RequestHandlerFactory;

class RoomAdminRequestHandler : public RequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& factory, LoggedUser user, Room room);
	~RoomAdminRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	string getUsername() override;

private:
	RequestResult closeRoom(RequestInfo info);
	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};