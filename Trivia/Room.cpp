#include "Room.h"
#include <string>

RoomData& Room::getRoomData()
{
	return this->m_metadata;
}
Room::Room(RoomData data)
{
	this->m_metadata = data;
}

Room::Room(const Room& room)
{
	this->m_metadata = room.m_metadata;
	this->m_users = room.m_users;
}

void Room::addUser(LoggedUser user){

	if (this->m_users.size() >= this->m_metadata.maxPlayers) {
		std::cout << "ERROR: room is full\n";
	}
	else
	{
		this->m_users.push_back(user); 
	}
}

void Room::removeUser(LoggedUser user)
{
	auto it = this->m_users.begin();

	while (it != this->m_users.end())
	{
		if (it->getUsername() == user.getUsername())
		{
			this->m_users.erase(it);
			return;
		}
		it++;
	}

	std::cout << "ERROR: user does not exist\n";
}

vector<string> Room::getALLUsers() {

	std::vector<std::string> allUsers;
	for (auto user : this->m_users) 
	{
		allUsers.push_back(user.getUsername());
	}
	return allUsers;
}

