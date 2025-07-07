#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "LoggedUser.h"
#include "Room.h"
#include <map>


static class RoomManager 
{
public:

	RoomManager(int lastID);
	~RoomManager();

	int createRoom(LoggedUser user, RoomData room);
	void deleteRoom(int ID);
	unsigned int GetRoomState(int ID);
	vector<RoomData> getRooms();
	Room& getRoom(int ID);


private:
	std::map<int, Room> m_rooms;
	int lastID;
};