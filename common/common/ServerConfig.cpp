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

		// worldd
		world_id_.clear();
		world_web_server_port_.clear();
		world_server_address_.clear();
		world_gamed_port_.clear();
		world_bind_ip_.clear();
		worldd_num_ = srv.lookup("app.worldd_num");
		Setting &worldd = srv.lookup("app.worldd");
		for( int i =0; i< worldd_num_; i++ )
		{
			int id = worldd[i]["id"];
			world_id_.push_back(id);
			world_web_server_port_.insert(make_pair(id, (int)worldd[i]["world_web_server_port"]));
			world_server_address_.insert(make_pair(id, (const char*)worldd[i]["world_server_address"]));
			world_gamed_port_.insert(make_pair(id,(int) worldd[i]["world_gamed_port"]));
			world_bind_ip_.insert(make_pair(id, (const char*)worldd[i]["world_bind_ip"]));
		}

		
		// proxy
		proxy_addr.clear();
		proxy_port_1.clear();
		proxy_port_2.clear();
		proxy_policy_port.clear();
		proxy_num_ = srv.lookup("app.proxy_num");
		Setting &proxyd = srv.lookup("app.proxy");
		for(int i =0; i< proxy_num_; i++)
		{
			int id = proxyd[i]["id"];
			proxy_addr.insert(make_pair(id, (const char*)proxyd[i]["proxy_address"]));
			proxy_port_1.insert(make_pair(id, (int)proxyd[i]["proxy_port_1"]));
			proxy_port_2.insert(make_pair(id,(int) proxyd[i]["proxy_port_2"]));
			proxy_policy_port.insert(make_pair(id, (int)proxyd[i]["proxy_policy_port"]));
		}

		
		// gamed
		gamed_ip_.clear();
		gamed_port_.clear();
		gamed_port1_.clear();
		gamed_bind_ip_.clear();
		gamed_server_port_.clear();
		gamed_policy_port_.clear();
		gamed_admin_port_.clear();
		gamed_num_ = srv.lookup("app.gamed_num");
		printf("gamed_num:%d\n", gamed_num_);
		Setting &gamed = srv.lookup("app.gamed");

		for (int i=0; i<gamed_num_; i++) {
			int gamed_id = gamed[i]["id"];
			gamed_ip_.insert(make_pair(gamed_id, (const char *)gamed[i]["addr"]));
			gamed_port_.insert(make_pair(gamed_id, (int) gamed[i]["port"]));
			gamed_port1_.insert(make_pair(gamed_id, (int)gamed[i]["port1"]));
			gamed_bind_ip_.insert(make_pair(gamed_id, (const char*) gamed[i]["bind_addr"]));
			gamed_server_port_.insert(make_pair(gamed_id, (int)gamed[i]["server_port"]));
			gamed_policy_port_.insert(make_pair(gamed_id, (int)gamed[i]["policy_port"]));
			gamed_admin_port_.insert(make_pair(gamed_id, (int)gamed[i]["admin_port"]));
		}

		// database
		db_gamed_name.clear();
		db_gamed_user.clear();
		db_gamed_password.clear();

		db_num_ = srv.lookup("app.db_num");
		printf("db_num:%d\n", db_num_);
		Setting &db = srv.lookup("app.database");

		for (int i=0; i<db_num_; i++) {
			int db_id = db[i]["id"];
			db_gamed_name.insert(make_pair(db_id, (const char*)db[i]["dataname"]));
			db_gamed_user.insert(make_pair(db_id, (const char*)db[i]["username"]));
			db_gamed_password.insert(make_pair(db_id, (const char*)db[i]["password"]));
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

	//syslog.cfg
	try
	{
		srv.readFile(SZSYSLOGCFG);
		gamed_log_start_ = 0;
		star_log_start_ = 0;
		Setting &gamed = srv.lookup("app.gamed");
		{
			gamed_log_start_			= (int)gamed["log_file_start"];
			gamed_log_dir_				= (const char *)gamed["log_file_dir"];
			gamed_log_name_				= (const char *)(const char *)gamed["log_file_name"];
			gamed_log_stat_level_		= (int)gamed["send_lv"];
			gamed_log_stat_modul_		= (int)gamed["user_mod"];
			gamed_log_stat_modul_val_	= (int)gamed["user_mod_val"];
			gamed_log_stat_addr_		= (const char *)gamed["statsrv_addr"];
			gamed_log_stat_port_		= (const char *)gamed["statsrv_port"];
		}

		Setting &hall = srv.lookup("app.star");
		{

			star_log_start_				= (int)hall["log_file_start"];
			star_log_dir_				= (const char *)hall["log_file_dir"];
			star_log_name_				= (const char *)hall["log_file_name"];
			star_log_stat_level_		= (int)hall["send_lv"];
			star_log_stat_addr_			= (const char *)hall["statsrv_addr"];
			star_log_stat_port_			= (const char *)hall["statsrv_port"];
		}

	}

	catch (ParseException ex)
	{
		//printf("Parsing config file %s failed.%d\n", SZSYSLOGCFG, ex.getLine());
		printf("Parsing config file %s failed.", SZSYSLOGCFG);
		return false;
	}
	catch (FileIOException ex) {

		printf("Parsing config file %s failed.\n", SZSYSLOGCFG);
		//return false;
	}
	catch (SettingNotFoundException ex) {
		printf("Parsing config file %s failed. Setting \"%s\" not found.\n", SZSYSLOGCFG, ex.getPath());
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

