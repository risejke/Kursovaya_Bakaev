/**
* @file  comstr.cpp
*/
#include "error.h"
#include "server.h"
///@brief Реализация ком. строки


string* Server::comstr(int argc, char *argv[]) {
    string* com = new string[4];
    int opt;
    int port = 33333;
    string file_name = "/etc/vcalc.conf";
    string file_error = "/var/log/vcalc.log";
    string error;
    com[3] = error;

    while ((opt = getopt(argc, argv, "hf:p:e:")) != -1) {
        switch(opt) {
            case 'h':
                cout << "Векторный калькулятор выполняющий действие сумму вектора"  << endl;
                cout << "-f Файл с логином и паролем пользователей" << endl;
                cout << "-p Порт сервера" << endl;
                cout << "-e Файл для записи ошибок" << endl;
                exit(0);
                break;
            case 'f':
                file_name = string(optarg);
                com[0] = file_name;
                break;
            case 'p':
                port = stoi(string(optarg));
                com[1] = to_string(port);
                break;
            case 'e':
                file_error = string(optarg);
                com[2] = file_error;
                break;
           	default:
                cerr << "Использование: " << argv[0] << " -f file_name -p port -e file_error" << endl;
                exit(EXIT_FAILURE);
           
        }
    }
    if (com[0].empty() || com[1].empty() || com[2].empty()) {
    cerr << "Ошибка: Все параметры (-f, -p, -e) должны быть указаны." << endl;
    cerr <<"Использование: " << argv[0] << " -f file_name -p port -e file_error"<<endl;
    cerr<< "Для вывода справки напишите: "<< argv[0]<< " -h"<<endl;
    exit(EXIT_FAILURE);
    }
    cout<<com<<endl;
    return com;
}
