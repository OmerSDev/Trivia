#include "CallbackFuncs.h"

int userExistCallback(void* data, int argc, char** argv, char** azColName)
{
    *((bool*)data) = true;
    return 0;
}

int passwordCheckCallback(void* data, int argc, char** argv, char** azColName)
{
    for (int i = 0; i < argc; i++)
    {
        if (std::string(azColName[i]) == "PASSWORD")
        {
            *((string*)data) = argv[i];
        }
    }
    return 0;
}

int avgCallback(void* data, int argc, char** argv, char** azColName)
{
    if (argv[0] != nullptr) {
        *((float*)data) = atof(argv[0]);
    }
    return 0;
}

int intCallback(void* data, int argc, char** argv, char** azColName)
{
    if (argv[0] != nullptr) {
        *((int*)data) = atoi(argv[0]);
    }
    return 0;
}

int getQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
    string question = "";
    vector<string> possibleAnswers;
    int correctAnswer = 0;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == "QUESTION")
        {
            question = argv[i];
        }
        else if (string(azColName[i]).rfind("ANSWER", 0) == 0)
        {
            possibleAnswers.push_back(argv[i]);
        }
        else if (azColName[i] == "CORRECT_ANSWER")
        {
            correctAnswer = atoi(argv[i]);
        }
    }
    ((list<Question>*)data)->push_back(Question(question, possibleAnswers, correctAnswer));
    return 0;
}

int highestSCorersCallback(void* data, int argc, char** argv, char** azColName)
{
    string str = string(argv[0]) + ": " + string(argv[1]);
    ((vector<string>*)data)->push_back(str);
    return 0;
}
