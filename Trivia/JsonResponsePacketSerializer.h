#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "Room.h"
typedef std::vector<unsigned char> Buffer;
#define LOGINCODE 111
#define SIGNUPCODE 222
#define ERRORCODE 0
#define LOGOUTCODE 1
#define GETROOMCODE 2
#define GETPLAYERSINROOMCODE 3
#define GETHIGHSCORECODE 4
#define GETPERSONALSTATSCODE 5
#define JOINROOMCODE 6
#define CREATEROOMCODE 7
#define CLOSEROOMCODE 8
#define STARTGAMECODE 9
#define LEAVEROOMCODE 10
#define GETROOMSTATECODE 11

using std::string;
using json = nlohmann::json;

struct LoginResponse {
	unsigned int status;
};

struct SignupResponse {
	unsigned int status;
};

struct ErrorResponse {
	string message;
};

struct LogoutResponse {
	unsigned int status;
};

struct GetRoomResponse {
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<string> players;
};

struct GetHighScoreResponse {
	unsigned int status;
	std::vector<string> statistics;
};

struct GetPersonalStatsResponse {
	unsigned int status;
	std::vector<string> statistics;
};

struct JoinRoomResponse {
	unsigned int status;
};

struct CreateRoomResponse {
	unsigned int status;
};

struct CloseRoomResponse {
	unsigned int status;
};

struct StartGameResponse {
	unsigned int status;
};

struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<string> players;
	unsigned int AnswerCount;
	unsigned int answerTimeOut;
};

struct LeaveRoomResponse {
	unsigned int status;
};



static class JsonResponsePacketSerializer{
public:
	static Buffer serializeResponse(LoginResponse);
	static Buffer serializeResponse(SignupResponse);
	static Buffer serializeResponse(ErrorResponse);

	static Buffer serializeResponse(LogoutResponse);
	static Buffer serializeResponse(GetRoomResponse);
	static Buffer serializeResponse(GetPlayersInRoomResponse);
	static Buffer serializeResponse(GetHighScoreResponse);
	static Buffer serializeResponse(GetPersonalStatsResponse);
	static Buffer serializeResponse(JoinRoomResponse);
	static Buffer serializeResponse(CreateRoomResponse);

	static Buffer serializeResponse(CloseRoomResponse);
	static Buffer serializeResponse(StartGameResponse);
	static Buffer serializeResponse(GetRoomStateResponse);
	static Buffer serializeResponse(LeaveRoomResponse);

private:
	static void addJsonToBuffer(Buffer* buffer, json data);
};


