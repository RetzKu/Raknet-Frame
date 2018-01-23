#include "Client.h"

int main()
{
	Client* Connection = new Client("127.0.0.1", 60000);
	Connection->OpenConnection();
	bool Running = true;
	while (Running)
	{
		Connection->ClientConnectionUpdate();
		if (GetConsoleWindow() == GetForegroundWindow())
		{
			if (GetAsyncKeyState(VK_NUMPAD0) == -32767)
			{
				Connection->SendUsernameForServer("Loyalisti");
			}
		}
	}
	Connection->CloseConnection();
	delete Connection;
	return 0;
}