#ifndef _LIBMEMINTERFACE_H_
#define _LIBMEMINTERFACE_H_

#include "Base.h"
#include "libmemcached/memcached.h"


class LibMemInterface
{

public:
	enum LIBMEMCONSTVALUES
	{
		MAXSERVERLISTLENGTH = 1024,
	};

public:
	LibMemInterface();
	~LibMemInterface();

	bool Init(const char* serverlistin);
	
	/**
		Fetches an individual value from the server
		param[in] key key of object whose value to server
		param[in] key_length key length of object whose value to server
		param[out] ra_val object that is retrieved is stored in this vector
	**/

	char * Get(const char* key,uint32 key_length,size_t *value_length);

	/**
	 * Write an object to the server. If the object already exists,it will overwrite the existing object
	 * This method always retures true
	 * when Using non-blocking mode unless a netword error occurs.
	 * 
	 * @param[in] key key of object to write to server
	 * @param[in] value value of object to write to server
	 * @param[in] expiration expiration time to keep te object stored in the server for
	 * return true on success;false otherwise
	**/
	bool  Set(const char* key,uint32 key_length, const char* value,uint32 value_length,time_t expiration);


	/**
		* Delete an object from a server specified by the key parameter
		* If the object already not exist,it will return false.
		*
		* @param[in] key key of object to delete from server
		* @param[in] key_length length of key
		* @param[in] expiration time to delete the object from server
	**/

	bool Delete (const char* key, size_t key_length,time_t expiration );

private:
	char serverlist[MAXSERVERLISTLENGTH + 1];
	memcached_st memc;
};

#endif