#include <iostream>
#include "Server.h"

int main()
{
	Server* Connection = new Server("127.0.0.1", 60000);
	bool Running = true;
	while (Running)
	{
		Connection->ServerUpdate();
		if (GetConsoleWindow() == GetForegroundWindow())
		{
			if (GetAsyncKeyState(VK_ESCAPE) == -32767)
			{
				Running = false;
			}
		}
	}
	delete Connection;
	return 0;
}