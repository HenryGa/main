#include "main.hpp"

using namespace std;

int main(int argc, char* argv[])
{

	Handler handler;

	handler.handle_input(argc, argv); // synarthsh xeirismou tou input

	handler.generate_Sylvester(); // synarthsh pou paragei to sylvester

	handler.generate_Polywnymo_Mhtrwwn(); // synarthsh pou paragei to polywnymo mhtrwwn

//	handler.generate_Bonus(); // synarthsh pou paragh to apotelesma M*v

	handler.print(); // synarthsh pou diaxeirizetai thn ektypwsh


}

