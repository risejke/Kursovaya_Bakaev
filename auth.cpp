/**
* @file  auth.cpp
*/
#include "error.h"
#include "auth.h"
#include "msg_send.h"
#include "md_gen.h"
#include <cstdlib>

/**
* @brief Функция для полученя и сравнения логина
* @param file_name путь к файлу с БД клиентов
* @param file_error описание ошибки
* @param message строка с логином и паролем
* @return login логин пользователя
* @return "doesn't match" если логины не совпадают
*/
std::string Auth::GetLogin(string file_name, string file_error, string message){
	string login, hashq, error;
	fstream file;
	file.open(file_name);
	if(!file.is_open()){
		error = "Ошибка открытия БД";
		errors(error, file_error);
		throw error_server(string(error));
	}else{
		getline (file, login, ':');
		getline (file, hashq);
}
	if(message != login){
		error = "Ошибка логина";
		errors(error, file_error);
		throw error_server(string(error));
		return "doesn't match";
}
return login;
}
/**
* @brief Функция для полученя и сравнения хэша
* @param file_name путь к файлу с БД клиентов
* @param file_error описание ошибки
* @param salt соль
* @param msg полученный хэш от пользователя
* @return digest MD хэш
* @return "doesn't match" если пароли не совпадают
*/
std::string Auth::GetPass(string file_name, string file_error, string salt, string msg){
	string login, hashq, error;
	fstream file;
	file.open(file_name);
	if(!file.is_open()){
		error = "Ошибка открытия БД";
		errors(error, file_error);
		throw error_server(string(error));
	}else{
		getline (file, login, ':');
		getline (file, hashq);
}
	string sah = salt + hashq;
	string digest;
	digest = MD(sah);
	if(digest != msg){
		error = "Ошибка пароля";
		errors(error, file_error);
		throw error_server(string(error));
		return "doesn't match";

}
	return digest;
}



/**
* @brief Функция реализации авторизации пользователя
* @param work_sock Рабочий сокет
* @param file_name Путь к файлу с базой данных пользователя
* @param file_error Путь к лог файлу для записи ошибки
* @return true
*/
int Auth::autorized(int work_sock, string file_name, string file_error){

                    string ok = "OK";
                    const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    const int length_salt = 16;
                    string salt;
                    for (int i = 0; i < length_salt; ++i) {
        				int index = rand() % (sizeof(alphabet) - 1);
        				salt += alphabet[index];
   	 				}
                    //string salt = "RISERISERISERISE";
                    salt.reserve(length_salt);
                    string err = "ERROR";
                    string error;
                    char msg[255];
                    recv(work_sock, &msg, sizeof(msg), 0);
                    string message = msg;
			  		string login = GetLogin(file_name, file_error, message);
                    if(login == "doesn't match"){
                        msgsend(work_sock,  err);
                            close(work_sock);
                        return 1;
                    }else{
                    msgsend(work_sock,  salt);
                    recv(work_sock, msg, sizeof(msg), 0);
					string pass = GetPass(file_name, file_error,salt, msg);
                    if(pass == "doesn't match"){
                        msgsend(work_sock,  err);
                        close(work_sock);
                        return 1;
                    }else{
                        msgsend(work_sock,  ok);
                    }
}
return 1;
}
