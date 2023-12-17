/**
* @file  mdfile.cpp
*/
#include "md_gen.h"
/**
* @brief Функция вычисления хэша
* @param sah Переменная содержащая соль и хэш
* @return digest MD5 хэш
*/

string MD(string sah){
Weak::MD5 hash;
    string digest;
    StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));  // строка-приемник
      return digest;
 }

