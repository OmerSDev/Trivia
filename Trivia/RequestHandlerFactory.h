#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "StatisticsManager.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser user, Room room);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser user, Room room);
	
private:
	StatisticsManager m_statisticsManager;
	RoomManager m_roomManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};

