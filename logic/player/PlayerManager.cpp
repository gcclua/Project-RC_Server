#include "PlayerManager.h"

PlayerManager::PlayerManager(void)
{
	m_nProcessCoonectTime = PROCESSCONNECTIONTIME;
}

PlayerManager::~PlayerManager(void)
{

}

void PlayerManager::Init(void)
{
	
}


void PlayerManager::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT
		QuerySockets();
		ProcessExceptions();
		ProcessInputs();
		ProcessOutputs();
    __LEAVE_PROTECT

	__ENTER_PROTECT
		ProcessCommand();
	__LEAVE_PROTECT

	__ENTER_PROTECT
		ProcessTicks(rTimeInfo);
	__LEAVE_PROTECT

	__ENTER_PROTECT
		ProcessCommand();
	__LEAVE_PROTECT
	
}

#if defined(__USE_SELECT__)
void PlayerManager::QuerySockets()
{
	__ENTER_FUNCTION
	if (m_PlayerList.empty())
	{
		return;
	}

	SOCKET MaxSocketID = m_PlayerList.front()->GetSocket().getSOCKET();
	FD_ZERO(&m_ReadSet);
	FD_ZERO(&m_WriteSet);
	FD_ZERO(&m_ExceptSet);

	for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
	{
		PlayerPtr Ptr = (*it);
		AssertEx(Ptr,"");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET,"");
		FD_SET(s,&m_ReadSet);
		FD_SET(s,&m_WriteSet);
		FD_SET(s,&m_ExceptSet);

		if (MaxSocketID < s)
		{
			MaxSocketID = s;
		}

		it++;
	}

	timeval timev;
	timev.tv_usec = 0;
	timev.tv_sec  = 0;

	int nRet = select(static_cast<int>(MaxSocketID+1),&m_ReadSet,&m_WriteSet,&m_ExceptSet,&timev);
	AssertEx(nRet != SOCKET_ERROR,"");

	__LEAVE_FUNCTION
}

#endif

#if defined(__USE_POOL)
void PlayerManager::QuerySockets()
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		AssertEx(m_PlayerList.size() != m_PollFDVector.size(),"");

		for (int i = 0;i < static_cast<int>(m_PollFDVector.size()); i++)
		{
			m_PollFDVector[i].revents = 0;
		}

		int nRet = poll(&(m_PollFDVector[0]),static_cast<int>(m_PollFDVector.size()),0);
		AssertEx(nRet > SOCKET_ERROR,"");
	__LEAVE_FUNCTION
}

#endif
#if defined(__USE_SELECT__)
void PlayerManager::ProcessInputs(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			if (FD_ISSET(s,&m_ReadSet))
			{
				if (Ptr->GetSocket().isSockError())
				{
					it = Del(Ptr,DEL_FOR_INPUTEXP1);
					continue;
				}
				else
				{
					__ENTER_PROTECT_EX
						bool bRet = Ptr->ProcessInput();
					    if (!bRet)
						{
							it = Del(Ptr,DEL_FOR_INPUTEXP2);
							continue;
						}
					__CATCH_PROTECT_EX
						it =  Del(Ptr,DEL_FOR_INPUTEXP3);
						continue;
					__LEAVE_PROTECT_EX
				}
			}
			it++;
		}
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_POOL)
void PlayerManager::ProcessInputs(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		AssertEx(m_PlayerList.size() != m_PollFDVector.size(),"");
		int nIndex = 0;
		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			AssertEx(nIndex >= 0 && nIndex < static_cast<int>(m_PollFDVector,size()),"");
			const pollfd &rpfd = m_PollFDVector[nIndex];
			AssertEx(rpfd.fd == s,"");
			AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT),"");

			if (rpfd.revents & POLLIN)
			{
				if (Ptr->GetSocket().isSockError())
				{
					it = Del(Ptr,DEL_FOR_INPUTEXP1);
					continue;
				}
				else
				{
					__ENTER_PROTECT_EX
						bool bRet = Ptr->ProcessInput();
					if (!bRet)
					{
						it = Del(Ptr,DEL_FOR_INPUTEXP2);
						continue;
					}
					__CATCH_PROTECT_EX
						it = Del(Ptr,DEL_FOR_INPUTEXP3);
					continue;
					__LEAVE_PROTECT_EX
				}
			}
			it++;
			nIndex++;
		}
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_SELECT__)
void PlayerManager::ProcessOutputs(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			if (FD_ISSET(s,&m_WriteSet))
			{
				if (Ptr->GetSocket().isSockError())
				{
					it = Del(Ptr,DEL_FOR_OUTPUTEXP1);
					continue;
				}
				else
				{
					__ENTER_PROTECT_EX
						bool bRet = Ptr->ProcessOutput();
					if (!bRet)
					{
						it = Del(Ptr,DEL_FOR_OUTPUTEXP2);
						continue;
					}
					__CATCH_PROTECT_EX
						it = Del(Ptr,DEL_FOR_OUTPUTEXP3);
						continue;
					__LEAVE_PROTECT_EX
				}
			}
			it++;
		}
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_POOL)
void PlayerManager::ProcessOutputs(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		AssertEx(m_PlayerList.size() != m_PollFDVector.size(),"");
		int nIndex = 0;
		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			AssertEx(nIndex >= 0 && nIndex < static_cast<int>(m_PollFDVector,size()),"");
			const pollfd &rpfd = m_PollFDVector[nIndex];
			AssertEx(rpfd.fd == s,"");
			AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT),"");

			if (rpfd.revents & POLLOUT)
			{
				if (Ptr->GetSocket().isSockError())
				{
					it = Del(Ptr,DEL_FOR_OUTPUTEXP1);
					continue;
				}
				else
				{
					__ENTER_PROTECT_EX
						bool bRet = Ptr->ProcessOutput();
					if (!bRet)
					{
						it = Del(Ptr,DEL_FOR_OUTPUTEXP2);
						continue;
					}
					__CATCH_PROTECT_EX
						it = Del(Ptr,DEL_FOR_OUTPUTEXP3);
						continue;
					__LEAVE_PROTECT_EX
				}
			}
			it++;
			nIndex++;
		}
	__LEAVE_FUNCTION
}
#endif


#if defined(__USE_SELECT__)
void PlayerManager::ProcessExceptions(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			if (FD_ISSET(s,&m_ExceptSet))
			{
				it = Del(Ptr,DEL_FOR_EXP);
			}
			it++;
		}
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_POOL)
void PlayerManager::ProcessExceptions(void)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		AssertEx(m_PlayerList.size() != m_PollFDVector.size(),"");
		int nIndex = 0;
		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			SOCKET s = Ptr->GetSocket().getSOCKET();
			AssertEx(s != INVALID_SOCKET,"");

			AssertEx(nIndex >= 0 && nIndex < static_cast<int>(m_PollFDVector,size()),"");
			const pollfd &rpfd = m_PollFDVector[nIndex];
			AssertEx(rpfd.fd == s,"");
			AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT),"");

			if ((rpfd.revents & POLLPRI) ||
				(rpfd.revents & POLLERR) ||
				(rpfd.revents & POLLHUP) ||
				(rpfd.revents & POLLNVAL))
			{
				it = Del(Ptr,DEL_FOR_EXP);
			}
			it++;
			nIndex++;
		}

	__LEAVE_FUNCTION
}
#endif

void PlayerManager::ProcessCommand()
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}

		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			
			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr,DEL_FOR_COMMANDEXP1);
			}
			else
			{
				__ENTER_PROTECT_EX
					bool bRet = Ptr->ProcessCommand();
				if (!bRet)
				{
					it = Del(Ptr,DEL_FOR_COMMANDEXP2);
					continue;
				}
				__CATCH_PROTECT_EX
					it = Del(Ptr,DEL_FOR_COMMANDEXP3);
				continue;
				__LEAVE_PROTECT_EX
			}
			
			it++;
		}
	__LEAVE_FUNCTION
}

void PlayerManager::ProcessConnection(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		m_nProcessCoonectTime -= rTimeInfo.m_uTimeElapse;
		if (m_nProcessCoonectTime>0)
		{
			return;
		}
		m_nProcessCoonectTime = PROCESSCONNECTIONTIME;
		if (m_PlayerList.empty())
		{
			return;
		}

		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");

			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr,Del_FOR_CONNECTEXP1);
			}
			else
			{
				__ENTER_PROTECT_EX
					bool bRet = Ptr->ProcessConnection(rTimeInfo.m_nAnsiTime);
				if (!bRet)
				{
					it = Del(Ptr,Del_FOR_CONNECTEXP2);
					continue;
				}
				__CATCH_PROTECT_EX
					it = Del(Ptr,Del_FOR_CONNECTEXP3);
				continue;
				__LEAVE_PROTECT_EX
			}

			it++;
		}

	__LEAVE_FUNCTION
}

#if defined(__USE_SELECT__)
void PlayerManager::Add(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_PlayerList.push_back(Ptr);
		OnAddPlayer(Ptr,nResult);
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_POOL)
void PlayerManager::Add(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_PlayerList.push_back(Ptr);
		
	pollfd pfd;
	pfd.fd = Ptr->GetSocket.getSOCKET();
	pfd.events = POLLIN | POLLOUT | POLLPRI;
	pfd.revents = 0;

	m_PollFDVector.push_back(pfd);
	AssertEx(m_PlayerList.size() == m_PollFDVector.size(),"");

	OnAddPlayer(Ptr,nResult);
	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_SELECT__)
PlayerPtrList::iterator PlayerManager::Del(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr tPtr = (*it);
			if (tPtr == Ptr)
			{
				PlayerPtrList::iterator itRet = m_PlayerList.erase(it);
				OnDelPlayer(Ptr,nResult);
				return itRet;
			}
			it++;
		}
		return m_PlayerList.end();
	__LEAVE_FUNCTION
		return m_PlayerList.end();
}
#endif


#if defined(__USE_POOL)
PlayerPtrList::iterator PlayerManager::Del(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		int nIndex = 0;
	for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
	{
		PlayerPtr tPtr = (*it);
		if (tPtr == Ptr)
		{
			PlayerPtrList::iterator itRet = m_PlayerList.erase(it);

			AssertEx(nIndex >=0,"");
			AssertEx(nIndex < static_cast<int>(m_PollFDVector.size()),"");
			m_PollFDVector.erase(m_PollFDVector.begin() + nIndex);
			AssertEx(m_PlayerList.size() == m_PollFDVector.size(),"");

			OnDelPlayer(Ptr,nResult);
			return itRet;
		}
		it++;
		nIndex++;
	}
	return m_PlayerList.end();
	__LEAVE_FUNCTION
		return m_PlayerList.end();
}
#endif

void PlayerManager::DelAll()
{
	int nPlayerCount = static_cast<int>(m_PlayerList.size());
	for (int i=0;i<nPlayerCount;i++)
	{
		Del(*(m_PlayerList.begin()),DEL_FOR_DEALL);
	}

	VerifyEx(m_PlayerList.empty(),"");
}