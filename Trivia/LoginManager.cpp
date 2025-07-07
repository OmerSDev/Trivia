#include "LoginManager.h"


LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;
}

LoginManager::~LoginManager()
{
}

int LoginManager::login(string username, string password)
{

	if (this->m_database->doesUserExist(username) && std::find(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), LoggedUser(username)) == this->m_loggedUsers.end())
	{
		if (this->m_database->doesPasswordMatch(username, password))
		{
			this->m_loggedUsers.push_back(LoggedUser(username));
			return LOGGED_IN;
		}
		else
		{
			return WRONG_PASSWORD;
		}
	}
	else if (!(this->m_database->doesUserExist(username)))
	{
		return INVALID_USER;
	}

	return USER_ALREADY_ACTIVE;
}

int LoginManager::signup(string username, string password, string email)
{
	if (!(this->m_database->doesUserExist(username)))
	{
		this->m_database->addNewUser(username, password, email);
		return SIGNED_UP;
	}
	return USER_ALREADY_EXISTS;

}

int LoginManager::logout(string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if ((*it).getUsername() == username)
		{
			this->m_loggedUsers.erase(it);
			return LOGGED_OUT;
		}
	}
	return USER_NOT_ACTIVE;
}