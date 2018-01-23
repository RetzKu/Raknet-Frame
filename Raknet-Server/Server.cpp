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
	Peer = RakPeerInterface::GetInstance();
	Connections = new UserDatabase();
	ServerStart();
}

Server::~Server()
{
	delete SD;
	delete Connections;
}

void Server::ServerStart()
{
	/*Creating Instance for server and starting up basic setup*/
	SD = new SocketDescriptor(PORT, 0);
	Peer->Startup(MaxConnections, SD, 1);
	Peer->SetMaximumIncomingConnections(MaxConnections);
	CONSOLE("Starting server at port " << Port);
	ServerLoop();
}

void Server::ServerLoop()
{
	char ip[512];
	strcpy_s(ip, IP.c_str());

	//BitStream bsIN(Packet->data, Packet->length, false); //When packet reading is needed 

	while (State)
	{
		/*Loads packet from peer*/
		for (Packet = Peer->Receive(); Packet; Peer->DeallocatePacket(Packet), Packet = Peer->Receive())
		{
			/*Switch case that lets us check what kind of packet it was*/
			switch (Packet->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
				Connections->ConnectUser(Packet);
				CONSOLE(Packet->guid.ToString() << " Connected to server");
				break;
			case USERNAME_FOR_GUID:
				CONSOLE(Packet->guid.ToString() << " gave an username");
				Connections->RegisterGuid(Packet);
				break;
			case ID_CONNECTION_LOST:
				Connections->RemoveUser(Packet);
				CONSOLE(Packet->guid.ToString() << " Connection lost");
				break;
			}
		}
		if (GetConsoleWindow() == GetForegroundWindow())
		{
			if (GetAsyncKeyState(VK_ESCAPE) == -32767)
			{
				State = false;
			}
		}
	}
	RakPeerInterface::DestroyInstance(Peer);
}

