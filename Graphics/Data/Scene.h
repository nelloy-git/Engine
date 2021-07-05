#pragma once

#include <vector>
#include <unordered_map>

namespace Graphics {

class Scene {
public:
    Scene();
    virtual ~Scene();

    void draw();
    void draw() const;

    std::vector<std::shared_ptr<Node>> nodes;

private:
};

}