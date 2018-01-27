#include "Client.h"
#include "Player.h"

#include <vector>
#define CONSOLE(x) std::cout << x;
#define CONSOLEL(x) std::cout << x << std::endl; 

int main()
{
	Client* Connection = new Client("127.0.0.1", 60000,"Loyalisti");
	Player* Pelaaja = new Player(20, 20); //Temporary player class that keeps player coors for internal testing

	std::vector<float*> PelaajaCoords;
	PelaajaCoords.push_back(&Pelaaja->x);
	PelaajaCoords.push_back(&Pelaaja->y);
	Connection->SetVar(PLAYER_COORD,PelaajaCoords); //save 2float pointers under player_coord enum.


	Connection->OpenConnection();
	bool Running = true;
	while (Running)
	{
		Pelaaja->x = rand() % 50 + 50;
		Pelaaja->y = rand() % 50;
		Connection->Update();
	}
	Connection->CloseConnection();
	delete Connection;
	delete Pelaaja;
	return 0;
}
