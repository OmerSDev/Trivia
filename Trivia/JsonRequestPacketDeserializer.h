#pragma once
#include "json.hpp"
#include "LoginRequestHandler.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using nlohmann::json;
using std::string;

struct LoginRequest
{
	string username;
	string password;
};
struct SignupRequest
{
	string username;
	string password;
	string email;
};

struct GetPlayersInRommRequest {
	unsigned int roomid;
};
struct JoinRommRequest {
	unsigned int roomid;
};
struct CreateRommRequest {
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

class JsonRequestPacketDeserializer
{
private:
	static json deserialize(Buffer buffer);

public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);

	static GetPlayersInRommRequest deserializeGetPlayersInRommRequest(Buffer buffer);
	static JoinRommRequest deserializeJoinRommRequest(Buffer buffer);
	static CreateRommRequest deserializeCreateRommRequest(Buffer buffer);
};