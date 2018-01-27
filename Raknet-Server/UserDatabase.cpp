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
	ClientData* tmp = new ClientData(chrono::system_clock::now(), Packet->guid.ToString(),Packet->systemAddress);
	Users.push_back(tmp);
}

RakNet::SystemAddress UserDatabase::FindSystemAddress(string guid)
{
	for (ClientData* var : Users)
	{
		if (var->ConnectionID == guid)
		{
			return var->Address;
		}
	}
	return NULL;
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

std::string UserDatabase::RegisterGuid(const RakNet::Packet* Packet)
{
	RakNet::BitStream bsIN(Packet->data,Packet->length,false);
	bsIN.IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::RakString Username;
	bsIN.Read(Username);
	for (ClientData* var : Users)
	{
		if (var->Username == Username.C_String())
		{
			return "NONE";
		}
		else if (var->Address == Packet->systemAddress)
		{
			var->Username = Username.C_String();
		}
	}
	return Username.C_String();
}

string UserDatabase::FindUsername(string guid)
{
	for (ClientData* var : Users)
	{
		if (var->ConnectionID == guid)
		{
			if (var->Username == "NONE")
			{
				return "NONE";
			}
			else
			{
				return var->Username;
			}
		}
	}
	return "NONE";
}

string UserDatabase::FindGuid(string username)
{
	for (ClientData* var : Users)
	{
		if (var->Username == username)
		{
			return var->ConnectionID;
		}
	}
	return "NONE";
}

vector<string> UserDatabase::GetAllUsers()
{
	vector<string> guids;
	for (ClientData* var : Users)
	{
		guids.push_back(var->ConnectionID);
	}
	return guids;
}