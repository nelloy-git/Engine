#pragma once

#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <mutex>

template<typename ... Args>
class Event {
public:
    Event(){};
    virtual ~Event(){};

    uint64_t add(std::function<void(Args...)> callback){
        std::lock_guard<std::mutex> lg(_lock);

        uint64_t id = _id_counter++;
        while (_actions.find(id) != _actions.end()){
            uint64_t id = _id_counter++;
        }

        _actions[id] = callback;
        return id;
    };

    bool remove(uint64_t callback_id){
        std::lock_guard<std::mutex> lg(_lock);

        auto found = _actions.find(callback_id);
        if (found == _actions.end()){
            return false;
        }
        _actions.erase(found);
        return true;
    };

    void run(Args... args){
        std::lock_guard<std::mutex> lg(_lock);
        for (auto it : _actions){
            it.second(args...);
        }
    };

protected:
    std::mutex _lock;
    uint64_t _id_counter = 0;
    std::map<uint64_t, std::function<void(Args...)>> _actions;
};