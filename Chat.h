#pragma once
#include <vector>
#include <exception>
#include "Message.h"

struct UserLoginExp : public std::exception
{
    const char* what() const noexcept override { return "error: user login is busy"; }
};


struct UserNameExp : public std::exception
{
    const char* what() const noexcept override { return "error: user name is busy"; }
};


class Chat
{
    bool _isChatWork = false;
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
    Chat() = default; 
    ~Chat();

    void start();

    std::vector<User*> getAllUsers() const { return _userList; }
    std::vector<Message> getAllMessages() const { return _messageList; }

    bool isChatWork() const { return _isChatWork; }

    User* getUserByName(const std::string& name) const;
    User* getUserByLogin(const std::string& login) const;

    User* getCurrentUser() const { return _currentUser; }

    void showLoginMenu();
    void showUserMenu();
    void showAllUsersName() const;

    void addMessage();
};