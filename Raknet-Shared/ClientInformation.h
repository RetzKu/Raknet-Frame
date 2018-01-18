#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct ClientData
{
	ClientData(chrono::system_clock::time_point ConnectionTimestamp, string ConnectionID) {
		this->ConnectionTimestamp = ConnectionTimestamp;
		this->ConnectionID = ConnectionID;
	}
	chrono::system_clock::time_point ConnectionTimestamp;
	string ConnectionID;
	string Username;
};