#pragma once
#include <functional>

using CallbackType = std::function<void()>;

class Job
{
public:
	Job(CallbackType&& callback) : _callBack(std::move(callback))
	{
	}

	template<typename T, typename Ret, typename... Args>
	Job(shared_ptr<T> owner, Ret(T::* memFunc)(Args...), Args&&... args)
	{
		_callBack = [owner, memFunc, args...]()
			{
				(owner.get()->*memFunc)(args...);
			};
	}

	void Execute()
	{
		_callBack();
	}


private:
	CallbackType _callBack;
};

