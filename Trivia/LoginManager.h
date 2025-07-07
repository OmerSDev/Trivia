#pragma once
#include <vector>
#include "LoggedUser.h"
#include "SqliteDatabase.h"
#include <algorithm>

#define LOGGED_IN 0
#define WRONG_PASSWORD 49
#define INVALID_USER 111
#define USER_ALREADY_ACTIVE 10
#define SIGNED_UP 31
#define USER_ALREADY_EXISTS 30
#define LOGGED_OUT 33
#define USER_NOT_ACTIVE 34

using std::vector;

class LoginManager
{
private:
	vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;

public:
	LoginManager(IDatabase* db);
	~LoginManager();
	int login(string username, string password);
	int signup(string username, string password, string email);
	int logout(string username);
};