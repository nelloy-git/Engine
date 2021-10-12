#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>

namespace File {

std::unique_ptr<std::string> readString(const std::string &path){
    auto code = std::make_unique<std::string>();
    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        file.open(path);
        std::stringstream str_stream;

        std::string line;
        while(!file.eof()){
	        std::getline(file, line); // Saves the line in STRING.
	        *code += line + "\n"; 
        }
        file.close();
    } catch(std::ifstream::failure e){
        return nullptr;
    }

    return code;
};

}