#include "RoomManager.h"

RoomManager::RoomManager(int lastID)
{
	this->lastID = lastID;
}

RoomManager::~RoomManager()
{
}

int RoomManager::createRoom(LoggedUser user, RoomData room) {
	room.id = this->lastID++;
	Room newRoom(room);
	newRoom.addUser(user);
	this->m_rooms.insert({ room.id, newRoom });
	return room.id;
}

void RoomManager::deleteRoom(int ID) {
	this->m_rooms.erase(this->m_rooms.find(ID));
}

unsigned int RoomManager::GetRoomState(int ID) {
	return this->m_rooms.find(ID)->second.getRoomData().isActive;
}

vector<RoomData> RoomManager::getRooms() {
	std::vector<RoomData> roomData_List;
	for (auto& room : this->m_rooms) {
		roomData_List.push_back(room.second.getRoomData());
	}

	return roomData_List;
}

Room& RoomManager::getRoom(int ID) {
	for (auto& room : this->m_rooms) {
		if (room.first == ID) {
			return room.second;
		}
	}

	Room r(RoomData({ 0, "", 0, 0, 0, 0 }));
	return r;
}
