/**
* @file  mdfile.h
* @author Бакаев В.Г.
* @version 1.0
* @brief Описание классов, подключение библиотек и переменных
* @date 16.12.2023
* @copyright ИБСТ ПГУ
*/
#include <netinet/in.h>
#include <iostream>
#include <cassert>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <getopt.h>
#include <cryptopp/hex.h> // HexEncoder
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
using namespace CryptoPP;
using namespace std;
#include <cryptopp/md5.h> // MD%, для другого алгоритма - другой заголовочный файл

///@brief Класс для обработки ошибок возникающих при работе сервера
class error_server:
    public invalid_argument
{
public:
    explicit error_server (const string& what_arg):
        std::invalid_argument(what_arg){}
    explicit error_server (const char* what_arg):
        std::invalid_argument(what_arg){}
};

void errors(string error, string file_name);
