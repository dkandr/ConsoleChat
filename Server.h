#pragma once
#include <vector>
#include "User.h"
#include "Message.h"

class Server
{
private:
    bool _isServerWork = false;
    bool _isUserLogin = false;
    std::vector<User> _userList;
    std::vector<Message> _messageList;
    User* _currentUser = nullptr;

    void initialization();

public:
    Server() = default; 
    ~Server() = default;

    void start();

    void showLoginMenu() const;

    const std::vector<User>& getAllUsers() { return _userList; }
    const std::vector<Message>& getAllMessages() { return _messageList; }

    void addUser(User user);
    void addMessage(Message message);

    const User* getUserByName(const std::string& name);

    const User* getCurrentUser() const { return _currentUser; }
};