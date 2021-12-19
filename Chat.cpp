#include <iostream>
#include "Chat.h"

void Chat::initialization()
{
    //добавляем двух пользователей
    users_.push_back(User{"admin@localhost", "admin", "Admin", true});
    users_.push_back(User{"demo@localhost", "demo", "Demo"});
}

void Chat::start()
{
    initialization();
    isChatWork_ = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string &login) const
{
    for (auto &user : users_)
    {
        if (login == user.getUserLogin())
            return std::make_shared<User>(user);
    }

    return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string &name) const
{
    for (auto &user : users_)
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

        currentUser_ = getUserByLogin(login);

        if (currentUser_ == nullptr || !(currentUser_ -> checkUserPassword(password)))
        {
            currentUser_ = nullptr;

            std::cout << "login failed..." << std::endl;
            std::cout << "(0)exit or (any key)repeat: ";
            std::cin >> operation;

            if (operation == '0')
                break;
        }

    } while (!currentUser_);
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
    users_.push_back(user);
    currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() const
{
    std::string from;
    std::string to;

    std::cout << "--- Chat ---" << std::endl;

    for (auto &mess : messages_)
    {

        //Показываем сообщения: от текущего пользователя, для него и для всем
        if (currentUser_ -> getUserLogin() == mess.getFrom() || currentUser_ -> getUserLogin() == mess.getTo() || mess.getTo() == "all")
        {
            //подменяем для себя имя на me
            from = (currentUser_ -> getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();

            if (mess.getTo() == "all")
            {
                to = "(all)";
            }
            else
            {
                to = (currentUser_ -> getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
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

    currentUser_ -> setUserName(newName);
}

void Chat::changePassword()
{
    std::string newPassword;

    std::cout << "New password: ";
    std::cin >> newPassword;

    currentUser_ -> setUserPassword(newPassword);
}

void Chat::showLoginMenu()
{
    currentUser_ = nullptr;

    char operation;

    do
    {
        std::cout << "\033[33m" << "(1)Login" << std::endl;
        std::cout << "(2)SignUp" << std::endl;
        std::cout << "\033[36m" << ">> " << "\033[0m";
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

    } while (!currentUser_);
}

void Chat::showUserMenu()
{
    char operation;

    std::cout << "Hi, " << currentUser_ -> getUserName() << std::endl;

    //Выполняем цикл, пока не выполнится пункт (0)Logout
    do
    {
        std::cout << "Menu: (1)Show chat | (2)Add message | (3)Users | (7)Change name | (8)Change password | (0)Logout";

        /* для пользователя с правами admin дабавляем возможность остановить программу */
        if (currentUser_ -> getIsAdmin())
            std::cout << " | (s)Shutdown";

        std::cout << std::endl
                  << ">> ";
        std::cin >> operation;

        if (currentUser_ -> getIsAdmin() && operation == 's')
        {
            currentUser_ = nullptr;
            isChatWork_ = false;
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
            currentUser_ = nullptr;
            break;
        default:
            std::cout << "unknown choice.." << std::endl;
            break;
        }

    } while (currentUser_);
}

void Chat::showAllUsersName() const
{
    std::cout << "--- Users ---" << std::endl;
    for (auto &user : users_)
    {
        std::cout << user.getUserName();

        if (currentUser_ -> getUserLogin() == user.getUserLogin())
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
        messages_.push_back(Message{currentUser_ -> getUserLogin(), "all", text});
    else
        messages_.push_back(Message{currentUser_ -> getUserLogin(), getUserByName(to)->getUserLogin(), text});
}