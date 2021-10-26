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
    User(const std::string& login, const std::string& password, const std::string& name, bool isAdmin = false) 
        : _login(login), _password(password), _name(name), _isAdmin(isAdmin) {}
  
    const std::string& getUserLogin() const { return _login; }

    const std::string& getUserPasword() const { return _password; }
    void setUserPassword(const std::string& password) { _password = password; }

    const std::string& getUserName() const { return _name; }
    void setUserName(const std::string& name) { _name = name; }

    bool getIsAdmin() const { return _isAdmin; }
    void setIsAdmin(bool isAdmin) { _isAdmin = isAdmin; }
};