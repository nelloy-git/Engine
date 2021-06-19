/*
 * File:   Log.cpp
 * Author: Vasily Ashitkov    v.ashitkov@wisetech.pro
 *
 * Created on December 9, 2015, 4:19 PM
 */

#include <thread>
#include <stdio.h>

#include "Log.h"

std::mutex Log::__mutex;

Log::Log(const std::string file_path,
         const int file_line,
         const std::string class_name,
         const std::string method_name,
         int level) :
    __level(0){

    __mutex.lock();

    std::string lvl;
    switch (level){
        case 0: lvl = "Msg"; break;
        case 1: lvl = "Warn"; break;
        case 2: lvl = "ERR"; break;
        default: lvl = "Msg"; break;
    }

    auto time = __getTime();
    time = time.substr(0, time.size() - 1);

    std::cout << file_path<< ":" << file_line << std::endl;
    std::cout << "{" << lvl << "}"
              << "[" << time << "]" << std::endl;
    std::cout << class_name << "." << method_name << ": ";
}

Log::~Log() {
    std::cout << std::endl << std::endl;
    __mutex.unlock();
}

std::string Log::__getTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&t);
}
