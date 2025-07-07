#include "SqliteDatabase.h"
#include <io.h>


bool SqliteDatabase::createTables()
{
	char* errMessage = nullptr;
	int res = sqlite3_exec(this->_db, "CREATE TABLE USERS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"USERNAME TEXT NOT NULL,"
		"PASSWORD TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL);", nullptr, nullptr, &errMessage);
	if (res)
	{
		this->_db = nullptr;
		cerr << errMessage << endl;
		return true;
	}

	res = sqlite3_exec(this->_db, "CREATE TABLE QUESTIONS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"QUESTION TEXT NOT NULL,"
		"ANSWER1 TEXT NOT NULL,"
		"ANSWER2 TEXT NOT NULL,"
		"ANSWER3 TEXT NOT NULL,"
		"ANSWER4 TEXT NOT NULL,"
		"CORRECT_ANSWER INTEGER NOT NULL);", nullptr, nullptr, &errMessage);
	if (res)
	{
		this->_db = nullptr;
		cerr << errMessage << endl;
		return true;
	}


	res = sqlite3_exec(this->_db, "CREATE TABLE STATISTICS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
		"GAME_ID INTEGER NOT NULL,"
		"USERNAME TEXT NOT NULL,"
		"IS_CORRECT BOOLEAN NOT NULL,"
		"ANSWER_TIME FLOAT NOT NULL,"
		"SCORE INTEGER NOT NULL);", nullptr, nullptr, &errMessage);
	if (res)
	{
		this->_db = nullptr;
		cerr << errMessage << endl;
		return true;
	}
}

bool SqliteDatabase::open()
{
	int doesFileExist = _access(SQLITE_FILE_NAME, 0);

	int res = sqlite3_open(SQLITE_FILE_NAME, &(this->_db));

	if (res)
	{
		this->_db = nullptr;
		cerr << "ERROR: Couldn't open DB" << endl;
		return true;
	}

	if (doesFileExist)
	{
		res = this->createTables();
	}

    return this->updateQuestions() || res;
}

bool SqliteDatabase::close()
{
	int res = sqlite3_close(this->_db);
	this->_db = nullptr;
    return res;
}

int SqliteDatabase::doesUserExist(string username)
{
	bool exists = false;
	bool* pExists = &exists;
	char* errMessage = nullptr;
	string request = "SELECT * FROM USERS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), userExistCallback, (void*)pExists, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
    return exists;
}

int SqliteDatabase::doesPasswordMatch(string username, string password)
{
	string userPassword = "";
	string* pUserPassword = &userPassword;
	char* errMessage = nullptr;
	string request = "SELECT PASSWORD FROM USERS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), passwordCheckCallback, (void*)pUserPassword, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	if (userPassword == password)
	{
		return 1;
	}
	return 0;
}

int SqliteDatabase::addNewUser(string username, string password, string email)
{
	char* errMessage = nullptr;
	string request = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" + username + "', '" + password + "', '" + email + "');";
	int res = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return res;
}

float SqliteDatabase::getPlayerAverageAnswerTime(string username)
{
	float avg = 0.0;
	float* pAvg = &avg;
	char* errMessage = nullptr;
	string request = "SELECT avg(ANSWER_TIME) FROM STATISTICS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), avgCallback, (void*)pAvg, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return avg;
}

int SqliteDatabase::getNumOfCorrectAnswers(string username)
{
	int count = 0;
	int* pCount = &count;
	char* errMessage = nullptr;
	string request = "SELECT count(IS_CORRECT) FROM STATISTICS WHERE USERNAME LIKE '" + username + "' AND IS_CORRECT = 1;";
	int res = sqlite3_exec(this->_db, request.c_str(), intCallback, (void*)pCount, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return count;
}

int SqliteDatabase::getNumOfTotalAnswers(string username)
{
	int count = 0;
	int* pCount = &count;
	char* errMessage = nullptr;
	string request = "SELECT count(IS_CORRECT) FROM STATISTICS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), intCallback, (void*)pCount, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return count;
}

int SqliteDatabase::getNumOfPlayerGames(string username)
{
	int count = 0;
	int* pCount = &count;
	char* errMessage = nullptr;
	string request = "SELECT count(DISTINCT GAME_ID) FROM STATISTICS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), intCallback, (void*)pCount, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return count;
}

int SqliteDatabase::addStatistic(int gameId, string username, bool isCorrect, float answerTime)
{
	int score = 0;
	if (isCorrect)
	{
		score = (int)(answerTime < MAX_TIME_TO_LOWER_SCORE ? (MAX_SCORE - SCORE_PER_SEC * answerTime) : MIN_SCORE);
	}

	char* errMessage = nullptr;
	string request = "INSERT INTO STATISTICS (GAME_ID, USERNAME, IS_CORRECT, ANSWER_TIME, SCORE) VALUES (" + std::to_string(gameId) + ", '" + username + "', " + std::to_string((int)isCorrect) + ", " + std::to_string(answerTime) + ", " + std::to_string(score) + ");";
	int res = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return res;
}

list<Question> SqliteDatabase::getQuestions()
{
	list<Question> questions;
	list<Question>* pQuestions = &questions;
	char* errMessage = nullptr;
	string request = "SELECT * FROM QUESTIONS;";
	int res = sqlite3_exec(this->_db, request.c_str(), getQuestionsCallback, (void*)pQuestions, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return list<Question>();
	}
	return questions;
}

int SqliteDatabase::addQuestion(string question, string answer1, string answer2, string answer3, string answer4, int correctAnswer)
{
	char* errMessage = nullptr;
	string request = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) VALUES ('" + question + "', '" + answer1 + "', '" + answer2 + "', '" + answer3 + "', '" + answer4 + "', " + std::to_string(correctAnswer) + ");";
	int res = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return res;
}

int SqliteDatabase::updateQuestions()
{
	int res = 0;
	std::ifstream file(QUESTIONS_FILE_NAME);
	json data = json::parse(file);
	file.close();

	if (this->clearQuestions())
	{
		cerr << "Error trying to update questions" << endl;
		throw;
	}

	for (int i = 0; i < data["Questions"].size(); i++)
	{
		auto q = data["Questions"][i];
		res = this->addQuestion(q["question"], q["answers"][0], q["answers"][1], q["answers"][2], q["answers"][3], q["correctAnswer"]);
		if (res)
		{
			cerr << "Error trying to update questions" << endl;
			throw;
		}
	}

	return 0;
}

int SqliteDatabase::clearQuestions()
{
	char* errMessage = nullptr;
	string request = "DELETE FROM QUESTIONS;";
	int res = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	
	request = "UPDATE SQLITE_SEQUENCE SET SEQ=0 WHERE NAME='QUESTIONS';";
	res = sqlite3_exec(this->_db, request.c_str(), nullptr, nullptr, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return res;
}

int SqliteDatabase::getPlayerScore(string username)
{
	int score = 0;
	int* pScore = &score;
	char* errMessage = nullptr;
	string request = "SELECT sum(SCORE) FROM STATISTICS WHERE USERNAME LIKE '" + username + "';";
	int res = sqlite3_exec(this->_db, request.c_str(), intCallback, (void*)pScore, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return score;
}

vector<string> SqliteDatabase::getHighScores()
{
	vector<string> users;
	vector<string>* pUsers = &users;
	char* errMessage = nullptr;
	string request = "SELECT USERNAME, sum(SCORE) FROM STATISTICS GROUP BY USERNAME ORDER BY sum(SCORE) DESC LIMIT 3;";
	int res = sqlite3_exec(this->_db, request.c_str(), highestSCorersCallback, (void*)pUsers, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return vector<string>();
	}

	return users;
}

unsigned int SqliteDatabase::getCurrentId()
{
	unsigned int id = 0;
	unsigned int* pId = &id;
	char* errMessage = nullptr;
	string request = "SELECT GAME_ID FROM STATISTICS LIKE ORDER BY GAME_ID DESC LIMIT 1;";
	int res = sqlite3_exec(this->_db, request.c_str(), intCallback, (void*)pId, &errMessage);
	if (res)
	{
		cerr << errMessage;
		return -1;
	}
	return id;
}
