// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
#include "NetHeader.h"

class NetSession;

enum class EventType : uint8
{
	Connect,
	Disconnect,
	Accept,
	Recv,
	Send
};

class CLIENT_API NetEvent : public OVERLAPPED
{
public:
	NetEvent(EventType type);

	void			Init();

public:
	EventType		eventType;
	NetObjectRef	owner;
};

class CLIENT_API ConnectEvent : public NetEvent
{
public:
	ConnectEvent() : NetEvent(EventType::Connect) { }
};

class CLIENT_API DisconnectEvent : public NetEvent
{
public:
	DisconnectEvent() : NetEvent(EventType::Disconnect) { }
};

class CLIENT_API AcceptEvent : public NetEvent
{
public:
	AcceptEvent() : NetEvent(EventType::Accept) { }

public:
	NetSessionRef	session = nullptr;
};

class CLIENT_API RecvEvent : public NetEvent
{
public:
	RecvEvent() : NetEvent(EventType::Recv) { }
};

class CLIENT_API SendEvent : public NetEvent
{
public:
	SendEvent() : NetEvent(EventType::Send) { }

	vector<SendBufferRef> sendBuffers;
};