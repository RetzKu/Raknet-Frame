#include "Client.h"

int main()
{
	Client* Connection = new Client("127.0.0.1", 60000);
	Connection->OpenConnection();
	bool Running = true;
	string name;
	std::cin >> name;
	while (Running)
	{
		Connection->ClientConnectionUpdate();
		//if (GetConsoleWindow() == GetForegroundWindow())
		//{
		if (GetAsyncKeyState(VK_NUMPAD0) == -32767)
		{
			Connection->SendUsernameForServer(name.c_str());
		}
		//}
	}
	Connection->CloseConnection();
	delete Connection;
	return 0;
}