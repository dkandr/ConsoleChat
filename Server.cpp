#include <iostream>
#include "Server.h"
//#include "TextMessage.h"
//#include "VideoMessage.h"

void Server::initialization()
{
    _userList.push_back(User{"admin@localhost","admin","Admin", true});
    _userList.push_back(User{"dmitry@mail.ru","12345","Dima"});
    _userList.push_back(User{"vladimir@post.ru","qwerty","Vova"});
    _userList.push_back(User{"ekaterina@gmail.com","password","Katya"}); 
}

void Server::start()
{
    initialization();
}

void Server::addUser(User user)
{    
     _userList.push_back(user);
}

void Server::addMessage(Message message)
{    
     _messageList.push_back(message);
}

const User* Server::getUserByName(const std::string& name)
{
    for (auto& user: _userList)
    {
        if (name == user.getUserName()) return &user;
    }

    return nullptr;
}