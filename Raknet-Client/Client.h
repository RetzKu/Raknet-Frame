#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>
#include <thread>
#include <vector>

#include "MessageCodes.h"
#include "ClientInformation.h"
//#include "Utility.h"

/*Including basic raknet headeres*/
#include <Raknet\RakPeerInterface.h>
#include <Raknet\MessageIdentifiers.h>
#include <Raknet\RakNetTypes.h>
#include <Raknet\BitStream.h>

#define CONSOLE(x) std::cout << x << std::endl;


typedef struct
{
	std::vector<string*> Values;
	CustomMessages MessageID;
}Var;

using namespace std;

class Client
{
public:
	Client(string IP, int Port,const char* username);
	~Client();
	void ClientConnectionUpdate();
	void OpenConnection();
	void CloseConnection();
	bool SendUsernameForServer(RakNet::RakString username);
	void SendBackCoord(RakNet::Packet* P);
	RakNet::RakString GetUsername() { return RakNet::RakString(username);}
	void SetVar(CustomMessages MessageID, std::vector<string*> Vars);
	std::vector<Var> Vars;
	void CheckForVar(CustomMessages messageID);

	bool Connected = false;
	bool LoggedIn = false;
private:
	string IP;
	int PORT;
	const char* username;

	RakNet::SystemAddress HostAddress;
	RakNet::RakPeerInterface* Peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* Packet;
	RakNet::SocketDescriptor* SD = new RakNet::SocketDescriptor();

	bool State = true;
};

