#ifndef _SERVERCONFIG_H_
#define _SERVERCONFIG_H_
#pragma once
#include <vector>
#include <string>
#include <set>
#include "Base.h"

#ifdef _WIN32
#pragma warning(disable: 4290)

#else
#include <libconfig.h++>
#endif
#include <libconfig.h++>
const char SZSYSLOGCFG[] = "syslog.cfg";

using namespace std;
using namespace libconfig;

class ServerConfig
{
public:
	ServerConfig(const char* server_file);
public:
	~ServerConfig(void);

	bool loadFromFile();

	int worlddNum() { return worldd_num_; }
	int worlddId(int id) {return world_id_[id];};
	const string worlddIp(int id);
	const string worlddBindIp(int id);
	int worlddGamedPort(int id);
	int worlddWebPort(int id);

	int gamedNum() {return gamed_num_;}
	const string gamedIp(int nid);
	int gamedPort(int nid);
	int gamedPort1(int nid);
	const string gamedBindIp(int nid);
	int gamedServerPort(int gid) {return gamed_server_port_[gid];}
	int gamedAdminPort(int gid) {return gamed_admin_port_[gid];}
	int gamedPolicyPort(int gid) {return gamed_policy_port_[gid];}



	int dbNum() {return db_num_;}
	const string& dbGamedName(int gid) {return db_gamed_name[gid];}
	const string& dbGamedUser(int gid) {return db_gamed_user[gid];}
	const string& dbGamedPassword(int gid) {return db_gamed_password[gid];}

	const string& dbMasterName(){return db_master_name;}
	const string& dbMasterUser(){return db_master_user;}
	const string& dbMasterPassword(){return db_master_password;}

	int memNum(){return mem_num_;}
	const string& getMemCache(int gid) {return mem_name[gid];}
	

	int proxyNum() {return proxy_num_;}
	const string proxyIp(int pid) {return proxy_addr[pid];}
	int proxyBindPort1(int pid) {return proxy_port_1[pid];}
	int proxyBindPort2(int pid) {return proxy_port_2[pid];}


private:

	string version_;

	map<int, string> proxy_ip_;
	map<int, int> proxy_port_1_;
	map<int, int> proxy_port_2_;
	map<int, int> proxy_policy_port_;
	int worldd_num_;
	vector<int> world_id_;
	map<int, string> world_bind_ip_;
	map<int, string> world_server_address_;
	map<int, int> world_gamed_port_;
	map<int, int> world_web_server_port_;

	int gamed_num_;
	map<int, string> gamed_ip_;
	map<int, int> gamed_port_;
	map<int, int> gamed_port1_;
	map<int, string> gamed_bind_ip_;
	map<int, int> gamed_server_port_;
	map<int, int> gamed_admin_port_;
	map<int, int> gamed_policy_port_;

	int db_num_;
	map<int, string> db_gamed_name;
	map<int, string>    db_gamed_user;
	map<int, string>    db_gamed_password;
	string db_master_name;
	string db_master_user;
	string db_master_password;

	int mem_num_;
	map<int,string> mem_name;


	int proxy_num_;
	map<int, string> proxy_addr;
	map<int, int> proxy_port_1;
	map<int, int> proxy_port_2;

	string server_file_;
	Config srv;
};

#endif
