#include "Chat.h"

int main()
{
    Chat chat;

    chat.start();

    //два цикла: 1ый(внешний) для входа в систему, 2ой(внутренний) для работы с чатом
    do {
        chat.showLoginMenu();

        do {
            chat.showUserMenu();
        } while (chat.getCurrentUser());

    } while (chat.isChatWork());

    return 0;
}