#include "Server.h"

int main()
{
    Server chat;

    chat.start();

    //2 цикла: 1ый для входа в систему, 2ой для работы с чатом
    do {
        chat.showLoginMenu();

        do {
            chat.showUserMenu();
        } while (chat.getCurrentUser());

    } while (chat.isServerWork());

    return 0;
}