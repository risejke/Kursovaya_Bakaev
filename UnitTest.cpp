#include <UnitTest++/UnitTest++.h>
#include "auth.h"
#include "math.h"
#include "md_gen.h"
#include "server.h"
#include "error.h"
#include "msg_send.h"
using namespace std;

struct things_fixture{
    Server * pointer;
    things_fixture(){
        pointer = new Server();
    }
    ~things_fixture(){
        delete pointer;
    }
};

struct for_calc{
    calculation * c;
    for_calc(){
        c = new calculation();
    }
    ~for_calc(){
        delete c;
    }
};

struct for_auth{
    Auth * a;
    for_auth(){
        a = new Auth();
    }
    ~for_auth(){
        delete a;
    }
};


SUITE(server)
{
    TEST_FIXTURE(things_fixture, Auth_without_problems){
        pointer->port = 33333;
        pointer->file_name = "base.txt";
		pointer->error_name = "error";
        CHECK(true);
    }
	
	TEST_FIXTURE(things_fixture, Incorrect_Port){
        pointer->port = 33333;
		pointer->error_name = "log.txt";
        CHECK_THROW(pointer->self_addr("error", "error.txt",  111),error_server);
    }

    TEST_FIXTURE(things_fixture, Wrong_Sock){
        pointer->port = 33333;
		pointer->file_error = "error.txt";
        CHECK_THROW(pointer->client_addr(-2, "err", "errtxt"),error_server);
    }
   }
SUITE(math){
    TEST_FIXTURE(for_calc, Only_positive){
    	std::vector<float>vector = {1.0, 2.0, 3.0};
        CHECK_CLOSE(6.0f,c->summa(vector), 0.00000001);
    }
    TEST_FIXTURE(for_calc, Only_negative){
    	std::vector<float>vector = {-1.0, -2.0, -3.0};
        CHECK_CLOSE(-6.0f,c->summa(vector), 0.00000001);
    }
    TEST_FIXTURE(for_calc, A_lot_of_numbers){
    	std::vector<float>vector = {-1.0, -2.0, -3.0, -4.2, -230, -11.2};
        CHECK_CLOSE(-251.4f,c->summa(vector), 0.00000001);
    }
    TEST_FIXTURE(for_calc, Empty_vector){
    	std::vector<float>vector = {};
        CHECK_CLOSE(0,c->summa(vector), 0.00000001);
    }
    TEST_FIXTURE(for_calc, Overflow_max){
   		float res = pow(2,32) - 1;
    	std::vector<float>vector = {pow(2,32),1};
        CHECK_CLOSE(res,c->summa(vector), 0.00000001);
    }
    TEST_FIXTURE(for_calc, Overflow_min){
   		float res = -pow(2,32);
    	std::vector<float>vector = {-pow(2,32),-1.0};
        CHECK_CLOSE(res,c->summa(vector), 0.00000001);
    }
}

SUITE(auth){
	 TEST_FIXTURE(for_auth, All_match){
		a->file_name = "base.txt";
		a->file_error = "nothing";
		a->message = "user:P@ssW@rd";
        CHECK(true);
    }
	 TEST_FIXTURE(for_auth, Login_dosent_match){
		a->file_name = "base.txt";
		a->file_error = "nothing";
		a->message = "incorrect_login:P@ssW@rd";
        CHECK_THROW(a->GetLogin(a->file_name,a->file_error,a->message), error_server);
    }
	 TEST_FIXTURE(for_auth, Password_doesnt_match){
		a->file_name = "base.txt";
		a->file_error = "nothing";
		a->message = "user:P@ssW@rd";
		a->salt = "RISERISERISERISE";
        CHECK_THROW(a->GetPass(a->file_name,a->file_error,a->salt,a->message), error_server);
    }
	 TEST_FIXTURE(for_auth, Incorrect_filepath_in_GetPass){
		a->file_name = "incorrect.txt";
		a->file_error = "nothing";
		a->message = "user:P@ssW@rd";
		a->salt = "RISERISERISERISE";
        CHECK_THROW(a->GetPass(a->file_name,a->file_error,a->salt,a->message), error_server);
    }
	 TEST_FIXTURE(for_auth, Incorrect_filepath_in_GetLogin){
		a->file_name = "incorrect.txt";
		a->file_error = "nothing";
		a->message = "user:P@ssW@rd";
        CHECK_THROW(a->GetLogin(a->file_name,a->file_error,a->message), error_server);
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}

