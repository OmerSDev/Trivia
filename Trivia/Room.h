#pragma once
#include "LoggedUser.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;

struct RoomData 
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};


static class Room 
{
public:

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);

	RoomData& getRoomData();
	Room(RoomData data);
	Room(const Room& room);

	vector<string> getALLUsers();

private:
	vector<LoggedUser> m_users;
	RoomData m_metadata;
};