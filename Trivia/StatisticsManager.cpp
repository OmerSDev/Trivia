#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* db)
{
    this->m_database = db;
}

StatisticsManager::~StatisticsManager()
{
}

vector<string> StatisticsManager::getHighScore()
{
    return this->m_database->getHighScores();
}

vector<string> StatisticsManager::getUserStatistics(string username)
{
    vector<string> stats;
    float avgTime = this->m_database->getPlayerAverageAnswerTime(username);
    int numCorrect = this->m_database->getNumOfCorrectAnswers(username);
    int numAnswers = this->m_database->getNumOfTotalAnswers(username);
    int numGames = this->m_database->getNumOfPlayerGames(username);
    int score = this->m_database->getPlayerScore(username);

    stats.push_back(std::to_string(avgTime));
    stats.push_back(std::to_string(numCorrect));
    stats.push_back(std::to_string(numAnswers));
    stats.push_back(std::to_string(numGames));
    stats.push_back(std::to_string(score));

    return stats;
}
