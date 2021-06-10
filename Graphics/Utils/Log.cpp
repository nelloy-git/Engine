/*
 * File:   Log.cpp
 * Author: Vasily Ashitkov    v.ashitkov@wisetech.pro
 *
 * Created on December 9, 2015, 4:19 PM
 */

#include <thread>
#include <stdio.h>

#include "Log.h"

Log::Log(const std::string class_name, const std::string method_name, int level) :
    _level(0){
    _mutex.lock();

    std::string lvl;
    switch (level){
        case 0: lvl = "Msg"; break;
        case 1: lvl = "Warn"; break;
        case 2: lvl = "ERR"; break;
        default: lvl = "Msg"; break;
    }

    std::cout << "{" << lvl << "}" << "[" << _getTime() << "] " << class_name << "." << method_name << ": ";
}

Log::~Log() {
    std::cout << std::endl;
    _mutex.unlock();
}

std::string Log::_getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&t);
}
