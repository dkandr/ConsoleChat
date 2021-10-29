#include <iostream>
#include "Chat.h"

void Chat::initialization()
{
    //добавляем двух пользователей
    _userList.push_back(User{"admin@localhost", "admin", "Admin", true});
    _userList.push_back(User{"demo@localhost", "demo", "Demo"});
}

void Chat::start()
{
    initialization();
    _isChatWork = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string &login) const
{
    for (auto &user : _userList)
    {
        if (login == user.getUserLogin())
            return std::make_shared<User>(user);
    }

    return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string &name) const
{
    for (auto &user : _userList)
    {
        if (name == user.getUserName())
            return std::make_shared<User>(user);
    }

    return nullptr;
}

void Chat::login()
{
    std::string login, password;
    char operation;

    do
    {
        std::cout << "login: ";
        std::cin >> login;
        std::cout << "password: ";
        std::cin >> password;

        _currentUser = getUserByLogin(login);

        if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
        {
            _currentUser = nullptr;

            std::cout << "login failed..." << std::endl;
            std::cout << "(0)exit or (any key)repeat: ";
            std::cin >> operation;

            if (operation == '0')
                break;
        }

    } while (!_currentUser);
}

void Chat::signUp()
{
    std::string login, password, name;

    std::cout << "login: ";
    std::cin >> login;
    std::cout << "password: ";
    std::cin >> password;
    std::cout << "name: ";
    std::cin >> name;

    if (getUserByLogin(login) || login == "all")
    {
        throw UserLoginExp();
    }
    
    if (getUserByName(name) || name == "all")
    {
        throw UserNameExp();
    }

    User user = User(login, password, name);
    _userList.push_back(user);
    _currentUser = std::make_shared<User>(user);
}

void Chat::showChat() const
{
    std::string from;
    std::string to;

    std::cout << "--- Chat ---" << std::endl;

    for (auto &mess : _messageList)
    {

        //Показываем сообщения: от текущего пользователя, для него и для всем
        if (_currentUser->getUserLogin() == mess.getFrom() || _currentUser->getUserLogin() == mess.getTo() || mess.getTo() == "all")
        {
            //подменяем для себя имя на me
            from = (_currentUser->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();

            if (mess.getTo() == "all")
            {
                to = "(all)";
            }
            else
            {
                to = (_currentUser->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
            }

            std::cout << "Message from " << from << " to " << to << std::endl;
            std::cout << "text: " << mess.getText() << std::endl;
        }
    }

    std::cout << "------------" << std::endl;
}

void Chat::changeName()
{
    std::string newName;

    std::cout << "New name: ";
    std::cin >> newName;

    if (getUserByName(newName) || newName == "all")
    {
        throw UserNameExp();
    }

    _currentUser->setUserName(newName);
}

void Chat::changePassword()
{
    std::string newPassword;

    std::cout << "New password: ";
    std::cin >> newPassword;

    _currentUser->setUserPassword(newPassword);
}

void Chat::showLoginMenu()
{
    _currentUser = nullptr;

    char operation;

    do
    {
        std::cout << "(1)Login" << std::endl;
        std::cout << "(2)SignUp" << std::endl;
        std::cout << ">> ";
        std::cin >> operation;

        switch (operation)
        {
        case '1':
            login();
            break;
        case '2':
            try
            {
                signUp();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        default:
            std::cout << "1 or 2..." << std::endl;
            break;
        }

    } while (!_currentUser);
}

void Chat::showUserMenu()
{
    char operation;

    std::cout << "Hi, " << _currentUser->getUserName() << std::endl;

    //Выполняем цикл, пока не выполнится пункт (0)Logout
    do
    {
        std::cout << "Menu: (1)Show chat | (2)Add message | (3)Users | (7)Change name | (8)Change password | (0)Logout";

        /* для пользователя с правами admin дабавляем возможность остановить программу */
        if (_currentUser->getIsAdmin())
            std::cout << " | (s)Shutdown";

        std::cout << std::endl
                  << ">> ";
        std::cin >> operation;

        if (_currentUser->getIsAdmin() && operation == 's')
        {
            _currentUser = nullptr;
            _isChatWork = false;
            break;
        }

        switch (operation)
        {
        case '1':
            showChat();
            break;
        case '2':
            addMessage();
            break;
        case '3':
            showAllUsersName();
            break;
        case '7':
            try
            {
                changeName();
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
            break;
        case '8':
            changePassword();
            break;
        case '0':
            _currentUser = nullptr;
            break;
        default:
            std::cout << "unknown choice.." << std::endl;
            break;
        }

    } while (_currentUser);
}

void Chat::showAllUsersName() const
{
    std::cout << "--- Users ---" << std::endl;
    for (auto &user : _userList)
    {
        std::cout << user.getUserName();

        if (_currentUser->getUserLogin() == user.getUserLogin())
            std::cout << "(me)";

        std::cout << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

void Chat::addMessage()
{
    std::string to, text;

    std::cout << "To (name or all): ";
    std::cin >> to;
    std::cout << "Text: ";
    std::cin.ignore();
    getline(std::cin, text);

    if (!(to == "all" || getUserByName(to))) //если не удалось найти получателя по имени
    {
        std::cout << "error send message: cann't find " << to << std::endl;
        return;
    }

    if (to == "all")
        _messageList.push_back(Message{_currentUser->getUserLogin(), "all", text});
    else
        _messageList.push_back(Message{_currentUser->getUserLogin(), getUserByName(to)->getUserLogin(), text});
}