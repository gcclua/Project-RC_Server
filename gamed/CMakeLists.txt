# CMakeLists file

add_library(game 
AdminHandler.cpp   Daemon.cpp             GameDataHandler.cpp  GameEventAutoCreate.cpp  GameNetHandler.cpp  MemCacheServerHandler.cpp  StarHandler.cpp      TransferHandler.cpp
ClientHandler.cpp  FriendInfoHandler.cpp  GameDataSaver.cpp    GameEventHandler.cpp     gdhandler.cpp       PolicyHandler.cpp          StarInfoHandler.cpp  WorldHandler.cpp

event/BaseEvent.cpp                  event/RceCreditHandle.cpp
event/CheckAttack.cpp                event/RceElectricPctHandle.cpp
event/DealAdminEvent.cpp             event/RceFightReprotHandle.cpp
event/DealCallBackFriend.cpp         event/RceFriendListHandle.cpp
event/DealCallBackFriendPlatid.cpp   event/RceGetHandle.cpp
event/DealInviteFriend.cpp           event/RceGiftWindowHandle.cpp
event/DealSendGift.cpp               event/RceHeartbeatHandle.cpp
event/DealSendGiftPlatid.cpp         event/RceInitHandle.cpp
event/DealWebHandle.cpp              event/RceLoadHandle.cpp
event/FriendRequest.cpp              event/RceMineModifyHandle.cpp
event/GameStarRequest.cpp            event/RcePurchaseHandle.cpp
event/GameTimer.cpp                  event/RceQuestHandle.cpp
event/RceAddArmyHandle.cpp           event/RceSaveHandle.cpp
event/RceAttackHandle.cpp            event/RceTutorialStageHandle.cpp
event/RceBanLoginHandle.cpp          event/RceUpdateSaveHandle.cpp
event/RceBannersGiftHandle.cpp       event/RceYellowDayGiftHandle.cpp
event/RceBaseBattleModifyHandle.cpp  event/RceYellowNewGiftHandle.cpp
event/RceBattleModifHandle.cpp       event/SendRemoteUser.cpp
event/RceBuildingModifyHandle.cpp    event/UpdateWorkingStatus.cpp
event/RceCalYellowGiftHandle.cpp     event/UserAuth.cpp
event/RceClearDataHandle.cpp         event/UserLogin.cpp

)
