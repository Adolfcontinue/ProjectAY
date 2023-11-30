// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
#include "NetHeader.h"


class CLIENT_API SendBuffer : public enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(BYTE* buffer, int32 allocSize);
	~SendBuffer();

public:
	BYTE* Buffer() { return _buffer; }
	int32 AllocSize() { return _allocSize; }
	int32 WriteSize() { return _writeSize; }
	void Close(uint32 writeSize);

private:
	BYTE* _buffer;
	uint32 _allocSize = 0;
	uint32 _writeSize = 0;
};
