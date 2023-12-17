/**
* @file  math.cpp
*/
#include "math.h"
#include "error.h"

/**
* @brief Функция для сложения значенй
* @param vector вектор со значениями
* @return sum сумма значений
*/
float calculation::summa(std::vector<float>vector){
	float sum = 0;
	for(auto i:vector){
		sum = sum + i;
	}
	return sum;
}
/**
* @brief Функция для проверки на переполнение
* @param sum сумма значений для проверки
* @return sum сумма значений
*/

float calculation::overflow(float sum){
	if(sum >= powf(2, 32)){
		sum =  powf(2,32) - 1;
		return sum;
	}
	else if(sum < -powf(2,32)){
		sum = -pow(2,32);
		return sum;
	}
	else{
	return sum;
	}
}


/**
* @brief Реализация фунцкции математических вычислений
* @param work_sock Рабочий сокет
* @return true
*/	
    float calculation::math(int work_sock){
                    uint32_t count;
                    uint32_t numb;
                    float vect;
                    calculation s;
                    recv(work_sock, &count, sizeof(count), 0);
                    //цикл векторов
                    for(uint32_t j=0; j<count; j++){
                        std::vector<float> res_vector;
                    	float summ_of_vector = 0;
                        recv(work_sock, &numb, sizeof(numb), 0);//прием длинны для первого вектора
                    	for(uint32_t i=0; i<numb; i++) { //цикл значений
                        	recv(work_sock, &vect, sizeof(vect), 0);
                        	res_vector.push_back(vect);
                    	}
                    	summ_of_vector = s.overflow(s.summa(res_vector));
                    	send(work_sock, &summ_of_vector, sizeof(summ_of_vector), 0);
                    }
                    cout << "Program finish!" <<endl;
                    close(work_sock);
                    return 1;
                    }


