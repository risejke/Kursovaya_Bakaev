/**
* @file  create_servers.cpp
*/
#include "server.h"
#include "error.h"
/**
* @brief Реализация метода self_addr
* @param error Описание ошибки
* @param port Порт для соединеня
* @param file_error Путь к лог файлу для записи ошибки
* @return s Возвращает рабочий сокет
*/
int Server::self_addr(string error, string file_error, int port){
            int s = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in * self_addr = new (sockaddr_in);
            self_addr->sin_family = AF_INET;
            self_addr->sin_port = htons(port);
            self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
            cout << "Wait for connect client...\n";
        int b = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
            
            
            if(b == -1) {
                string error = "binding error";
                throw error_server(string(error));
                errors(error,  file_error);
                return 2;
            }


            listen(s, SOMAXCONN);
            return s;
            }


/**
* @brief Реализация метода client_addr
* @param error Описание ошибки
* @param s Сокет полученный из метода self_addr
* @param file_error Путь к лог файлу для записи ошибки
* @return work_sock Возвращает рабочий сокет
*/
int Server::client_addr(int s, string error,  string file_error){
                sockaddr_in * client_addr = new sockaddr_in;
                socklen_t len = sizeof (sockaddr_in);
                int work_sock = accept(s, (sockaddr*)(client_addr), &len);
                
                if(work_sock == -1) {
                string error = "Error with connection";
                throw error_server(string(error));
                errors(error, file_error);
                return 0;
                }
                else {
                    //Успешное подключение к серверу
                    cout << "Successfull client connection!\n";
                    return work_sock;
                }
                }
