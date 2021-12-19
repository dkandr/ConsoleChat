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
    bool isChatWork_ = false;
    std::vector<User> users_;
    std::vector<Message> messages_;
    std::shared_ptr<User> currentUser_ = nullptr;

    void initialization();
    void login();
    void signUp();
    void showChat() const;
    void changeName();
    void changePassword();

public:
    void start();

    std::vector<User> &getAllUsers() { return users_; }
    std::vector<Message> &getAllMessages() { return messages_; }

    bool isChatWork() const { return isChatWork_; }

    std::shared_ptr<User> getUserByLogin(const std::string &login) const;
    std::shared_ptr<User> getUserByName(const std::string &name) const;

    std::shared_ptr<User> getCurrentUser() const { return currentUser_; }

    void showLoginMenu();
    void showUserMenu();
    void showAllUsersName() const;

    void addMessage();
};