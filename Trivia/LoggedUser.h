#pragma once
#include <iostream>
using std::string;

class LoggedUser
{
private:
	string m_username;

public:
	LoggedUser(string username);
	~LoggedUser();
	string getUsername();
	bool operator==(LoggedUser other);
};