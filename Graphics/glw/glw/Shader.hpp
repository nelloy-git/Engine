#pragma once

#include <memory>
#include <string>

#include "glw/Utils.hpp"

namespace glw {

class Shader {
public:
    Shader(ShaderType type, const std::string& code) :
        id(_newId(type)){
        auto c_str = code.c_str();
        glShaderSource(id, 1, &c_str, nullptr);
        glCompileShader(id);
        _verifyCompilation();
    };

    inline virtual ~Shader(){
        glDeleteShader(id);
    }

    const GLuint id;

private:
    inline GLuint _newId(ShaderType type){
        return glCreateShader(gl(type));
    }

    void _verifyCompilation(){
        auto res = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &res);
        if (res == GL_FALSE){
            char *msg = new char[8192];
            GLsizei msglen;
            glGetShaderInfoLog(id, 8192, &msglen, msg);
            glDeleteShader(id);
            throw std::invalid_argument("GLwrap::Shader: " + std::string(msg));
        }
    }
};

}