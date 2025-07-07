#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& factory, LoggedUser user) :
    m_loggedUser(LoggedUser(user.getUsername())), m_handlerFactory(factory)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == CREATEROOMCODE || info.id == GETROOMCODE ||
        info.id == GETPLAYERSINROOMCODE || info.id == JOINROOMCODE ||
        info.id == GETPERSONALSTATSCODE || info.id == LOGOUTCODE ||
        info.id == GETHIGHSCORECODE;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (isRequestRelevant(info))
    {
        if (info.id == LOGOUTCODE)
        {
            result = this->signout(info);
        }
        else if (info.id == GETROOMCODE)
        {
            result = this->getRooms(info);
        }
        else if (info.id == GETPLAYERSINROOMCODE)
        {
            result = this->getPlayersInRoom(info);
        }
        else if (info.id == GETPERSONALSTATSCODE)
        {
            result = this->getPersonalStats(info);
        }
        else if (info.id == GETHIGHSCORECODE)
        {
            result = this->getHighScore(info);
        }
        else if (info.id == JOINROOMCODE)
        {
            result = this->joinRoom(info);
        }
        else if (info.id == CREATEROOMCODE)
        {
            result = this->createRoom(info);
        }
    }
    return result;
}

string MenuRequestHandler::getUsername()
{
    return this->m_loggedUser.getUsername();
}

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(LogoutResponse({ LOGGED_OUT }));
    this->m_handlerFactory.getLoginManager().logout(this->m_loggedUser.getUsername());
    return RequestResult({ response, this->m_handlerFactory.createLoginRequestHandler() });
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(GetRoomResponse({ LOGGED_IN, this->m_handlerFactory.getRoomManager().getRooms() }));
    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser) });
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
    unsigned int roomId = JsonRequestPacketDeserializer::deserializeGetPlayersInRommRequest(info.buffer).roomid;
    Buffer response = JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse({ this->m_handlerFactory.getRoomManager().getRoom(roomId).getALLUsers() }));
    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser) });
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse({ LOGGED_IN, this->m_handlerFactory.getStatisticsManager().getUserStatistics(this->m_loggedUser.getUsername()) }));
    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser) });
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
    Buffer response = JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse({ LOGGED_IN, this->m_handlerFactory.getStatisticsManager().getHighScore() }));
    return RequestResult({ response, this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser) });
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
    RequestHandler* newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
    unsigned int roomId = JsonRequestPacketDeserializer::deserializeJoinRommRequest(info.buffer).roomid;
    Room& room = this->m_handlerFactory.getRoomManager().getRoom(roomId);
    unsigned int status = this->m_handlerFactory.getRoomManager().GetRoomState(roomId) ? FAILED_TO_JOIN : JOINED;
    if (status == JOINED)
    {
        room.addUser(this->m_loggedUser);
        vector<string> vec = room.getALLUsers();
        status = (find(vec.begin(), vec.end(), this->m_loggedUser.getUsername()) != vec.end()) ? JOINED : FAILED_TO_JOIN;
        if (status == JOINED)
        {
            newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_loggedUser, room);
        }
    }

    Buffer response = JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({ status }));
    return RequestResult({ response, newHandler });
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
    unsigned int status = 0;
    int roomID = 0;
    RequestHandler* newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_loggedUser);
    try
    {
        CreateRommRequest request = JsonRequestPacketDeserializer::deserializeCreateRommRequest(info.buffer);

        if (request.maxUsers >= 1 && request.questionCount >= 1 && request.answerTimeout >= 1)
        {
            status = ROOM_CREATED;
            roomID = this->m_handlerFactory.getRoomManager().createRoom(this->m_loggedUser, RoomData({ 0, request.roomName, request.maxUsers, request.questionCount, request.answerTimeout, false }));
            newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_loggedUser, this->m_handlerFactory.getRoomManager().getRoom(roomID));
        }
        else
        {
            status = ROOM_NOT_CREATED;
        }
    }
    catch (...) {
        status = ROOM_NOT_CREATED;
    }
    Buffer response = JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse({ status }));
    return RequestResult({ response, newHandler });
}
