#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <unordered_map>

#include "GLwrap/Shader.h"

namespace GLwrap {

class Program {
public:

    explicit Program(const std::vector<const Shader *> &attach);
    Program(const Program &) = delete;

    inline virtual ~Program(){
        glDeleteProgram(id);
    };

    void use() const;

    const GLuint id;

    // Subroutines
    
    // Number of subroutine signatures
    inline GLint getSubroutinesCount(ShaderType type){
        GLint count;
        glGetProgramStageiv(id, static_cast<GLenum>(type), GL_ACTIVE_SUBROUTINE_UNIFORMS, &count);
        return count;
    };

    // Location of subroutine signature
    inline GLint getSubroutineLoc(ShaderType type, const std::string &name){
        return glGetSubroutineUniformLocation(id, static_cast<GLenum>(type), name.c_str());
    };

    // Index of subroutine instance
    inline GLint getSubroutineIndex(ShaderType type, const std::string &name){
        return glGetSubroutineIndex(id, static_cast<GLenum>(type), name.c_str());
    };

    // Apply subroutines idices to locations.
    // list.size() == getSubroutinesCount(...)
    // list[getSubroutineLoc(...)] = getSubroutineIndex(...)
    bool setSubroutines(ShaderType type,
                        const std::vector<GLuint> &list,
                        bool ignore_checks = false);

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
    std::unordered_map<ShaderType, std::vector<GLuint>> _subroutines;
};

}