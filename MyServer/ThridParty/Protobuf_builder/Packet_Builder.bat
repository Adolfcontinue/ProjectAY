@echo off
pushd %~dp0

echo "Builer Start"

protoc.exe -I=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C2P_ --send=P2C_
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=P2C_ --send=C2P_



IF ERRORLEVEL 1 PAUSE

echo.

XCOPY /Y Enum.pb.h "../../GameServer"
XCOPY /Y Enum.pb.cc "../../GameServer"
XCOPY /Y Struct.pb.h "../../GameServer"
XCOPY /Y Struct.pb.cc "../../GameServer"
XCOPY /Y Protocol.pb.h "../../GameServer"
XCOPY /Y Protocol.pb.cc "../../GameServer"
XCOPY /y ClientPacketHandler.h "../../GameServer"

XCOPY /Y Enum.pb.h "../../DummyClient"
XCOPY /Y Enum.pb.cc "../../DummyClient"
XCOPY /Y Struct.pb.h "../../DummyClient"
XCOPY /Y Struct.pb.cc "../../DummyClient"
XCOPY /Y Protocol.pb.h "../../DummyClient"
XCOPY /Y Protocol.pb.cc "../../DummyClient"
XCOPY /y ServerPacketHandler.h "../../DummyClient"

echo.
DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h

PAUSE