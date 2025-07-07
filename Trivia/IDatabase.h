#pragma once
#include <iostream>
#include <list>
#include <vector>
#include "Question.h"

using std::vector;
using std::list;
using std::string;
using std::endl;
using std::cout;
using std::cerr;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(string username) = 0;
	virtual int doesPasswordMatch(string username, string password) = 0;
	virtual int addNewUser(string username, string password, string email) = 0;
	
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;
	virtual int addStatistic(int gameId, string username, bool isCorrect, float answerTime) = 0;

	virtual list<Question> getQuestions() = 0;
	virtual int addQuestion(string question, string answer1, string answer2, string answer3, string answer4, int correctAnswer) = 0;
	virtual int updateQuestions() = 0;
	virtual int clearQuestions() = 0;
	virtual int getPlayerScore(string username) = 0;
	virtual vector<string> getHighScores() = 0;

	virtual unsigned int getCurrentId() = 0;
};