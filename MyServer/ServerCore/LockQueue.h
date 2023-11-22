#pragma once

template <typename T>
class LockQueue
{
public:
	void Push(T item)
	{
		WRITE_LOCK;
		_Items.push(item);
	}

	T Pop()
	{
		WRITE_LOCK;
		if (_Items.empty())
			return T();

		T ret = _Items.front();
		_Items.pop();
		return ret;
	}

	void PopAll(Vector<T>& items)
	{
		WRITE_LOCK;
		while (T item = Pop())
		{
			items.push_back(item);
		}
	}

	void Clear()
	{
		WRITE_LOCK;
		_Items = Queue<T>();
	}

private:
	USE_LOCK;
	Queue<T> _Items;
};

