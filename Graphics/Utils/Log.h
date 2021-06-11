#pragma once

#include <mutex>
#include <iostream>
#include <vector>
#include <string>

#define MSG (0)
#define WRN (1)
#define ERR (2)
#define LOG(x) Log(__FILE__, __LINE__, typeid(*this).name(), __func__, x)

class Log {
public:
    Log(const std::string file_path,
        const int file_line,
        const std::string class_name,
        const std::string method_name,
        int level = 0);
    virtual ~Log();

    template<typename T>
    Log& operator<<(T val) {
        std::cout << val;
        return *this;
    }

private:
    static std::string __getTime();

    int __level;
    
    static std::mutex __mutex;
};
