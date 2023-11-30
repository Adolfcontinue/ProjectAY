// Fill out your copyright notice in the Description page of Project Settings.


#include "NetWork/SendBuffer.h"

SendBuffer::SendBuffer(BYTE* buffer, int32 allocSize)
	: _buffer(buffer), _allocSize(allocSize)
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32 writeSize)
{
	if (!(_allocSize >= writeSize)) return;
	_writeSize = writeSize;
}

