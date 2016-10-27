#include "Obj_Login.h"
#include "player/Player.h"

Obj_Login::Obj_Login(Player &player)
	:m_rPlayer(player)
{
	
}

tuint32 Obj_Login::HandlePacket( ::CG_LOGIN &rPacket )
{
	__ENTER_FUNCTION

		
	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION
		return PACKET_EXE_CONTINUE;
}