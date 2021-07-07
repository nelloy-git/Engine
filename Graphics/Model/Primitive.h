#pragma once

#include <optional>
#include <map>
#include <unordered_map>
#include <vector>

#include "Model/Buffer/BufferGL.h"
#include "Model/Material.h"

namespace GLwrap {
    class Array;
    class Program;
}

namespace Graphics::Model {

struct PrimitiveTarget {
    std::shared_ptr<BufferGL> pos;
    std::shared_ptr<BufferGL> norm;
    std::shared_ptr<BufferGL> tang;
};

class Primitive {
    template<typename T>
    using Ref = std::shared_ptr<T>;

public:
    Primitive() = default;
    virtual ~Primitive() = default;

    void initGL(const GLwrap::Program &prog);
    GLwrap::Program const *getInitedProgram();
    bool draw(const GLwrap::Program &prog);
    bool draw(const GLwrap::Program &prog) const;

    PrimitiveDrawMode mode;
    Ref<BufferGL> indices;
    Ref<Material> material;
    std::map<PrimitiveAttribute, Ref<BufferGL>> attributes;
    std::vector<PrimitiveTarget> targets;

private:
    bool _verifyLoc(int loc, const std::string &name);

    GLwrap::Program const *_inited_prog = nullptr;
    Ref<GLwrap::Array> _vao = nullptr;
};

}