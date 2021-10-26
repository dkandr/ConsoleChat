#include "Server.h"

int main()1
{
    Server chat;

    chat.start();

    //два цикла: 1ый(внешний) для входа в систему, 2ой(внутренний) для работы с чатом
    do {
        chat.showLoginMenu();

        do {
            chat.showUserMenu();
        } while (chat.getCurrentUser());

    } while (chat.isServerWork());

    return 0;
}