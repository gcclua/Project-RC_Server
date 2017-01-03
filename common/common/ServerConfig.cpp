#include <time.h>
#include "ServerConfig.h"

ServerConfig::ServerConfig(const char* server_file): server_file_(server_file)
{
	if (!loadFromFile()) {
		printf("WARNING! read config file failed.\n");
		exit(1);
	}
}
ServerConfig::~ServerConfig(void)
{
}

bool ServerConfig::loadFromFile()
{
	//server.cfg
	try
	{
		srv.readFile(server_file_.c_str());

		const Setting& root = srv.getRoot();

		// worldd
		world_id_.clear();
		world_web_server_port_.clear();
		world_server_address_.clear();
		world_gamed_port_.clear();
		world_bind_ip_.clear();
	
		Setting &worlds = root["app"]["worldd"];
		worldd_num_ =  worlds.getLength();;
		for( int i =0; i< worldd_num_; i++ )
		{
			const Setting &world = worlds[i];
			int id = 0;
			int world_web_server_port = 0;
			const char* world_server_address;
			int world_gamed_port = 0;
			const char* world_bind_ip;
			if(!(world.lookupValue("id", id)
				&& world.lookupValue("world_web_server_port", world_web_server_port)
				&& world.lookupValue("world_bind_ip", world_bind_ip)
				&& world.lookupValue("world_server_address", world_server_address)
				&& world.lookupValue("world_gamed_port", world_gamed_port)))
			{
				continue;
			}
			world_id_.push_back(id);
			world_web_server_port_.insert(make_pair(id, world_web_server_port));
			world_server_address_.insert(make_pair(id, world_server_address));
			world_gamed_port_.insert(make_pair(id,world_web_server_port));
			world_bind_ip_.insert(make_pair(id, world_bind_ip));
		}

		
		// proxy
		proxy_addr.clear();
		proxy_port_1.clear();
		proxy_port_2.clear();
		Setting &proxyds = root["app"]["proxy"];
		proxy_num_ =  proxyds.getLength();;
		for(int i =0; i< proxy_num_; i++)
		{
			const Setting &proxyd = proxyds[i];
			int id = 0;
			const char* proxy_address;
			int proxy_port1 = 0;
			int proxy_port2 = 0;
			int proxy_port = 0;
			if(!(proxyd.lookupValue("id", id)
				&& proxyd.lookupValue("proxy_port_1", proxy_port1)
				&& proxyd.lookupValue("proxy_port_2", proxy_port2)
				&& proxyd.lookupValue("proxy_address", proxy_address)))
			{
				continue;
			}
			
			proxy_addr.insert(make_pair(id,   proxy_address));
			proxy_port_1.insert(make_pair(id, proxy_port1));
			proxy_port_2.insert(make_pair(id, proxy_port2));
		}

		
		// gamed
		gamed_ip_.clear();
		gamed_port_.clear();
		gamed_port1_.clear();
		gamed_bind_ip_.clear();
		gamed_server_port_.clear();
		gamed_policy_port_.clear();
		gamed_admin_port_.clear();

		Setting &gameds = root["app"]["gamed"];
		gamed_num_ =  gameds.getLength();

		for (int i=0; i<gamed_num_; i++) {
			const Setting &gamed = gameds[i];
			int gamed_id = 0;
			const char* addr;
			const char* bind_addr;
			int port = 0;
			int port1 = 0;
			int server_port = 0;
			int policy_port = 0;
			int admin_port  = 0;
			if(!(gamed.lookupValue("id", gamed_id)
				&& gamed.lookupValue("port", port)
				&& gamed.lookupValue("port1", port1)
				&& gamed.lookupValue("addr", addr)
				&& gamed.lookupValue("bind_addr", bind_addr)
				&& gamed.lookupValue("server_port", server_port)
				&& gamed.lookupValue("policy_port", policy_port)
				&& gamed.lookupValue("admin_port", admin_port)))
			{
				continue;
			}
			
			gamed_ip_.insert(make_pair(gamed_id, addr));
			gamed_port_.insert(make_pair(gamed_id, port));
			gamed_port1_.insert(make_pair(gamed_id, port1));
			gamed_bind_ip_.insert(make_pair(gamed_id, bind_addr));
			gamed_server_port_.insert(make_pair(gamed_id, server_port));
			gamed_policy_port_.insert(make_pair(gamed_id, policy_port));
			gamed_admin_port_.insert(make_pair(gamed_id, admin_port));
		}

		// database
		db_gamed_name.clear();
		db_gamed_user.clear();
		db_gamed_password.clear();

		Setting &dbs = root["app"]["database"];
		db_num_ =  dbs.getLength();

		for (int i=0; i<db_num_; i++) {
			const Setting &db = dbs[i];
			const char* dataname;
			const char* username;
			const char* password;
			int db_id;
			if(!(db.lookupValue("id", db_id)
				&& db.lookupValue("dataname", dataname)
				&& db.lookupValue("username", username)
				&& db.lookupValue("password", password)))
			{
				continue;
			}
			db_gamed_name.insert(make_pair(db_id, dataname));
			db_gamed_user.insert(make_pair(db_id, username));
			db_gamed_password.insert(make_pair(db_id, password));
		}
	}
	catch (ParseException ex)
	{
		printf("Parsing config file %s failed.\n", server_file_.c_str());
		return false;
	}
	catch (FileIOException ex) {
		printf("Read config file %s failed. IOExcetpion.\n", server_file_.c_str());
		return false;
	}
	catch (SettingNotFoundException ex) {
		printf("Read config file %s failed. Setting \"%s\" not found.\n", server_file_.c_str(), ex.getPath());
		return false;
	}

	return true;
}

int ServerConfig::worlddGamedPort(int id) 
{
	map<int, int>::const_iterator iter = world_gamed_port_.find(id);
	if (iter==world_gamed_port_.end()) 
		return 0;
	return iter->second; 
}


int ServerConfig::worlddWebPort(int id)
{
	map<int, int>::const_iterator iter = world_web_server_port_.find(id);
	if (iter==world_web_server_port_.end()) 
		return 0;
	return iter->second; 
}

const string ServerConfig::worlddIp(int id) 
{
	map<int, string>::const_iterator iter = world_server_address_.find(id);
	if (iter==world_server_address_.end()) 
		return "";
	return iter->second; 
}

const string ServerConfig::worlddBindIp(int id)
{
	map<int, string>::const_iterator iter = world_bind_ip_.find(id);
	if (iter==world_bind_ip_.end()) 
		return "";
	return iter->second; 
}

const string ServerConfig::gamedIp(int id) {
	map<int, string>::const_iterator iter = gamed_ip_.find(id);
	if (iter==gamed_ip_.end())
		return "";
	return iter->second;
}

int ServerConfig::gamedPort1(int nid)
{
	map<int, int>::const_iterator iter = gamed_port1_.find(nid);
	if (iter==gamed_port1_.end())
		return 0;
	return iter->second;
}

int ServerConfig::gamedPort(int id) {
	map<int, int>::const_iterator iter = gamed_port_.find(id);
	if (iter==gamed_port_.end())
		return 0;
	return iter->second;
}

const string ServerConfig::gamedBindIp(int id) {
	map<int, string>::const_iterator iter = gamed_bind_ip_.find(id);
	if (iter==gamed_bind_ip_.end())
		return "";
	return iter->second;
}

