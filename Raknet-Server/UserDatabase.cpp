#include "UserDatabase.h"

using namespace std;

UserDatabase::UserDatabase()
{
	Users = vector<ClientData*>();
}


UserDatabase::~UserDatabase()
{
	for (int i = 0; i < Users.size(); i++)
		delete Users[i];
	Users.clear();
}

void UserDatabase::ConnectUser(const RakNet::Packet* Packet)
{
	ClientData* tmp = new ClientData(chrono::system_clock::now(), Packet->guid.ToString());
	Users.push_back(tmp);
}

void UserDatabase::RemoveUser(const RakNet::Packet* Packet)
{
	assert(Users.empty() == false);
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i]->ConnectionID == Packet->guid.ToString())
		{
			delete Users[i];
			Users.erase(Users.begin() + i);
		}
	}
}

bool UserDatabase::RegisterGuid(const RakNet::Packet* Packet)
{
	RakNet::BitStream bsIN(Packet->data,Packet->length,false);
	bsIN.IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::RakString Username;
	bsIN.Read(Username);
	for (int i = 0; i < Users.size(); i++)
	{
		if (Users[i]->ConnectionID == Packet->guid.ToString())
		{
			if (Users[i]->Username == "None")
			{
				Users[i]->Username = Username.C_String();
			}
			else if (Users[i]->Username == Username.C_String())
			{
				return false;
			}
			else { return false; }
		}
	}
	return true;
}