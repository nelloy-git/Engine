#include "glw/Program.hpp"

#include <stdexcept>

#include "glad/gl.h"

using namespace glw;

Program::Program(const std::vector<const Shader *> &attach) :
    id(glCreateProgram()){

    for (auto shader : attach){
        if (!shader) continue;
        glAttachShader(id, shader->id);
    }
    glLinkProgram(id);

    auto res = GL_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &res);
    if (res == GL_FALSE){
        char *c_msg = new char[8192];
        GLsizei msglen;
        glGetProgramInfoLog(id, 8192, &msglen, c_msg);
        std::string msg(c_msg);
        delete c_msg;
        throw std::invalid_argument("GLwrap::Program: " + msg);
    }
}


void Program::use() const {
    glUseProgram(id);
    for (auto &iter : _subroutines){
        glUniformSubroutinesuiv(static_cast<GLenum>(iter.first),
                                iter.second.size(), iter.second.data());
    }
}


bool Program::setSubroutines(ShaderType type,
                             const std::vector<GLuint> &list,
                             bool ignore_checks){
    if (!ignore_checks){
        if (list.size() != getSubroutinesCount(type)){
            return false;
        }

        for (int i = 0; i < list.size(); ++i){
            GLint compatible_count;
            glGetActiveSubroutineUniformiv(id, static_cast<GLenum>(type), i, GL_NUM_COMPATIBLE_SUBROUTINES, &compatible_count);

            GLint *compatible_list = new GLint[compatible_count];
            glGetActiveSubroutineUniformiv(id, static_cast<GLenum>(type), i, GL_COMPATIBLE_SUBROUTINES, compatible_list);

            bool failed = true;
            for (int j = 0; j < compatible_count; ++j){
                if (list[i] == compatible_list[j]){
                    failed = false;
                    break;
                }
            }

            delete[] compatible_list;

            if (failed){
                return false;
            }
        }
    }

    _subroutines[type] = list;
    return true;
}