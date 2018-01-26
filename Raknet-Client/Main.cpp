#include "Client.h"
#include "Player.h"

#include <vector>
#define CONSOLE(x) std::cout << x;
#define CONSOLEL(x) std::cout << x << std::endl; 

int main()
{
	Client* Connection = new Client("127.0.0.1", 60000,"Loyalisti");

	Connection->OpenConnection();
	Player* Pelaaja = new Player("20", "20");
	std::vector<string*> Sijainnit;

	Sijainnit.push_back(&Pelaaja->x);
	Sijainnit.push_back(&Pelaaja->y);
	
	Connection->SetVar(PLAYER_COORD, Sijainnit);

	bool Running = true;
	while (Running)
	{
		Pelaaja->x = std::to_string(rand() % 50+50);
		Pelaaja->y = std::to_string(rand() % 50);
		Connection->ClientConnectionUpdate();
	}
	Connection->CloseConnection();
	delete Connection;
	delete Pelaaja;
	return 0;
}
