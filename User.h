#pragma once
#include <string>

class User
{
private:
    const std::string _login;
    std::string _password;
    std::string _name;
    bool _isAdmin;
public:
    //User() = default;
    User(const std::string& login, const std::string& password, const std::string& name, bool isAdmin = false) 
        : _login(login), _password(password), _name(name), _isAdmin(isAdmin) {}

    //User(User &other) : _login(other._login), _password(other._password), _name(other._name) {}
 
    const std::string& getUserLogin() const { return _login; }
    const std::string& getUserName() const { return _name; }
};