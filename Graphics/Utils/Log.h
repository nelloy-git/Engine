#pragma once

#include <mutex>
#include <iostream>
#include <vector>
#include <string>

#define MSG (0)
#define WRN (1)
#define ERR (2)

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define LOG(lvl) Log(__FILE__, __LINE__, __PRETTY_FUNCTION__, lvl)

class Log {
public:
    Log(const std::string &file_path,
        const int file_line,
        const std::string &method_name,
        int level = 0);
    virtual ~Log();

    template<typename T>
    Log& operator<<(T val) {
        std::cout << val;
        return *this;
    }

private:
    static std::string _getTime();
    static std::string _demandle(const std::string &class_or_method);

    int __level;
    
    static std::mutex _mutex;
};
