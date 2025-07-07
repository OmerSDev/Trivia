#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& factory, LoggedUser user, Room room) :
	m_room(Room(room.getRoomData())), m_user(LoggedUser(user.getUsername())), m_handlerFactory(factory), m_roomManager(factory.getRoomManager())
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == LEAVEROOMCODE || info.id == GETROOMSTATECODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (isRequestRelevant(info))
    {
        if (info.id == LEAVEROOMCODE)
        {
            result = this->leaveRoom(info);
        }
        else if (info.id == GETROOMSTATECODE)
        {
            result = this->getRoomState(info);
        }
    }
    return result;
}

string RoomMemberRequestHandler::getUsername()
{
	return this->m_user.getUsername();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ LOGGED_IN }));

    try
    {
        this->m_roomManager.getRoom(this->m_room.getRoomData().id).removeUser(this->m_user);
    }
    catch (...)
    {

    }

    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_user) });
}


RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
    Buffer response;
    Room& room = this->m_roomManager.getRoom(this->m_room.getRoomData().id);
    RequestHandler* newHandler = nullptr;
    RoomData data = room.getRoomData();
    unsigned int status = LOGGED_IN;
    if (data.numOfQuestionsInGame == 0)
    {
        status = LEAVEROOMCODE;
        newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
        response = JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse({ LOGGED_IN }));
    }
    else if (data.isActive)
    {
        newHandler = nullptr;
        response = JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ status, (bool)data.isActive, room.getALLUsers() , data.numOfQuestionsInGame, data.timePerQuestion }));
    }
    else
    {
        newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, room);
        response = JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ status, (bool)data.isActive, room.getALLUsers() , data.numOfQuestionsInGame, data.timePerQuestion }));
    }
    return RequestResult({ response, newHandler });
}
