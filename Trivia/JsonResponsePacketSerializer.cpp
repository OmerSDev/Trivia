#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse buffer){
    Buffer newBuffer;
    newBuffer.push_back(LOGINCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);
    
    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse buffer){
    Buffer newBuffer;
    newBuffer.push_back(SIGNUPCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse buffer){
    Buffer newBuffer;

    newBuffer.push_back(ERRORCODE);
    string strJson = "";
    json data;
    data["message"] = buffer.message;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(LOGOUTCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(GETROOMCODE);

    json data;
    data["status"] = buffer.status;
    data["Rooms"] = json::array({});
    for (int i = 0; i < buffer.rooms.size(); i++) {
        data["Rooms"][i]["name"] = buffer.rooms[i].name;
        data["Rooms"][i]["id"] = buffer.rooms[i].id;
    }
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(GETPLAYERSINROOMCODE);

    json data;
    data["PlayersInRoom"] = buffer.players;

    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetHighScoreResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(GETHIGHSCORECODE);

    json data;
    data["status"] = buffer.status;
    data["HighScores"] = buffer.statistics;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetPersonalStatsResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(GETPERSONALSTATSCODE);

    json data;
    data["status"] = buffer.status;
    data["UserStatistics"] = buffer.statistics;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(JOINROOMCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(CREATEROOMCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(CLOSEROOMCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(StartGameResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(STARTGAMECODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(STARTGAMECODE);

    json data;
    data["status"] = buffer.status;
    data["hasGameBegun"] = buffer.hasGameBegun;
    data["players"] = buffer.players;
    data["AnswerCount"] = buffer.AnswerCount;
    data["answerTimeOut"] = buffer.answerTimeOut;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse buffer)
{
    Buffer newBuffer;
    newBuffer.push_back(LEAVEROOMCODE);

    json data;
    data["status"] = buffer.status;
    addJsonToBuffer(&newBuffer, data);

    return newBuffer;
}

void JsonResponsePacketSerializer::addJsonToBuffer(Buffer* buffer, json data)
{
    string strJson = data.dump();
    int size = strJson.size();
    unsigned char numberStr[4];

    memcpy(numberStr, &size, 4);
    for (int i = 0; i < 4; i++) {
        buffer->push_back(numberStr[i]);
    }

    for (int j = 0; j < size; j++) {
        buffer->push_back((unsigned char)strJson[j]);
    }
}

