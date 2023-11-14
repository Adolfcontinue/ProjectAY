#pragma once

class BufferWriter
{
public:
	BufferWriter();
	BufferWriter(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferWriter();

	BYTE* Buffer() { return _buffer; }
	uint32 Size() { return _size; }
	uint32 WriteSize() { return _pos; }
	uint32 FreeSize() { return _size - _pos; }


	template <typename T>
	bool Write(T* src) { return Write(src, sizeof(T)); }
	bool Write(void* src, int len);

	template <typename T>
	T* Reserve();

	template <typename T>
	BufferWriter& operator<<(T&& src);

private:
	BYTE* _buffer;
	uint32 _pos;
	uint32 _size;
};

template <typename T>
T* BufferWriter::Reserve()
{
	if (FreeSize() < sizeof(T))
		return nullptr;

	T* retval = reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += sizeof(T);
	return retval;
}

template <typename T>
BufferWriter& BufferWriter::operator<<(T&& src)
{
	//::memcpy(&_buffer[_pos], &src, sizeof(T));
	using DataType = std::remove_reference_t<T>;
	*reinterpret_cast<DataType*>(&_buffer[_pos]) = std::forward<DataType>(src);
	_pos += sizeof(T);
	return *this;
}

