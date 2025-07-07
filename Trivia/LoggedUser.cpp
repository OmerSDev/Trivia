#include "LoggedUser.h"

LoggedUser::LoggedUser(string username)
{
    this->m_username = username;
}

LoggedUser::~LoggedUser()
{
}

string LoggedUser::getUsername()
{
    return this->m_username;
}

bool LoggedUser::operator==(LoggedUser other)
{
    return this->m_username == other.m_username;
}
