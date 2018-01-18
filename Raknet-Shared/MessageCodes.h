#include <Raknet\MessageIdentifiers.h>

enum CustomMessages
{
	CHAT_MESSAGE = ID_USER_PACKET_ENUM + 1,
	PLAYER_COORD,
	MOUSE_COORD,
};