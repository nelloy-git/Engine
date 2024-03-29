/*
 * File:   Log.cpp
 * Author: Vasily Ashitkov    v.ashitkov@wisetech.pro
 *
 * Created on December 9, 2015, 4:19 PM
 */

#include <thread>
#include <stdio.h>

#ifndef _WIN32
#include <cxxabi.h>
#endif

#include "Log.h"

std::mutex Log::_mutex;

Log::Log(const std::string &file_path,
         const int file_line,
         const std::string &method_name,
         int level) :
    __level(0){

    _mutex.lock();

    std::string lvl;
    switch (level){
        case ERR:
            lvl = "ERR";
            std::cout << file_path << ":" << file_line << std::endl;
        case WRN:
            lvl = lvl.size() > 0 ? lvl : "Warn";
            std::cout << _demandle(method_name) << std::endl;
        default:
            lvl = lvl.size() > 0 ? lvl : "Msg";
            auto time = _getTime();
            time = time.substr(0, time.size() - 1);
            std::cout << "[" << time << "]" << std::endl;
            std::cout << "{" << lvl << "}: ";
    }
}

Log::~Log() {
    std::cout << std::endl << std::endl;
    _mutex.unlock();
}

std::string Log::_getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&t);
}

std::string Log::_demandle(const std::string &class_or_method){
#ifndef _WIN32
    int status;
    auto name = abi::__cxa_demangle(class_or_method.c_str(), nullptr, 0, &status);
    if (status != 0){
        return class_or_method;
    }
    std::string res(name);
    delete name;
    return res;
#else
    return class_or_method;
#endif
}