// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include <memory>
#include <mutex>
#include <set>
#include <array>
#include <vector>

using NetSessionRef = std::shared_ptr<class NetSession>;
using NetObjectRef = std::shared_ptr<class NetObject>;
using NetCoreRef = std::shared_ptr<class NetCore>;
using ListenerRef = std::shared_ptr<class Listener>;
using SendBufferRef = std::shared_ptr<class SendBuffer>;
using PacketSessionRef = std::shared_ptr<class PacketSession>;
using ServerServiceRef = std::shared_ptr<class ServerService>;
using SendBufferChunkRef = std::shared_ptr<class SendBufferChunk>;

using namespace std;

#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))
#define len16(arr)		static_cast<int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)		static_cast<int32>(sizeof(arr)/sizeof(arr[0]))



class CLIENT_API NetHeader
{
public:
	NetHeader();
	~NetHeader();
};
