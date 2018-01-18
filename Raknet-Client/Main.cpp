#include "Client.h"

int main()
{
	Client* Connection = new Client("Loyalisti", "127.0.0.1", 60000);
	delete Connection;
	return 0;
}