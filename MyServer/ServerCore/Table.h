#pragma once

class TableBase : public enable_shared_from_this<TableBase>
{

};

template <typename TKey, typename TValue>
class Table : public TableBase
{
public:
    Table()
    {
    }

    ~Table()
    {
        for (auto iter = _table.begin(); iter != _table.end(); iter++)
        {
        }
    }

public:
    virtual void Init(string path = "") {}

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
            return TValue();

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


