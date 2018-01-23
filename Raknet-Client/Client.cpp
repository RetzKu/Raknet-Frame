#include "Client.h"

using namespace RakNet;
using namespace std;

#define CONSOLE(x) cout << x << endl;

Client::Client(string IP, int Port)
{
	
	this->IP = IP;
	this->PORT = Port;

	string title = "Raknet-Client";
	SetConsoleTitle(title.c_str());
}

Client::~Client()
{
	delete SD;
}

void Client::CloseConnection()
{
	RakPeerInterface::DestroyInstance(Peer);
}

/*Does simple setup for client connection*/
void Client::OpenConnection()
{
	Peer = RakPeerInterface::GetInstance();

	Peer->Startup(1, SD, 1);
	Peer->SetOccasionalPing(true);

	Peer->Connect(IP.c_str(),PORT, 0, 0);
}

void Client::ClientConnectionUpdate()
{
	for (Packet = Peer->Receive(); Packet; Peer->DeallocatePacket(Packet), Packet = Peer->Receive())
	{
		switch (Packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			HostAddress = Packet->systemAddress;
			CONSOLE("Connection with server at " << IP << " was succesfull");
			Connected = true;
			break;
		case ID_CONNECTION_LOST:
			CONSOLE("Connection lost to server at " << IP);
			Connected = false;
			break;
		case PLAYER_COORD:
			SendBackCoord(Packet);
			CONSOLE("PLAYER COORD REQUEST RECEIVED");
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
	if (Connected = false)
	{
		Sleep(500); 
		Peer->Connect(IP.c_str(), PORT, 0, 0);
	}

}

bool Client::SendUsernameForServer(RakNet::RakString username)
{
	RakNet::BitStream BS;
	BS.Write((RakNet::MessageID)USERNAME_FOR_GUID);
	BS.Write(username);
	Peer->Send(&BS, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, HostAddress, false,0);
	return true;
}
void Client::SendBackCoord(RakNet::Packet* P)
{
	RakNet::BitStream bs;
	bs.Write((MessageID)PLAYER_COORD);
	bs.Write("20");
	Peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, P->systemAddress, false, 0);
}