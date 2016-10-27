
#include "LibMemInterface.h"
#include "libmemcached/memcached_result.h"


LibMemInterface::LibMemInterface()
{
	memcached_create(&memc);
}

LibMemInterface::~LibMemInterface()
{
	memcached_free(&memc);

}

bool LibMemInterface::Init(const char* serverlistin)
{
	__ENTER_FUNCTION
	strncpy(serverlist,serverlistin,MAXSERVERLISTLENGTH);
	serverlist[MAXSERVERLISTLENGTH] = '\0';
	memcached_server_st *servers;
	servers = memcached_servers_parse(serverlist);
	memcached_server_push(&memc,servers);
	memcached_server_free(servers);

	return true;
	__LEAVE_FUNCTION
	return false;
}

char * LibMemInterface::Get(const char* key,uint32 key_length,size_t *value_length)
{
	__ENTER_FUNCTION

		if (null_ptr == key)
		{
			return null_ptr;
		}

		memcached_return rc;
		uint32 flags;
		char* value = memcached_get(&memc,key,key_length,value_length,&flags,&rc);
		if (MEMCACHED_SUCCESS != rc)
		{
			if (null_ptr != value)
			{
				free(value);
				value = null_ptr;
			}
			return null_ptr;
		}

		if (null_ptr == value)
		{

			return null_ptr;
		}

		return value;


    __LEAVE_FUNCTION
		return null_ptr;
}

bool LibMemInterface::Set(const char* key,uint32 key_length, const char* value,uint32 value_length,time_t expiration)
{
	__ENTER_FUNCTION

	if (null_ptr == key || null_ptr == value)
	{
		return false;
	}

	uint32 flags = 0;
	memcached_return rc = memcached_set(&memc,key,key_length,value,value_length,expiration,flags);
	bool retval = (rc ==  MEMCACHED_SUCCESS || rc == MEMCACHED_BUFFERED);
	if (false == retval)
	{


	}
	return retval;
	__LEAVE_FUNCTION

	return false;
}

bool LibMemInterface::Delete (const char* key, size_t key_length,time_t expiration )
{
	__ENTER_FUNCTION

		if (null_ptr == key)
		{
			return false;
		}

		memcached_return rc;
		uint32 flags = 0;
		rc = memcached_delete(&memc,key,key_length,expiration);
		
		bool retval = (rc == MEMCACHED_SUCCESS || rc == MEMCACHED_NOTFOUND);
		if (false ==  retval)
		{
			
		}
		return retval;
		__LEAVE_FUNCTION

		return false;
}