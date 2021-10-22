#pragma once
#include <iostream>
#include <string>
#include "User.h"

class Message
{
private:
    const User* _from = nullptr; // использую указатель а не ссылки,
    const User* _to = nullptr;   // потому что _to может быть nullptr
    std::string _text;

public:
    Message(const User* from, const User* to, const std::string& text) : _from(from), _to(to), _text(text) {}

    const User* getFrom() const { return _from; }
    const User* getTo() const { return _to; }
    const std::string getText() const { return _text; }

    //virtual void Show() = 0;
};