#pragma once
#include "Singleton.h"


template <typename Type, typename TKey, typename TValue>
class Table : public Singleton<Type>
{
public:
    Table()
    {
    }

    ~Table()
    {
        for (auto iter = _table.begin(); iter != _table.end(); iter++)
        {
            iter->second = nullptr;
        }
    }

public:
    virtual void Init() override {}

protected:
    std::unordered_map<TKey, TValue> _table;

public:
    void Insert(TKey key, TValue& value)
    {
        _table.insert(std::make_pair(key, value));
    }

    void Remove(TKey key)
    {
        auto value = _table.find(key);
        if (value == _table.end())
            return;

        value->second = nullptr;
        _table.erase(key);
    }

    TValue Find(TKey key) const
    {
        auto value = _table.find(key);
        if (value == _table.end())
            return nullptr;

        return value->second;
    }

    void Clear()
    {
        _table.clear();
    }

    long Size()
    {
        return _table.size();
    }
};


