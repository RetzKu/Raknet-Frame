#include <Raknet\MessageIdentifiers.h>

enum CustomMessages
{
	CHAT_MESSAGE = ID_USER_PACKET_ENUM + 1,
	USERNAME_FOR_GUID,
	PLAYER_COORD,
	MOUSE_COORD,
	LOGIN_FAILED,
	LOGIN_ACCEPTED,
	USERNAME,
	PLAYER_COORD_UPDATE,
};

enum Type
{
	INT_TYPE,
	STRING_TYPE,
	FLOAT_TYPE,
};

template <typename T>
struct Var
{
	Type type;
	std::vector<T*> Values;
	CustomMessages MessageID;
};