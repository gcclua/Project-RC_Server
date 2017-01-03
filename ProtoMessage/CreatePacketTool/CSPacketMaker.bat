@echo off
cls
color 0b

echo CSharp��Ϣ����������V1.0
set homeford=%cd%
cd..
cd..
set workpath=%cd%
cd "%homeford%"

rem ����CsharpĿ���ļ���
set DestDir=%workpath%\Client\Assets\FengYun\Script\GameLogic\NetWork

rem ����Դ�ļ��У����������ɵ�CSharp��Ϣ��
set SrcFolder=%homeford%\tmp

rem ɾ��tmp�ļ���
if exist %SrcFolder% rmdir /Q /S %SrcFolder%

rem "%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -cpp -c#
rem "%homeford%"\protoc -I=./ --cpp_out=./tmp/cpp/Packet/ PBMessage.proto

"%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -c#
"%homeford%"\CodeEngine.exe -i:PBMessage.proto -o:tmp\cs\PBMessage.cs -c:csharp

rem 
copy /y %SrcFolder%\cs\*.cs  %DestDir%\PacketStream\

rem ��������Ϣ��
cd %SrcFolder%\cs\PacketHandler
for %%a in (*.cs) do (
	if not exist  %DestDir%\PacketHandler\%%a (
		copy %%a %DestDir%\PacketHandler\
		svn add %DestDir%\PacketHandler\%%a
	)
)

rem ɾ��������Ϣ��
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
