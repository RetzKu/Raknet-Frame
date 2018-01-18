#include "Client.h"

using namespace RakNet;
using namespace std;

Client::Client(string Username, string IP, int Port)
{
	this->Username = Username;
	this->IP = IP;
	this->Port = Port;

	string title = "Raknet-Client";
	SetConsoleTitle(title.c_str());

	ClientConnect();
}

Client::~Client()
{
}

void Client::ClientConnect()
{
	Peer = RakPeerInterface::GetInstance();
	SocketDescriptor SD;
	Peer->Startup(1, &SD, 1);
	this->SD = &SD;
	Peer->SetOccasionalPing(true);
	char ip[512];
	strcpy_s(ip, IP.c_str());
	Peer->Connect(ip, Port, 0, 0);
	CONSOLE("Client connection starting")
	ClientLoop();
}

void Client::ClientLoop()
{
	char ip[512];
	strcpy_s(ip, IP.c_str());
	//BitStream bsIN(Packet->data, Packet->length, false);

	while (State)
	{
		if (Connected = false){ Sleep(500); Peer->Connect(ip, Port, 0, 0); }
		for (Packet = Peer->Receive(); Packet; Peer->DeallocatePacket(Packet), Packet = Peer->Receive())
		{
			switch (Packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
				std::cout << "Connection was accepted\n";
				Connected = true;
				//HOST_ADD = packet->systemAddress;
				break;
			case ID_CONNECTION_LOST:
				printf("Connection lost");
				Connected = false;
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
