#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory) : RequestHandler(), m_handlerFactory(factory), m_loginManager(factory.getLoginManager())
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGINCODE || info.id == SIGNUPCODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    RequestResult result;
    if (isRequestRelevant(info))
    {
        try
        {
            if (info.id == LOGINCODE)
            {
                result = this->login(info);

            }
            else
            {
                result = this->signup(info);
            }
        }
        catch (const std::exception& e)
        {
            result = this->error();
        }
    }
    else
    {
        result = this->error();
    }
    return result;
}

string LoginRequestHandler::getUsername()
{
    return string();
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
    Buffer buffer;
    RequestHandler* newHandler = nullptr;
    LoginRequest userInfo = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
    LoginResponse logRes;
    logRes.status = m_loginManager.login(userInfo.username, userInfo.password);
    buffer = JsonResponsePacketSerializer::serializeResponse(logRes);
    if (logRes.status == LOGGED_IN)
    {
        newHandler = this->m_handlerFactory.createMenuRequestHandler(LoggedUser(userInfo.username));
    }
    else
    {
        newHandler = this->m_handlerFactory.createLoginRequestHandler();
    }
    RequestResult requestRes = { buffer, newHandler };
    return requestRes;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
    Buffer buffer;
    RequestHandler* newHandler = nullptr;
    SignupRequest userInfo = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
    SignupResponse signRes;
    signRes.status = m_loginManager.signup(userInfo.username, userInfo.password, userInfo.email);
    buffer = JsonResponsePacketSerializer::serializeResponse(signRes);
    newHandler = this->m_handlerFactory.createLoginRequestHandler();
    RequestResult requestRes = { buffer, newHandler };
    return requestRes;
}

RequestResult LoginRequestHandler::error()
{
    ErrorResponse errorRes;
    Buffer buffer;
    RequestHandler* newHandler = nullptr;
    errorRes.message = "Error: Invalid Request";
    buffer = JsonResponsePacketSerializer::serializeResponse(errorRes);
    RequestResult requestRes = { buffer, newHandler };
    return requestRes;
}