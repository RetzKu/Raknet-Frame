#include <iostream>
#include "Server.h"

int main()
{
	Server* MainServer = new Server("127.0.0.1", 60000);
	delete MainServer;
	return 0;
}