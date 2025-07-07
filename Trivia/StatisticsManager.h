#pragma once
#include "SqliteDatabase.h"
#include <vector>
#include <string>

using std::vector;

class StatisticsManager
{
private:

	IDatabase* m_database;

public:

	StatisticsManager(IDatabase* db);
	~StatisticsManager();

	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);
};