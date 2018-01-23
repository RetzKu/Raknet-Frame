#include <string>
#include <vector>
#include <chrono>
#include <iostream>

#include "ClientInformation.h"
#include <Raknet\BitStream.h>

using namespace std;

class UserDatabase
{
public:
	UserDatabase();
	~UserDatabase();
	void ConnectUser(const RakNet::Packet* Packet);
	void RemoveUser(const RakNet::Packet* Packet);
	bool RegisterGuid(const RakNet::Packet* Packet);
private:
	vector<ClientData*> Users;
};

