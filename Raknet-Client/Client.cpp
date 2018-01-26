#include "Client.h"

using namespace RakNet;
using namespace std;

#define CONSOLE(x) cout << x << endl;

Client::Client(string IP, int Port, const char* username)
{
	
	this->IP = IP;
	this->PORT = Port;
	this->username = username;
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
			CONSOLE("Connection with server at " << IP << " was succesful");
			Connected = true;
			break;
		case ID_CONNECTION_LOST:
			CONSOLE("Connection lost to server at " << IP);
			Connected = false;
			break;
		case PLAYER_COORD:
			CheckForVar(PLAYER_COORD);
			CONSOLE("PLAYER COORD REQUEST RECEIVED");
			break;
		case PLAYER_COORD_UPDATE:
			CONSOLE("RECEIVED NEW COORDS FOR GUID" << Packet->guid.ToString());
			break;
		case LOGIN_ACCEPTED:
			CONSOLE("Server accepted our username");
			LoggedIn = true;
			break;
		}
	}
	if (Connected == false)
	{
		Peer->Connect(IP.c_str(), PORT, 0, 0);
		Sleep(500); 
	}
	if (!LoggedIn)
	{
		RakNet::RakString username = GetUsername();
		SendUsernameForServer(username);
		Sleep(500);
	}
}

void Client::CheckForVar(CustomMessages messageID)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)messageID);

	for (Var tmp : this->Vars)
	{
		if (tmp.MessageID == messageID)
		{
			for (string* value : tmp.Values)
			{
				string as = *value;
				RakNet::RakString asr(as.c_str());
				bs.Write(asr);
			}
			Peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, HostAddress, false, 0);
		}
	}
}

void Client::SetVar(CustomMessages MessageID, std::vector<string*> Vars)
{
	Var tmp;
	tmp.MessageID = MessageID;
	tmp.Values = Vars;
	this->Vars.push_back(tmp);
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
	Peer->Send(&bs, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, P->systemAddress, false, 0);
}