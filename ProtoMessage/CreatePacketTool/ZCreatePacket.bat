echo on

echo C++和CSharp消息包创建工具V1.0

set homeford=%cd%
echo %homeford%
cd..
cd..
set workpath=%cd%
cd..
cd..
set ServerPath=%cd%
cd "%homeford%"

rem 设置Cpp目标文件夹
set DstCppFolder=%ServerPath%\Server\Project\Server\Server\Server\Common\Packet

rem 设置Csharp目标文件夹
set DstCSharpFolder=%workpath%\Client\Assets\FengYun\Script\GameLogic\NetWork\PacketStream

rmdir /Q /S tmp

rem 设置源文件夹，里面有生成的c++和csharp消息包
set SrcFolder=%homeford%\tmp

"%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -cpp -c#
"%homeford%"\protoc -I=./ --cpp_out=./tmp/cpp/Packet/ PBMessage.proto

"%homeford%"\CodeEngine.exe -i:PBMessage.proto -o:tmp\cs\PBMessage.cs -c:csharp
rem "%homeford%"\FigurePacket.exe -i:PBMessage.proto -s:0 -c#

copy /Y %SrcFolder%\cpp\Packet\*.* "%DstCppFolder%"\Packet\
copy /Y %SrcFolder%\cpp\PacketHandler\*.* "%DstCppFolder%"\PacketHandler\

copy /Y %SrcFolder%\cs\*.cs "%DstCSharpFolder%"\

cd "%homeford%"
echo Complete!

pause


