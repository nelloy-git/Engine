#include "Data/AssimpImporter.h"

using namespace Graphics::Data;

std::unordered_map<std::thread::id, std::shared_ptr<Assimp::Importer>> AssimpImporter::__thread2importer;

std::shared_ptr<Assimp::Importer> AssimpImporter::inst(){
    auto th_id = std::this_thread::get_id();
    auto found = __thread2importer.find(th_id);
    std::shared_ptr<Assimp::Importer> importer;

    if (found == __thread2importer.end()){
        importer = std::make_shared<Assimp::Importer>();
        __thread2importer[th_id] = importer;
    } else {
        importer = found->second;
    }

    return importer;
}

void AssimpImporter::clear(){
    for (auto it = __thread2importer.begin(); it != __thread2importer.end();){
        if (it->second.use_count() <= 1){
            __thread2importer.erase(it++);
        } else {
            ++it;
        }
    }
}