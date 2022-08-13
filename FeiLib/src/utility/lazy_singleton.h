#pragma once
template<class SingletonType>
class lazy_singleton
{
public:
    lazy_singleton() = delete;
    lazy_singleton(const lazy_singleton&) = delete;
    lazy_singleton& operator=(const lazy_singleton&) = delete;
    static SingletonType& get_instance()
    {
        static SingletonType instance;
        return instance;
    }
};
