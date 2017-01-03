@echo off
cls
color 0b

echo CSharp消息包创建工具V1.0
set homeford=%cd%
cd..
cd..
set workpath=%cd%
cd "%homeford%"

rem 设置Csharp目标文件夹
set DestDir=%workpath%\Client\Assets\FengYun\Script\GameLogic\NetWork

rem 设置源文件夹，里面有生成的CSharp消息包
set SrcFolder=%homeford%\tmp

rem 删除tmp文件夹
if exist %SrcFolder% rmdir /Q /S %SrcFolder%

rem "%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -cpp -c#
rem "%homeford%"\protoc -I=./ --cpp_out=./tmp/cpp/Packet/ PBMessage.proto

"%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -c#
"%homeford%"\CodeEngine.exe -i:PBMessage.proto -o:tmp\cs\PBMessage.cs -c:csharp

rem 
copy /y %SrcFolder%\cs\*.cs  %DestDir%\PacketStream\

rem 增加新消息包
cd %SrcFolder%\cs\PacketHandler
for %%a in (*.cs) do (
	if not exist  %DestDir%\PacketHandler\%%a (
		copy %%a %DestDir%\PacketHandler\
		svn add %DestDir%\PacketHandler\%%a
	)
)

rem 删除废弃消息包
cd %DestDir%\PacketHandler
for %%a in (*.cs) do (
	if not exist %SrcFolder%\cs\PacketHandler\%%a (
		svn del %%a
		if exist %%a.meta svn del %%a.meta
	)
)

echo Complete!
pause
@echo on
