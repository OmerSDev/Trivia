#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "CallbackFuncs.h"
#include <string>
#include <vector>
#include "json.hpp"
#include <fstream>

#define SQLITE_FILE_NAME "triviaDB.sqlite"
#define QUESTIONS_FILE_NAME "Questions.json"

using nlohmann::json;

class SqliteDatabase : public IDatabase
{
private:
	sqlite3* _db;

	bool createTables();

public:
	bool open() override;
	bool close() override;
	int doesUserExist(string username) override;
	int doesPasswordMatch(string username, string password) override;
	int addNewUser(string username, string password, string email) override;

	float getPlayerAverageAnswerTime(string username) override;
	int getNumOfCorrectAnswers(string username) override;
	int getNumOfTotalAnswers(string username) override;
	int getNumOfPlayerGames(string username) override;
	int addStatistic(int gameId, string username, bool isCorrect, float answerTime) override;

	list<Question> getQuestions() override;
	int addQuestion(string question, string answer1, string answer2, string answer3, string answer4, int correctAnswer) override;
	int updateQuestions() override;
	int clearQuestions() override;

	int getPlayerScore(string username) override;
	vector<string> getHighScores() override;

	unsigned int getCurrentId() override;
};