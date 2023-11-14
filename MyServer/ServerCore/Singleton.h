template <typename T>
class Singleton
{
protected:
    Singleton() {};
    ~Singleton() {};
    Singleton(const Singleton& other) {};

private:
    static std::once_flag _check;
    static T* _instance;

public:
    static void Destroy()
    {
        if (_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;
        }
    }

public:
    static T& Instance()
    {
        std::call_once(_check, []()
            {
                _instance = new T();
                std::atexit(Destroy);
            });

        return *(_instance);
    }

};

template <typename T> 
T* Singleton <T>::_instance = nullptr;

template <typename T> 
std::once_flag Singleton<T>::_check;