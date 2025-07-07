#pragma once
#include "RequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"


class RequestHandlerFactory;

class RoomMemberRequestHandler : public RequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& factory, LoggedUser user, Room room);
	~RoomMemberRequestHandler();
	bool isRequestRelevant(RequestInfo info) override;
	RequestResult handleRequest(RequestInfo info) override;
	string getUsername() override;

private:
	RequestResult leaveRoom(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};