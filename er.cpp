/**
* @file  er.cpp
*/
#include "error.h"
/**
* @brief Функция для обработки ошибок
* @param error Описание ошибки
* @param file_error Путь к лог файлу для записи ошибки
* @return true
*/
void errors(string error, string file_error){
    ofstream file;
    file.open(file_error, ios::app);
    if(!file.is_open()){
        throw error_server(string(error));
    }
    if(file.is_open()){
        time_t seconds = time(NULL);
        tm* timeinfo = localtime(&seconds);
        file << error << ':'<<asctime(timeinfo)<<endl;
        file.close();
        cout << error <<':'<<asctime(timeinfo)<<endl;
    }
}
