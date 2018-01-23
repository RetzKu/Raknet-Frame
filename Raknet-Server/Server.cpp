#include "Server.h"


using namespace RakNet;
using namespace std;

#define PORT 60000

Server::Server(string IP, int Port)
{
	string title = "Raknet-Server";
	SetConsoleTitle(title.c_str());
	this->IP = IP;
	this->Port = Port;
	Connections = new UserDatabase();
	ServerStart();
}

Server::~Server()
{
}

void Server::ServerStart()
{
	Peer = RakPeerInterface::GetInstance();
	SD = new SocketDescriptor(PORT, 0);
	/*Creating Instance for server and starting up basic setup*/
	Peer->Startup(MaxConnections, SD, 1);
	Peer->SetMaximumIncomingConnections(MaxConnections);
	CONSOLE("Starting server at port " << Port);
	
	 Delta120 = chrono::system_clock::now();
	 TimeInterval = (int)((1.0 / 30) * 1000);
}

void Server::ServerStop()
{
	RakPeerInterface::DestroyInstance(Peer);
	delete SD;
	delete Connections;
}

void Server::ServerUpdate()
{
	auto Delta = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - Delta120);
	/*Loads packet from peer*/
	if ((float)Delta.count() > TimeInterval)
	{
		Delta120 += chrono::milliseconds((int)TimeInterval);
		for (Packet = Peer->Receive(); Packet; Peer->DeallocatePacket(Packet), Packet = Peer->Receive())
		{
			/*Switch case that lets us check what kind of packet it was*/
			CheckPacket(*Packet);
		}
	}
}

void Server::CheckPacket(const RakNet::Packet P)
{
	switch (P.data[0])
	{
	case ID_NEW_INCOMING_CONNECTION:
		Connections->ConnectUser(Packet);
		CONSOLE(Packet->guid.ToString() << " Connected to server");
		break;
	case USERNAME_FOR_GUID:
		Result = Connections->RegisterGuid(Packet);
		CONSOLE(Packet->guid.ToString() << " gave an username " << Result);
		break;
	case ID_CONNECTION_LOST:
		Connections->RemoveUser(Packet);
		CONSOLE(Packet->guid.ToString() << " Connection lost");
		break;
	case PLAYER_COORD:
		CONSOLE("Handle Player coord that was requested");
		break;
	}
}

bool Server::AskForVariable(CustomMessages var, INT64 guid)
{
	RakNet::BitStream bs;
	RakNet::RakNetGUID rakguid;
	rakguid.FromString(to_string(guid).c_str());

	bs.Write((RakNet::MessageID)PLAYER_COORD);
	Peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, rakguid, false, 0);
	return true;
}

bool Server::AskForVariable(CustomMessages var, string username)
{
	string guid = Connections->FindGuid(username);
	if (guid == "NONE")
	{
		return false;
	}
	INT64 guidint = stoll(guid);
	return AskForVariable(var, guidint);
}


void Server::RequestFromAll(CustomMessages Requested)
{
	vector<string> guids = Connections->GetAllUsers();
	INT64 guidint;
	for each(string var in guids)
	{
		guidint = stoll(var);
		AskForVariable(Requested, guidint);
	}
}

