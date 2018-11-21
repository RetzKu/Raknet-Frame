#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>

#include "MessageCodes.h"
#include "ClientInformation.h"
//#include "Utility.h"

/*Including basic raknet headeres*/
#include <Raknet\RakPeerInterface.h>
#include <Raknet\MessageIdentifiers.h>
#include <Raknet\RakNetTypes.h>
#include <Raknet\BitStream.h>
#include <Raknet/PacketizedTCP.h>

/*Autopatcher includes*/
#include <Raknet/Extra/Autopatcher/AutopatcherClient.h>
#include <Raknet/Extra/Autopatcher/AutopatcherServer.h>
#include <Raknet/FileListTransfer.h>
#include <Raknet/AutopatcherPatchContext.h>
#include <Raknet/FileListTransferCBInterface.h>
#include <Raknet/Gets.h>
#include <Raknet/RakSleep.h>

#define CONSOLE(x) std::cout << x << std::endl;




//typedef struct
//{
//	std::vector<float*> Values;
//	CustomMessages MessageID;
//}Var;
//
//typedef struct
//{
//	std::vector<string*> Values;
//	CustomMessages MessageID;
//}Var;

using namespace std;

class Client
{
/*PUBLIC FUNCTIONS*/
public:
	Client(string IP, int Port,const char* username);
	~Client();
	void Update();
	void OpenConnection();
	void OpenPatcher();
	void CloseConnection();
	void RetryConnection();
	bool SendUsernameForServer(RakNet::RakString username);
	void SendBackCoord(RakNet::Packet* P);
	RakNet::RakString GetUsername() { return RakNet::RakString(username);}
	void UsernameChange();
	void CheckForVar(CustomMessages messageID);
	void SetVar(CustomMessages MessageID, std::vector<string*> Vars);
	void SetVar(CustomMessages MessageID, std::vector<float*>Vars);
	void SetVar(CustomMessages MessageID, std::vector<int*>Vars);

/*PRIVATE FUNCTIONS*/
private:
	void ClientConnectionUpdate(RakNet::Packet* Packet);

/*PUBLIC VARIABLES*/
public:
	bool Connected = false;
	bool LoggedIn = false;
	string IP;
	int SERVER_PORT;
	const char* username;
	bool State = true;
	vector<Var<int>>IntVars;
	vector<Var<string>> StringVars;
	vector<Var<float>> FloatVars;
	std::thread BackupThread;
/*PRIVATE VARIABLES*/
private:

	RakNet::SystemAddress HostAddress;
	RakNet::RakPeerInterface* Peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::Packet* Packet;
	RakNet::SocketDescriptor* SD = new RakNet::SocketDescriptor(0,0);

	std::chrono::system_clock::time_point Delta;
	float TimeInterval;
};

