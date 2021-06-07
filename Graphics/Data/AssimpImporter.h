#pragma once

#include <unordered_map>
#include <memory>
#include <thread>

#include "assimp/Importer.hpp"

namespace Graphics::Data {

class AssimpImporter {
public:
    static std::shared_ptr<Assimp::Importer> inst();
    static void clear();

private:
    static std::unordered_map<std::thread::id, std::shared_ptr<Assimp::Importer>> __thread2importer;
};

}