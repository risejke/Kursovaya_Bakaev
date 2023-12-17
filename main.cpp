/**
* @file  main.cpp
*/
#include "md_gen.h"
#include "math.h"
#include "auth.h"
#include "server.h"
int main(int argc, char *argv[]) {
    Server Server;
	Auth Auth;
    while (true) {
        string* com = Server.comstr(argc, argv);
        int s = Server.self_addr(com[3], com[2], stoi(com[1]));
        int work_sock = Server.client_addr(s, com[3], com[2]);
        // Вызов функций autorized и math
        Auth.autorized(work_sock, com[0], com[2]);
        calculation::math(work_sock);
        delete[] com; // Освобождаем выделенную память
        return 0;
    }
    return 0;
}
