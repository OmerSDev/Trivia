#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Question
{
private:
	string m_question;
	vector<string> m_possibleAnswers;
	int m_correctAnswer;

public:
	Question(string question, vector<string> possibleAnswers, int correctAnswer);
	~Question();

	string getQuestion();
	vector<string> getPossibleAnswers();
	int getCorrectAnswerId();

};