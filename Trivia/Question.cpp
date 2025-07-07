#include "Question.h"

Question::Question(string question, vector<string> possibleAnswers, int correctAnswer)
{
    this->m_question = question;
    this->m_possibleAnswers = possibleAnswers;
    this->m_correctAnswer = correctAnswer;
}

Question::~Question()
{
}

string Question::getQuestion()
{
    return this->m_question;
}

vector<string> Question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
    return this->m_correctAnswer;
}
