#pragma once

#include <mutex>
#include <iostream>
#include <vector>
#include <string>

#define MSG (0)
#define WRN (1)
#define ERR (2)
#define LOG(x) Log(typeid(*this).name(), __func__, x)

class Log {
public:
    Log(const std::string class_name, const std::string method_name, int level = 0);
    virtual ~Log();

    template<typename T>
    Log& operator<<(T val) {
        std::cout << val;
        return *this;
    }

private:
    static std::string _getTime();

    int _level;
    
    static std::mutex _mutex;
};
