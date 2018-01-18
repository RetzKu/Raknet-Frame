#pragma once

#include <iostream>
#include <string>
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

class Client
{
public:
	Client(string Username, string IP, int Port);
	~Client();
	void ClientConnect();
	void ClientLoop();
private:
	string Username;
	string IP;
	int Port;

	RakNet::Packet* Packet;
	RakNet::SocketDescriptor* SD;
	RakNet::RakPeerInterface* Peer;

	bool Connected = false;
	bool State = true;
};

