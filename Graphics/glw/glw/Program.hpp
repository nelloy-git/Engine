#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include "glw/Shader.hpp"

namespace glw {

class Program {
public:
    const GLuint id;

    explicit Program(const std::vector<Shader> &shaders) :
        id(_newId()){
        _linkShaders(shaders);
        _verifyLinkage();
    };

    Program(const Program &) = delete;

    inline virtual ~Program(){
        glDeleteProgram(id);
    };

    inline void use(){
        glUseProgram(id);
        _applySubroutines();
    };

    // Subroutines
    
    // Number of subroutine signatures
    inline GLint getSubroutinesCount(ShaderType type){
        GLint count;
        glGetProgramStageiv(id, gl(type), GL_ACTIVE_SUBROUTINE_UNIFORMS, &count);
        return count;
    };

    // Location of subroutine signature
    inline GLint getSubroutineLoc(ShaderType type, const std::string &name){
        return glGetSubroutineUniformLocation(id, gl(type), name.c_str());
    };

    // Index of subroutine instance
    inline GLint getSubroutineIndex(ShaderType type, const std::string &name){
        return glGetSubroutineIndex(id, gl(type), name.c_str());
    };

    // Apply subroutines idices to locations.
    // list.size() == getSubroutinesCount(...)
    // list[getSubroutineLoc(...)] = getSubroutineIndex(...)
    bool setSubroutines(ShaderType type,
                        const std::vector<GLuint> &subroutines,
                        bool ignore_checks = false){
        if (_verifySubroutines(type, subroutines)){
            _subroutines[type] = subroutines;
            return true;
        }
        return false;
    }

    // Static call for active program

    // Program must be in use.
    static inline void setUniform1vi(GLint loc, int val){
        glUniform1i(loc, val);
    };

    // Program must be in use.
    static inline void setUniform1vf(GLint loc, float val){
        glUniform1f(loc, val);
    };

    // Program must be in use.
    static inline void setUniformVec4f(GLint loc, const float *vec4){
        glUniform4fv(loc, 1, vec4);
    };

    // Program must be in use.
    static inline void setUniformMat4f(GLint loc, const float *mat4){
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat4);
    };

    // Program must be in use.
    static inline void setUniformFloatArray(GLint loc, const float *ptr, size_t size){
        glUniform1fv(loc, size, ptr);
    };

    inline GLint getAttribLoc(const std::string &name){
        return glGetAttribLocation(id, name.c_str());
    };

    inline GLint getUniformLoc(const std::string &name){
        return glGetUniformLocation(id, name.c_str());
    };

private:

    inline GLuint _newId(){
        return glCreateProgram();
    }

    inline void _linkShaders(const std::vector<Shader> shaders){
        for (int i = 0; i < shaders.size(); ++i){
            glAttachShader(id, shaders[i].id);
        }
        glLinkProgram(id);
    }

    void _verifyLinkage(){
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

    bool _verifySubroutines(ShaderType type,
                            const std::vector<GLuint> &list){
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

    void _applySubroutines(){
        for (auto &iter : _subroutines){
            glUniformSubroutinesuiv(gl(iter.first), iter.second.size(), iter.second.data());
        }
    }

    std::unordered_map<ShaderType, std::vector<GLuint>> _subroutines;
};

}