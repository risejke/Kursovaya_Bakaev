#include "msg_send.h"
///@brief Функция для реализации отправки сообщения
void msgsend(int work_sock, string mess){
    char *buffer = new char[4096];
    strcpy(buffer, mess.c_str());
    send(work_sock, buffer, mess.length(), 0);
}
