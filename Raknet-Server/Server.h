#include <vector>
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>

#include "MessageCodes.h"
#include "ClientInformation.h"
//#include "Utility.h"

/*Including basic raknet headeres*/
#include <Raknet\RakPeerInterface.h>
#include <Raknet\MessageIdentifiers.h>
#include <Raknet\RakNetTypes.h>
#include <Raknet\BitStream.h>

#define CONSOLE(x) std::cout << x << std::endl;

using namespace std;

class Server
{
public:
	Server(string IP, int Port);
	~Server();
	void ServerStart();
	void ServerLoop();

private:
	RakNet::Packet* Packet;
	RakNet::RakPeerInterface* Peer;
	RakNet::SocketDescriptor* SD;
	RakNet::BitStream bsIN;
	RakNet::BitStream bsOUT;

	vector<ClientData*> Connections;


	string IP;
	int Port;
	int MaxConnections = 10; 

	bool State = true;
};