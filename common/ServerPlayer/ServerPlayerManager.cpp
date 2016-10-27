#include "ServerPlayerManager.h"

ServerPlayerManager::ServerPlayerManager(void)
{

}

ServerPlayerManager::~ServerPlayerManager(void)
{

}

void ServerPlayerManager::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	QuerySockets();
	ProcessExceptions();
	ProcessInputs();
	ProcessOutputs();

	__LEAVE_PROTECT

	__ENTER_PROTECT

	ProcessCommands();

	__LEAVE_PROTECT
}

#if defined(__USE_SELECT__)
void ServerPlayerManager::QuerySockets(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	SOCKET MaxSocketID = m_ServerPlayerList.front()->GetSocket().getSOCKET();

	FD_ZERO(&m_ReadSet);
	FD_ZERO(&m_WriteSet);
	FD_ZERO(&m_ExceptSet);

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		FD_SET(s, &m_ReadSet);
		FD_SET(s, &m_WriteSet);
		FD_SET(s, &m_ExceptSet);

		if (MaxSocketID < s)
		{
			MaxSocketID = s;
		}

		it++;
	}

	timeval timev;
	timev.tv_sec = 0;
	timev.tv_usec = 0;

	tint32 nRet = select(static_cast<tint32>(MaxSocketID + 1),
		&m_ReadSet, &m_WriteSet, &m_ExceptSet, &timev);

	AssertEx(nRet != SOCKET_ERROR, "");

	__LEAVE_FUNCTION
}
#endif
#if defined(__USE_POLL__)
void ServerPlayerManager::QuerySockets(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

	for (tint32 i = 0; i < static_cast<tint32>(m_PollFDVector.size()); i++)
	{
		m_PollFDVector[i].revents = 0;
	}

	tint32 nRet = poll(&(m_PollFDVector[0]), static_cast<tint32>(m_PollFDVector.size()), 0);

	AssertEx(nRet > SOCKET_ERROR, "");

	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_SELECT__)
void ServerPlayerManager::ProcessInputs(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		if(FD_ISSET(s, &m_ReadSet))
		{
			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr);
				continue;
			}
			else
			{
				__ENTER_PROTECT_EX
				bool bRet = Ptr->ProcessInput();
				if (!bRet)
				{
					it = Del(Ptr);
					continue;
				}
				__CATCH_PROTECT_EX
				it = Del(Ptr);
				continue;
				__LEAVE_PROTECT_EX
			}
		}

		it++;
	}

	__LEAVE_FUNCTION
}
#endif
#if defined(__USE_POLL__)
void ServerPlayerManager::ProcessInputs(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

	tint32 nIndex = 0;
	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		AssertEx(nIndex >= 0 && nIndex < static_cast<tint32>(m_PollFDVector.size()), "");
		const pollfd &rpfd = m_PollFDVector[nIndex];
		AssertEx(rpfd.fd == s, "");
		AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT), "");

		if (rpfd.revents & POLLIN)
		{
			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr);
				nIndex = nIndex;
				continue;
			}
			else
			{
				__ENTER_PROTECT_EX
					bool bRet = Ptr->ProcessInput();
					if (!bRet)
					{
						it = Del(Ptr);
						nIndex = nIndex;
						continue;
					}
				__CATCH_PROTECT_EX
					it = Del(Ptr);
					nIndex = nIndex;
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
void ServerPlayerManager::ProcessOutputs(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		if(FD_ISSET(s, &m_WriteSet))
		{
			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr);
				continue;
			}
			else
			{
				__ENTER_PROTECT_EX
					bool bRet = Ptr->ProcessOutput();
					if (!bRet)
					{
						it = Del(Ptr);
						continue;
					}
				__CATCH_PROTECT_EX
					it = Del(Ptr);
					continue;
				__LEAVE_PROTECT_EX
			}
		}

		it++;
	}

	__LEAVE_FUNCTION
}
#endif
#if defined(__USE_POLL__)
void ServerPlayerManager::ProcessOutputs(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

	tint32 nIndex = 0;
	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		AssertEx(nIndex >= 0 && nIndex < static_cast<tint32>(m_PollFDVector.size()), "");
		const pollfd &rpfd = m_PollFDVector[nIndex];
		AssertEx(rpfd.fd == s, "");
		AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT), "");

		if (rpfd.revents & POLLOUT)
		{
			if (Ptr->GetSocket().isSockError())
			{
				it = Del(Ptr);
				nIndex = nIndex;
				continue;
			}
			else
			{
				__ENTER_PROTECT_EX
					bool bRet = Ptr->ProcessOutput();
					if (!bRet)
					{
						it = Del(Ptr);
						nIndex = nIndex;
						continue;
					}
				__CATCH_PROTECT_EX
					it = Del(Ptr);
					nIndex = nIndex;
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
void ServerPlayerManager::ProcessExceptions(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		if (FD_ISSET(s, &m_ExceptSet))
		{
			it = Del(Ptr);
			continue;
		}

		it++;
	}

	__LEAVE_FUNCTION
}
#endif
#if defined(__USE_POLL__)
void ServerPlayerManager::ProcessExceptions(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

	tint32 nIndex = 0;
	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");
		SOCKET s = Ptr->GetSocket().getSOCKET();
		AssertEx(s != INVALID_SOCKET, "");

		AssertEx(nIndex >= 0 && nIndex < static_cast<tint32>(m_PollFDVector.size()), "");
		const pollfd &rpfd = m_PollFDVector[nIndex];
		AssertEx(rpfd.fd == s, "");
		AssertEx(rpfd.events == (POLLIN | POLLPRI | POLLOUT), "");

		if ((rpfd.revents & POLLPRI) ||
			(rpfd.revents & POLLERR) ||
			(rpfd.revents & POLLHUP) ||
			(rpfd.revents & POLLNVAL))
		{
			it = Del(Ptr);
			nIndex = nIndex;
			continue;
		}

		it++;
		nIndex++;
	}

	__LEAVE_FUNCTION
}
#endif

void ServerPlayerManager::ProcessCommands(void)
{
	__ENTER_FUNCTION

	if (m_ServerPlayerList.empty())
	{
		return;
	}

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr Ptr = (*it);
		AssertEx(Ptr, "");

		if (Ptr->GetSocket().isSockError())
		{
			it = Del(Ptr);
			continue;
		}
		else
		{
			__ENTER_PROTECT_EX
				bool bRet = Ptr->ProcessCommand();
				if (!bRet)
				{
					it = Del(Ptr);
					continue;
				}
			__CATCH_PROTECT_EX
				it = Del(Ptr);
				continue;
			__LEAVE_PROTECT_EX
		}

		it++;
	}

	__LEAVE_FUNCTION
}

#if defined(__USE_SELECT__)
void ServerPlayerManager::Add(ServerPlayerPtr Ptr)
{
	__ENTER_FUNCTION

	m_ServerPlayerList.push_back(Ptr);

	__LEAVE_FUNCTION
}
#endif
#if defined(__USE_POLL__)
void ServerPlayerManager::Add(ServerPlayerPtr Ptr)
{
	__ENTER_FUNCTION

	m_ServerPlayerList.push_back(Ptr);

	pollfd pfd;
	pfd.fd = Ptr->GetSocket().getSOCKET();
	pfd.events = POLLIN | POLLPRI | POLLOUT;
	pfd.revents = 0;
	m_PollFDVector.push_back(pfd);
	AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

	__LEAVE_FUNCTION
}
#endif

#if defined(__USE_SELECT__)
ServerPlayerPtrList::iterator ServerPlayerManager::Del(ServerPlayerPtr Ptr)
{
	__ENTER_FUNCTION

	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr tPtr = (*it);
		if (tPtr == Ptr)
		{
			ServerPlayerPtrList::iterator itRet = m_ServerPlayerList.erase(it);
			return itRet;
		}
		it++;
	}
	return m_ServerPlayerList.end();

	__LEAVE_FUNCTION
	return m_ServerPlayerList.end();
}
#endif
#if defined(__USE_POLL__)
ServerPlayerPtrList::iterator ServerPlayerManager::Del(ServerPlayerPtr Ptr)
{
	__ENTER_FUNCTION

	tint32 nIndex = 0;
	for (ServerPlayerPtrList::iterator it = m_ServerPlayerList.begin(); it != m_ServerPlayerList.end(); )
	{
		ServerPlayerPtr tPtr = (*it);
		if (tPtr == Ptr)
		{
			ServerPlayerPtrList::iterator itRet = m_ServerPlayerList.erase(it);

			AssertEx(nIndex >= 0, "");
			AssertEx(nIndex < static_cast<tint32>(m_PollFDVector.size()), "");
			m_PollFDVector.erase(m_PollFDVector.begin() + nIndex);
			AssertEx(m_ServerPlayerList.size() == m_PollFDVector.size(), "");

			return itRet;
		}
		it++;
		nIndex++;
	}
	return m_ServerPlayerList.end();

	__LEAVE_FUNCTION
	return m_ServerPlayerList.end();
}
#endif

void ServerPlayerManager::DelAll(void)
{
	__ENTER_FUNCTION

	tint32 nPlayerCount = static_cast<tint32>(m_ServerPlayerList.size());
	for (tint32 i = 0; i < nPlayerCount; i++)
	{
		Del(*(m_ServerPlayerList.begin()));
	}

	VerifyEx(m_ServerPlayerList.empty(), "");

	__LEAVE_FUNCTION
}
