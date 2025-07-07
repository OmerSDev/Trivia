#pragma once

#include <vector>
#include <ctime>
#include <iostream>

using std::string;
typedef std::vector<unsigned char> Buffer;

class RequestHandler;

struct RequestInfo
{
	int id;	
	time_t receivalTime;
	Buffer buffer;
};

struct RequestResult
{
	Buffer response;
	RequestHandler* newHandler;
};

class RequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
	virtual string getUsername() = 0;
};