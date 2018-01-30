#include "Client.h"

#include <vector>
#define CONSOLE(x) std::cout << x;
#define CONSOLEL(x) std::cout << x << std::endl; 

int main()
{
	Client* Connection = new Client("127.0.0.1", 60000,"Loyalisti");

	Connection->OpenConnection();
	bool Running = true;
	while (Running)
	{
		Connection->Update();
	}
	Connection->CloseConnection();
	delete Connection;
	return 0;
}
