#pragma once

template<typename T>
class singleton
{
protected:
    singleton() {}
    ~singleton() {}

    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;

    singleton(singleton&&) = delete;
    singleton& operator=(singleton&&) = delete;

public:
    static T& Get()
    {
        static T inst{};
        return inst;
    }
};