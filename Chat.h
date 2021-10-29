#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

struct UserLoginExp : public std::exception
{
    const char *what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public std::exception
{
    const char *what() const noexcept override { return "error: user name is busy"; }
};

class Chat
{
    bool _isChatWork = false;
    std::vector<User> _userList;
    std::vector<Message> _messageList;
    std::shared_ptr<User> _currentUser = nullptr;

    void initialization();
    void login();
    void signUp();
    void showChat() const;
    void changeName();
    void changePassword();

public:
    void start();

    std::vector<User> &getAllUsers() { return _userList; }
    std::vector<Message> &getAllMessages() { return _messageList; }

    bool isChatWork() const { return _isChatWork; }

    std::shared_ptr<User> getUserByLogin(const std::string &login) const;
    std::shared_ptr<User> getUserByName(const std::string &name) const;

    std::shared_ptr<User> getCurrentUser() const { return _currentUser; }

    void showLoginMenu();
    void showUserMenu();
    void showAllUsersName() const;

    void addMessage();
};