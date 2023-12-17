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

/// @brief Класс для аутентификации пользователя
class Auth{
public:
string file_name;
string file_error;
string message;
string salt;
string GetLogin(string file_name,string file_error, string message);
string GetPass(string file_name,string file_error, string salt, string msg);
int autorized(int work_sock, string file_name, string file_error);
};
