#include "JsonRequestPacketDeserializer.h"

json JsonRequestPacketDeserializer::deserialize(Buffer buffer)
{
	char* strJson = new char[buffer.size() + 1];

	std::copy(buffer.begin(), buffer.end(), strJson);
	strJson[buffer.size()] = 0;


	json dataJson = json::parse(strJson);

	delete[] strJson;
	return dataJson;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer)
{
	LoginRequest ret;

	json dataJson = deserialize(buffer);

	ret.username = dataJson["username"];
	ret.password = dataJson["password"];

	return ret;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer buffer)
{
	SignupRequest ret;
	json dataJson = deserialize(buffer);

	ret.username = dataJson["username"];
	ret.password = dataJson["password"];
	ret.email = dataJson["mail"];

	return ret;
}

GetPlayersInRommRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRommRequest(Buffer buffer)
{
	GetPlayersInRommRequest ret;
	json dataJson = deserialize(buffer);

	ret.roomid = stoi(string(dataJson["roomid"]));

	return ret;
}

JoinRommRequest JsonRequestPacketDeserializer::deserializeJoinRommRequest(Buffer buffer)
{
	JoinRommRequest ret;
	json dataJson = deserialize(buffer);

	ret.roomid = stoi(string(dataJson["roomid"]));

	return ret;
}

CreateRommRequest JsonRequestPacketDeserializer::deserializeCreateRommRequest(Buffer buffer)
{
	CreateRommRequest ret;
	json dataJson = deserialize(buffer);

	ret.roomName = dataJson["roomName"];
	ret.maxUsers = stoi(string(dataJson["maxUsers"]));
	ret.questionCount = stoi(string(dataJson["questionCount"]));
	ret.answerTimeout = stoi(string(dataJson["answerTimeout"]));

	return ret;
}