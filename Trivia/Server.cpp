#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>


static const unsigned short PORT = 8326;
static const unsigned int IFACE = 0;

using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;


Server::Server() : m_handlerFactory(RequestHandlerFactory(nullptr))
{
	this->m_database = new SqliteDatabase();
	if (this->m_database->open())
	{
		delete this->m_database;
		throw;
	}
	this->m_handlerFactory = RequestHandlerFactory(this->m_database);

	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	this->m_database->close();
	delete this->m_database;

	TRACE(__FUNCTION__ " closing accepting socket");

	try
	{

		::closesocket(_socket);
	}
	catch (...) {}
}

void Server::serve()
{
	bindAndListen();

	std::thread commands(&Server::getCommands, this);
	commands.detach();

	while (true)
	{

		TRACE("accepting client...");
		acceptClient();
	}
}


void Server::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;

	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void Server::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");

	std::thread tr(&Server::clientHandler, this, client_socket);
	tr.detach();

}



void Server::clientHandler(const SOCKET client_socket)
{
	string username = "";
	int id = client_socket;
	RequestHandler* handler = this->m_handlerFactory.createLoginRequestHandler();
	bool loggedIn = false;
	this->_clients.insert(std::pair<SOCKET, RequestHandler*>(client_socket, handler));
	RequestInfo* currRcvMsg;
	RequestResult result;
	result.newHandler = handler;
	char* arr;
	try
	{
		while (handler)
		{
			this->_clients[client_socket] = handler;
			currRcvMsg = build_receive_message(client_socket);
			result = handler->handleRequest(*currRcvMsg);

			delete handler;
			handler = result.newHandler;
			this->_clients[client_socket] = handler;

			arr = new char[result.response.size() + 1];

			std::copy(result.response.begin(), result.response.end(), arr);
			arr[result.response.size()] = 0;

			send(client_socket, arr, result.response.size(), 0);


		}


	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catch in function clientHandler. socket=" << client_socket << ", what=" << e.what() << std::endl;
		TRACE("Recieved exit message from client");

		safeDeleteUser(client_socket);
	}
	closesocket(client_socket);
}

RequestInfo* Server::build_receive_message(const SOCKET client_socket)
{
	RequestInfo* msg = new RequestInfo();
	Buffer buffer;
	int size = 0;
	char* str = nullptr;

	msg->receivalTime = time(0);
	str = Helper::getStringPartFromSocket(client_socket, 1);
	msg->id = (unsigned char)str[0];
	delete[] str;
	str = Helper::getStringPartFromSocket(client_socket, 4);
	memcpy(&size, str, 4);
	delete str;
	str = Helper::getStringPartFromSocket(client_socket, size);

	for (int i = 0; i < size; i++)
	{
		buffer.push_back(str[i]);
	}

	msg->buffer = buffer;

	return msg;

}

void Server::safeDeleteUser(const SOCKET id)
{
	try
	{
		if (string(typeid(*(this->_clients[id])).name()).find("LoginRequestHandler") == string::npos)
		{
			this->m_handlerFactory.getLoginManager().logout((this->_clients.at(id))->getUsername());
		}

		for (auto roomData : this->m_handlerFactory.getRoomManager().getRooms())
		{
			Room& room = this->m_handlerFactory.getRoomManager().getRoom(roomData.id);
			vector<string> users = room.getALLUsers();
			if (std::find(users.begin(), users.end(), this->_clients[id]->getUsername()) != users.end())
			{
				room.removeUser(this->_clients[id]->getUsername());
			}
			if (room.getALLUsers().size() == 0)
			{
				this->m_handlerFactory.getRoomManager().deleteRoom(roomData.id);
			}
		}

		std::map<SOCKET, RequestHandler*>::iterator iter;
		for (auto it = this->_clients.begin(); it != this->_clients.end(); it++)
		{
			if (it->first == id)
			{
				iter = it;

			}
		}
		this->_clients.erase(iter);
	}
	catch (...) {}

}




void Server::getCommands()
{
	string command = "";
	while (true)
	{
		std::getline(std::cin, command);

		if (command == "EXIT")
		{
			this->closeAll();
			exit(0);
		}
		else if (command == "UPDATE QUESTIONS")
		{
			this->m_database->updateQuestions();
		}
	}
}

void Server::closeAll()
{
	for (auto it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		safeDeleteUser((*it).first);
		closesocket((*it).first);
	}
}