#pragma once

namespace Graphics::Render {

class ShaderInput {
public:
    ShaderInput() = default;
    virtual ~ShaderInput() = 0;
};

inline ShaderInput::~ShaderInput(){};



class ShaderVertex {
public:
    ShaderVertex() = default;
    virtual ~ShaderVertex() = 0;
};

inline ShaderVertex::~ShaderVertex(){};



class ShaderFragment {
public:
    ShaderFragment() = default;
    virtual ~ShaderFragment() = 0;
};

inline ShaderFragment::~ShaderFragment(){};

}