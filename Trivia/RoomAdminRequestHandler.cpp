#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& factory, LoggedUser user, Room room) : 
    m_room(room), m_user(LoggedUser(user.getUsername())), m_handlerFactory(factory), m_roomManager(factory.getRoomManager())
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == CLOSEROOMCODE || info.id == STARTGAMECODE || info.id == GETROOMSTATECODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (isRequestRelevant(info))
    {
        if (info.id == CLOSEROOMCODE)
        {
            result = this->closeRoom(info);
        }
        else if (info.id == STARTGAMECODE)
        {
            result = this->startGame(info);
        }
        else if (info.id == GETROOMSTATECODE)
        {
            result = this->getRoomState(info);
        }
    }
    return result;
}

string RoomAdminRequestHandler::getUsername()
{
    return this->m_user.getUsername();
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse({ LOGGED_IN }));

    this->m_roomManager.deleteRoom(this->m_room.getRoomData().id);

    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_user) });
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{

    Buffer response = JsonResponsePacketSerializer::serializeResponse(StartGameResponse({ LOGGED_IN }));

    this->m_roomManager.getRoom(this->m_room.getRoomData().id).getRoomData().isActive = true;

    return RequestResult({ response, nullptr });
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
    RoomData data = this->m_roomManager.getRoom(m_room.getRoomData().id).getRoomData();

    Buffer response = JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse({ LOGGED_IN, (bool)data.isActive, this->m_room.getALLUsers() , data.numOfQuestionsInGame, data.timePerQuestion }));
    return RequestResult({response, this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_roomManager.getRoom(data.id)) });
}
