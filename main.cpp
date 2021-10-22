#include "Server.h"

int main()
{
    Server chat;

    chat.start();

    std::cout << "Program start.." << std::endl;

    for (auto& user : chat.getAllUsers())
    {
        std::cout <<  user.getUserLogin() << " - " << user.getUserName() << std::endl;    
    }

    const User* u1 = chat.getUserByName("Admin");
    const User* u2 = chat.getUserByName("Dima");

    const std::string text = "hi all!!!";

    Message m {u1, u2, text};
    Message m2 {u1, nullptr, text};

    chat.addMessage(m);
    chat.addMessage(m2);

    std::string from;
    std::string to;

    for (auto& mess : chat.getAllMessages())
    {
        from = (*mess.getFrom()).getUserName();

        if (mess.getTo() == nullptr)
        {
            to = "(all)";
        }
        else to = mess.getTo()->getUserName();

        std::cout << "Message from " << from << " to " << to << std::endl;
        std::cout << "text: " << mess.getText() << std::endl;
    }


    return 0;
}