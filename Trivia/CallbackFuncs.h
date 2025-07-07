#pragma once
#include <iostream>
#include <vector>
#include "Question.h"
#include <list>
#include <string>

#define MAX_SCORE 1000
#define SCORE_PER_SEC 30
#define MIN_SCORE 100
#define MAX_TIME_TO_LOWER_SCORE 30

using std::vector;
using std::list;
using std::string;

int userExistCallback(void* data, int argc, char** argv, char** azColName);
int passwordCheckCallback(void* data, int argc, char** argv, char** azColName);

int avgCallback(void* data, int argc, char** argv, char** azColName);
int intCallback(void* data, int argc, char** argv, char** azColName);

int getQuestionsCallback(void* data, int argc, char** argv, char** azColName);

int highestSCorersCallback(void* data, int argc, char** argv, char** azColName);