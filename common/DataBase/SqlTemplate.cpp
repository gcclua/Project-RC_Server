
#include "SqlTemplate.h"

/*
 *	角色基本信息
 */
const char*		LoadCharFullData	=
"select \
charguid,charname,title,sex,createtime,level,enegry,exp,vmoney,pw,\
haircolor,facecolor,hairmodel,facemodel,scene,xpos,zpos,logintime,logouttime,dbversion,\
camp,menpai,hp,mp,strikepoint,str,spr,con,ipr,dex,points,settings,\
shopinfo,carrypet,guldid,teamid,headid,erecover,vigor,maxvigor,vrecover,energymax,\
pwdeltime,dietime,bankmoney,bankend,bkscene,bkxpos,bkzpos,rage \
from %s where charguid = %d and isvalid = 1";



const char*		UpdateCharFullData	=	
"update \
%s  set title=\'%s\',sex=%d,level=%d,enegry=%d,exp=%d,vmoney=%d,pw=\'%s\',\
haircolor=%d,facecolor=%d,hairmodel=%d,facemodel=%d,scene=%d,xpos=%d,zpos=%d,logintime=%d,logouttime=%d, \
camp=\'%s\',menpai=%d,hp=%d,mp=%d,strikepoint=%d,str=%d,spr=%d,con=%d,ipr=%d,dex=%d,points=%d,settings=\'%s\', \
shopinfo = \'%s\',carrypet = \'%s\' ,guldid= %d,teamid =%d,headid=%d,erecover=%d,vigor=%d,maxvigor=%d,vrecover=%d,energymax=%d, \
pwdeltime=%d,dietime=%d,bankmoney=%d,bankend=%d,bkscene=%d,bkxpos=%d,bkzpos=%d,rage=%d,dbversion=%d  \
where charguid = %d and isvalid = 1";

const char*     LoadTileData = "select * from %s";
const char*     UpdateTileData = "update %s set posx=%d,posy=%d,block=%d,type=%d where tileId=%d";