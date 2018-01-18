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
	ServerStart();
}

Server::~Server()
{
	delete SD;
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
		RakNet::BitStream bsIN;
		for (Packet = Peer->Receive(); Packet; Peer->DeallocatePacket(Packet), Packet = Peer->Receive())
		{
			RakNet::BitStream bsIN(Packet->data, Packet->length, false);

			switch (Packet->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
				Connections.push_back(new ClientData(std::chrono::system_clock::now(),Packet->guid.ToString()));
				CONSOLE(Packet->guid.ToString() << " Connecting to server");
				break;
			case ID_CONNECTION_LOST:
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
