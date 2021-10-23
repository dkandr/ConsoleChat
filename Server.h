#pragma once
#include <vector>
#include "Message.h"

class Server
{
private:
    bool _isServerWork = false;
    std::vector<User*> _userList;
    std::vector<Message> _messageList;
    User* _currentUser = nullptr;

    void initialization();
    void login();
    void signUp();
    void showChat() const;
    void changeName();
    void changePassword();

public:
    Server() = default; 
    ~Server();

    void start();

    std::vector<User*> getAllUsers() const { return _userList; }
    std::vector<Message> getAllMessages() const { return _messageList; }

    bool isServerWork() const { return _isServerWork; }

    User* getUserByName(const std::string& name) const;
    User* getUserByLogin(const std::string& login) const;

    User* getCurrentUser() const { return _currentUser; }

    void showLoginMenu();
    void showUserMenu();
    void showAllUsersName() const;

    void addMessage();
};