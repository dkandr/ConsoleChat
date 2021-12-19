#pragma once
#include <string>
#include "sha1.h"

class User
{
    const std::string login_;
    std::string name_;
    const bool isAdmin_;
    uint* password_;
 
public:
    User(const std::string &login, const std::string &password, const std::string &name, bool isAdmin = false)
        : login_(login), name_(name), isAdmin_(isAdmin) 
    {
        const char *str = password.c_str();
        password_ = sha1(str, password.length());
    }

    const std::string &getUserLogin() const { return login_; }

    bool checkUserPassword(const std::string password) const 
    {
        const char *str = password.c_str();
        
        uint* digest = sha1(str, password.length());
    
        bool cmpHashes = compareSHA(password_, digest);
        delete[] digest;

        return cmpHashes;
    }

    void setUserPassword(const std::string &password) 
    { 
        const char *str = password.c_str();
        password_ = sha1(str, password.length());
    }

    const std::string &getUserName() const { return name_; }
    void setUserName(const std::string &name) { name_ = name; }

    bool getIsAdmin() const { return isAdmin_; }
};