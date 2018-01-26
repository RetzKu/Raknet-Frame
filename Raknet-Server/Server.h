#include <vector>
#include <string>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>
#include <chrono>

#include "MessageCodes.h"
#include "UserDatabase.h"
#include "UserVariables.h"
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
	void ServerStop();
	void ServerUpdate();
	void CheckPacket(const RakNet::Packet& P);
	bool AskForVariable(CustomMessages var, INT64 guid);
	bool AskForVariable(CustomMessages var, string username);
	void RequestFromAll(CustomMessages var);
	void SendResponse(RakNet::SystemAddress sys, CustomMessages responseID);
	void BroadcastVar(CustomMessages Var, RakNet::Packet Packet);

private:
	RakNet::Packet* Packet;
	RakNet::RakPeerInterface* Peer;
	RakNet::SocketDescriptor* SD;
	RakNet::BitStream bsIN;
	RakNet::BitStream bsOUT;

	UserDatabase* Connections;

	string IP;
	int Port;
	int MaxConnections = 10; 

	bool State = true;
	string Result;

	/*Tickrates*/
	chrono::time_point<chrono::system_clock> Delta120;
	float TimeInterval;
};