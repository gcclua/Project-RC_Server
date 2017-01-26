
create database if not exists main DEFAULT CHARACTER SET utf8mb4;
use main;

/*==============================================================*/
/* Table: t_char                                               */
/*==============================================================*/
drop table if exists t_char;
create table if not exists t_char
(
   accname                           varchar(80) binary           not null default '',
   charname                          varchar(80) binary           not null default '',
   charguid                          bigint unsigned              not null default 0xffffffffffffffff,
   isvalid                           tinyint                      not null default -1,
   commonflag                        varchar(41)                  not null default '',
   commondata                        varchar(4096)                not null default '',
   createtime                        bigint                       not null default 0,
   logouttime                        bigint                       not null default 0,
   cityid                            bigint                       not null default 0,
   gender                            tinyint                      not null default 0,
   primary key (charguid)
)ENGINE = INNODB;

create index Index_char_accname on t_char
(
   accname
);

create unique index Index_char_charname on t_char
(
   charname
);

delimiter //
drop procedure if exists load_char_info//
create procedure load_char_info(pcharguid bigint unsigned)
begin


select c.accname, 
			c.charname,
			charguid,
			c.isvalid,
			c.commonflag,
			c.commondata,
			c.logouttime,
			c.createtime,
			c.cityid,
			c.gender 
			from t_char as c
		where c.charguid=pcharguid and c.isvalid=1;

end;//
delimiter ;


delimiter //
drop procedure if exists update_char_info//
create procedure update_char_info(
pcharguid bigint unsigned,
pcharname varchar(80) binary,
paccname varchar(80) binary,
pisvalid tinyint,
pcommondata varchar(4096),
pcommonflag varchar(41),
pcityid   bigint unsigned,
tlogouttime bigint
)
begin

update t_char as c set
    c.charname=pcharname,
    c.isvalid=pisvalid,
    c.commonflag=pcommondata,
    c.commondata=pcommonflag,
   	c.logouttime=tlogouttime,
   	c.cityid=pcityid
where c.charguid=pcharguid and c.isvalid=1;

end;//
delimiter ;

delimiter //
drop procedure if exists loadcharlist//
create procedure loadcharlist(paccname varchar(80) binary)
begin
select
    c.charguid,
    c.charname
from t_char as c
where c.accname=paccname and c.isvalid=1;
end;//
delimiter ;

delimiter //
drop procedure if exists createchar//
create procedure createchar(
pcharguid bigint unsigned,
pcharname varchar(80) binary,
paccname varchar(80) binary,
plevel smallint,
pgender tinyint
)
begin
declare vcount int default 0;
declare vresult int default 1;
declare vnamecount bigint unsigned default 0;

start transaction;
select count(*) into vcount from t_char where isvalid=1 and accname=paccname;
if vcount < 1 then
    select count(*) into vnamecount from t_char where charname = pcharname;
    if vnamecount > 0 then
        set vresult = -2;       -- duplicate charname
    else
        insert into t_char(charguid, charname, accname,  gender, isvalid,createtime)
        values (pcharguid, pcharname, paccname, pgender,1,now());
    end if;
else
    set vresult = -4;           -- too more character
end if;

commit;
select vresult;
end//
delimiter ;

/*==============================================================*/
/* Table: t_guid;             */
/*==============================================================*/

DROP TABLE IF EXISTS t_guid;
CREATE TABLE t_guid (
  type int not null default 0,
  serial int unsigned not null default 0,
  unique key (type)
) ENGINE=InnoDB;

delimiter //
drop procedure if exists saveguid//
create procedure saveguid(
           ptype int,
           pserial int unsigned)
begin

    update t_guid set
           serial=pserial
    where type=ptype;
end//
delimiter ;

/*==============================================================*/
/* Table: t_randomname;             */
/*==============================================================*/
DROP TABLE IF EXISTS `t_randomname`;
CREATE TABLE `t_randomname` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(80) binary NOT NULL DEFAULT '',
  `exist` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB;

create index Index_randomname_name on t_randomname(name);
/*==============================================================*/
/* Table: t_randomname;             */
/*==============================================================*/
delimiter //
drop procedure if exists loadrandomname//
create procedure loadrandomname()
begin
select name from t_randomname where exist = 0 order by Id limit 100000;
end;//
delimiter ;
      
/*==============================================================*/
/* Table: t_city                                              */
/*==============================================================*/
drop table if exists t_city;
create table if not exists t_city
(
   charguid                          bigint unsigned              not null default 0xffffffffffffffff,
   cityid                            bigint unsigned              not null default 0xffffffffffffffff,
   tileid                            int                          not null default 0,
   posx                              int                          not null default 0,
   posz                              int                          not null default 0,
   level                             smallint                     not null default 0,
   createtime                        bigint                       not null default 0,
   food                              bigint                       not null default 0,
   stone                             bigint                       not null default 0,
   iron                              bigint                       not null default 0,
   gold                              bigint                       not null default 0,
   primary key (cityid)
)ENGINE = INNODB;

create index Index_city_charid on t_city(charguid);

delimiter //
drop procedure if exists createcity//
create procedure createcity(
pcityid bigint unsigned,
pcharguid bigint unsigned,
ptileid int,
posx int,
posz int,
plevel smallint,
pfood bigint,
pstone bigint,
piron bigint,
pgold  bigint
)
begin
declare vcount int default 0;
declare vresult int default 1;
declare vcitycount bigint unsigned default 0;

start transaction;

select count(*) into vcount from t_city where  charguid=pcharguid;
if vcount < 1 then
    select count(*) into vcitycount from t_city where cityid = pcityid;
    if vcitycount > 0 then
        set vresult = -2;       -- duplicate cityid
    else
        insert into t_city(charguid, cityid, tileid,  posx, posz,level,createtime,food,stone,iron,gold)
        values (pcharguid, pcityid, ptileid, posx,posz,plevel,now(),pfood,pstone,piron,pgold);
    end if;
else
    set vresult = -4;           -- too more city
end if;

commit;
select vresult;
end;//
delimiter ;

delimiter //
drop procedure if exists updatecity//
create procedure updatecity(
pcityid bigint unsigned,
ptileid int,
posx int,
posz int,
plevel smallint,
pfood bigint,
pstone bigint,
piron bigint,
pgold  bigint
)
begin
declare vresult int default 1;
declare vcitycount bigint unsigned default 0;

start transaction;

  select count(*) into vcitycount from t_city where cityid = pcityid;
  if vcitycount <= 0 then
      set vresult = -2;       -- no cityid
  else
  	update t_city as c set
    c.tileid=ptileid,
    c.posx=posx,
    c.posz=posz,
    c.level=plevel,
   	c.food=pfood,
   	c.stone=pstone,
   	c.iron=piron,
   	c.gold=pgold
where c.cityid=pcityid ;
  end if;

commit;
select vresult;
end;//
delimiter ;

delimiter //
drop procedure if exists loadcity//
create procedure loadcity(
pcharguid bigint unsigned
)
begin

  select cityid,charguid,tileid, posx,posz,level,food,stone,iron,gold from t_city where charguid = pcharguid;

end;//
delimiter ;

/*==============================================================*/
/* Table: t_building                                            */
/*==============================================================*/
drop table if exists t_building;
create table if not exists t_building
(
   guid                              bigint unsigned              not null default 0xffffffffffffffff,
   cityid                            bigint unsigned              not null default 0xffffffffffffffff,
   type                              smallint                     not null default 0,
   slot                              smallint                     not null default 0,
   level                             smallint                     not null default 0,
   createtime                        bigint                       not null default 0,
   primary key (guid)
)ENGINE = INNODB;

create index Index_building_cityid on t_building(cityid);

delimiter //
drop procedure if exists updatebuilding//
create procedure updatebuilding(
pguid bigint unsigned,
pcityid bigint unsigned,
ptype smallint,
pslot smallint,
plevel smallint
)
begin

declare vbuildcount bigint unsigned default 0;

start transaction;
  select count(*) into vbuildcount from t_building where guid = pguid;
  if vbuildcount > 0 then
      update t_building as c set
    c.level=plevel
    	where  guid = pguid;
  else
      insert into t_building(guid, cityid, type,  slot, level,createtime)
      values (pguid, pcityid, ptype, pslot,plevel,now());
  end if;

commit;

end//
delimiter ;

delimiter //
drop procedure if exists loadbuilding//
create procedure loadbuilding(
pcityid bigint unsigned
)
begin

declare vbuildcount bigint unsigned default 0;

start transaction;
  select guid,type,slot, level from t_building where cityid = pcityid;

commit;

end//
delimiter ;

/*==============================================================*/
/* Table: t_march                                              */
/*==============================================================*/
drop table if exists t_march;
create table if not exists t_march
(
   marchid                           bigint unsigned              not null default 0xffffffffffffffff,
   heroid                            bigint unsigned              not null default 0xffffffffffffffff,
   cityid                            bigint unsigned              not null default 0xffffffffffffffff,
   charguid                          bigint unsigned              not null default 0xffffffffffffffff,
   buildid                           bigint unsigned              not null default 0xffffffffffffffff,
   posx                              int                          not null default 0,
   posz                              int                          not null default 0,
   begintime                         bigint                       not null default 0,
   endtime                           bigint                       not null default 0,
   state                             int                          not null default 0,
   sceneinsid                        int                          not null default 0,
   sceneclassid                      int                          not null default 0,
   primary key (marchid)
)ENGINE = INNODB;

delimiter //
drop procedure if exists updatemarch//
create procedure updatemarch(
pmarchid bigint unsigned,
pheroid bigint unsigned,
pcharguid bigint unsigned,
pcityid bigint unsigned,
pbuildid bigint unsigned,
pposx int,
pposz int,
tbegintime bigint,
tendtime   bigint,
pstate     int,
pinstid    int,
pclassid   int
)
begin

declare vmarchcount bigint unsigned default 0;

start transaction;
  select count(*) into vmarchcount from t_march where marchid = pmarchid;
  if vmarchcount > 0 then
      update t_march as c set
    c.buildid=pbuildid,
    c.posx=pposx,
    c.posz=pposz,
    c.begintime=tbegintime,
    c.endtime=tendtime,
    c.state=pstate,
    c.sceneinsid=pinstid,
    c.sceneclassid=pclassid
    	where  marchid = pmarchid;
  else
      insert into t_march(marchid, heroid, charguid, cityid, buildid, posx,posz,begintime,endtime,state,sceneinsid,sceneclassid)
      values (pmarchid, pheroid, pcharguid,pcityid, pbuildid,pposx,pposz,tbegintime,tendtime,pstate,pinstid,pclassid);
  end if;

commit;

end//
delimiter ;

create index Index_march_cityid on t_march(cityid);
create index Index_march_state on t_march(state);

delimiter //
drop procedure if exists loadcitymarch//
create procedure loadcitymarch(
pcityid bigint unsigned
)
begin

start transaction;
  select marchid,heroid,charguid,buildid, posx, posz,state,begintime,endtime,sceneinsid,sceneclassid from t_march where cityid = pcityid;
commit;

end//
delimiter ;

delimiter //
drop procedure if exists loadmarch//
create procedure loadmarch(
pmarchid bigint unsigned
)
begin

start transaction;
  select marchid,heroid,buildid, posx, posz,state,begintime,endtime,sceneinsid,sceneclassid from t_march where marchid = pmarchid;
commit;

end//
delimiter ;

delimiter //
drop procedure if exists loadmapmarch//
create procedure loadmapmarch(
)
begin

  select marchid,heroid,charguid,buildid,cityid, posx, posz,state,begintime,endtime,sceneinsid,sceneclassid from t_march where state >= 10;

end//
delimiter ;



/*==============================================================*/
/* Table: t_hero                                              */
/*==============================================================*/
drop table if exists t_hero;
create table if not exists t_hero
(
   heroid                            bigint unsigned              not null default 0xffffffffffffffff,
   cityid                          bigint unsigned              not null default 0xffffffffffffffff,
   marchid                           bigint unsigned              not null default 0xffffffffffffffff,
   type                              smallint                     not null default 0,
   level                             smallint                     not null default 0,
   quality                           smallint                     not null default 0,
   createtime                        bigint                       not null default 0,
   state                             int                          not null default 0,
   exp                               int                          not null default 0,
   hp                                int                          not null default 0,
   queueindex                        smallint                     not null default 0,
   arrangeindex                      smallint                     not null default 0,
   primary key (heroid)
)ENGINE = INNODB;

delimiter //
drop procedure if exists updatehero//
create procedure updatehero(
pheroid bigint unsigned,
pcityid bigint unsigned,
pmarchid bigint unsigned,
ptype smallint,
plevel smallint,
pquality smallint,
pstate     int,
pexp  int,
pqueueindex smallint,
parrangeindex smallint,
php int
)
begin
declare vresult int default 1;
declare vherocount bigint unsigned default 0;

start transaction;
  select count(*) into vherocount from t_hero where heroid = pheroid;
  if vherocount > 0 then
      update t_hero as c set
    	c.level=plevel,
    	c.quality=pquality,
    	c.state=pstate,
    	c.exp=pexp,
    	c.queueindex=pqueueindex,
    	c.arrangeindex=parrangeindex,
    	c.marchid=pmarchid,
    	c.hp=php
    	where  heroid = pheroid;
  else
      insert into t_hero(heroid, cityid,  marchid, type,level,quality,createtime,state,exp,queueindex,arrangeindex,hp)
      values (pheroid, pcityid, pmarchid,ptype,plevel,pquality,now(),pstate,pexp,pqueueindex,parrangeindex,php);
  end if;

commit;
select vresult;
end//
delimiter ;

delimiter //
drop procedure if exists loadhero//
create procedure loadhero(
pheroid bigint unsigned
)
begin

  select heroid,cityid,marchid, type, level,quality,state,exp,queueindex, arrangeindex,hp from t_hero where heroid = pheroid;

end//
delimiter ;

create index Index_city_hero on t_hero(cityid);

delimiter //
drop procedure if exists loadcityhero//
create procedure loadcityhero(
pcityid bigint unsigned
)
begin

  select heroid,cityid,marchid, type, level,quality,state,exp,hp,queueindex, arrangeindex from t_hero where cityid=pcityid;


end//
delimiter ;

/*==============================================================*/
/* Table: t_troop                                              */
/*==============================================================*/
drop table if exists t_troop;
create table if not exists t_troop
(
   troopid                           bigint unsigned              not null default 0xffffffffffffffff,
   marchid                           bigint unsigned              not null default 0xffffffffffffffff,
   type                              smallint                     not null default 0,
   level                             smallint                     not null default 0,
   createtime                        bigint                       not null default 0,
   hp                                int                          not null default 0,
   queueindex                        smallint                     not null default 0,
   arrangeindex                      smallint                     not null default 0,
   primary key (troopid)
)ENGINE = INNODB;

delimiter //
drop procedure if exists updatetroop//
create procedure updatetroop(
ptroopid bigint unsigned,
pmarchid bigint unsigned,
ptype smallint,
plevel smallint,
pqueueindex smallint,
parrangeindex smallint,
php int
)
begin
declare vresult int default 1;
declare vherocount bigint unsigned default 0;

start transaction;
  select count(*) into vherocount from t_troop where troopid = ptroopid;
  if vherocount > 0 then
      update t_troop as c set
    	c.level=plevel,
    	c.marchid=pmarchid,
    	c.queueindex=pqueueindex,
    	c.arrangeindex=parrangeindex,
    	c.hp=php
    	where  troopid = ptroopid;
  else
      insert into t_troop(troopid,  marchid, type,level,createtime,queueindex,arrangeindex,hp)
      values (ptroopid, pmarchid,ptype,plevel,now(),pqueueindex,parrangeindex,php);
  end if;

commit;
select vresult;
end//
delimiter ;

create index Index_march_troop on t_troop(marchid);

delimiter //
drop procedure if exists loadmarchtroop//
create procedure loadmarchtroop(
pmarchid bigint unsigned
)
begin

start transaction;
  select troopid,marchid, type, level,hp ,queueindex, arrangeindex from t_troop where marchid = pmarchid;
commit;

end//
delimiter ;

delimiter //
drop procedure if exists loadtroop//
create procedure loadtroop(
ptroopid bigint unsigned
)
begin

start transaction;
  select troopid,marchid, type, level,hp,queueindex, arrangeindex from t_troop where troopid = ptroopid;
commit;

end//
delimiter ;

/*==============================================================*/
/* Table: t_tile                                             */
/*==============================================================*/
drop table if exists t_traintroop;
create table if not exists t_traintroop
(
   id                                bigint unsigned              not null default 0xffffffffffffffff,
   cityid                            bigint unsigned              not null default 0xffffffffffffffff,
	 begintime                         bigint                       not null default 0,
   completetime                      bigint                       not null default 0,
   trooptype                         smallint                     not null default 0,
   hp                                int                          not null default 0,
   buildid                           bigint unsigned              not null default 0xffffffffffffffff,
   queueindex                        int                          not null default 0,
   primary key (id)
)ENGINE = INNODB;

delimiter //
drop procedure if exists updatetraintroop//
create procedure updatetraintroop(
pid bigint unsigned,
pcityid bigint unsigned,
tbegintime bigint,
tcompletetime bigint,
ptrooptype smallint,
php int,
pbuildid bigint unsigned,
pqueueindex int
)
begin
declare vcount int default 0;

  select count(*) into vcount from t_traintroop where id = pid;
  if vcount > 0 then
      update t_traintroop as c set
    	c.cityid=pcityid,
    	c.begintime=tbegintime,
    	c.completetime=tcompletetime,
    	c.hp=php,
    	c.trooptype=ptrooptype,
    	c.buildid=pbuildid,
    	c.queueindex = pqueueindex
    	where  id = pid;
  else
      insert into t_traintroop(id,cityid, begintime,completetime,trooptype,hp,buildid,queueindex)
      values (pid, pcityid,tbegintime,tcompletetime,ptrooptype,php,pbuildid,pqueueindex);
  end if;

end//
delimiter ;

create index Index_city_train on t_traintroop(cityid);

delimiter //
drop procedure if exists loadtrooptrain//
create procedure loadtrooptrain(
pcityid bigint unsigned
)
begin

start transaction;
  select id,begintime, completetime, hp,trooptype, buildid,queueindex from t_traintroop where cityid = pcityid;
commit;

end//
delimiter ;



/*==============================================================*/
/* Table: t_tile                                             */
/*==============================================================*/
drop table if exists t_tile;
create table if not exists t_tile
(
   tileid                            int unsigned                 not null default 0,
   charguid                          bigint unsigned              not null default 0xffffffffffffffff,
   cityid                            bigint unsigned              not null default 0xffffffffffffffff,
	 posx															 int                          not null default 0,
	 posz															 int                          not null default 0,
   type                              smallint                     not null default 0,
   state                             smallint                     not null default 0,
   primary key (tileid)
)ENGINE = INNODB;

delimiter //
drop procedure if exists loadtile//
create procedure loadtile(
)
begin

  select tileid,charguid, cityid,posx,posz,type,state from t_tile;

end//
delimiter ;

delimiter //
drop procedure if exists savetile//
create procedure savetile(
ptileid int,
pcharguid bigint unsigned,
pcityid bigint unsigned,
pposx   int,
pposz   int,
ptype smallint,
pstate smallint
)
begin

  update t_tile as c set
    c.tileid=ptileid,
    c.charguid=pcharguid,
    c.cityid=pcityid,
    c.posx=pposx,
   	c.posz=pposz,
   	c.type=ptype,
   	c.state=pstate
where c.tileid=ptileid;

end//
delimiter ;


