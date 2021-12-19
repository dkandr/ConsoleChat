#pragma once
#include <string>
#include "sha1.h"

class User
{
    const std::string _login;
    uint* _password;
    std::string _name;
    const bool _isAdmin;

public:
    User(const std::string &login, const std::string &password, const std::string &name, bool isAdmin = false)
        : _login(login), _name(name), _isAdmin(isAdmin) 
    {
        const char *str = password.c_str();
        _password = sha1(str, password.length());
    }

    const std::string &getUserLogin() const { return _login; }

    bool checkUserPassword(const std::string password) const 
    {
        const char *str = password.c_str();
        
        uint* digest = sha1(str, password.length());
    
        bool cmpHashes = compareSHA(_password, digest);
        delete[] digest;

        return cmpHashes;
    }

    void setUserPassword(const std::string &password) 
    { 
        const char *str = password.c_str();
        _password = sha1(str, password.length());
    }

    const std::string &getUserName() const { return _name; }
    void setUserName(const std::string &name) { _name = name; }

    bool getIsAdmin() const { return _isAdmin; }
};