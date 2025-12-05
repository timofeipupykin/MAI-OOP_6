#pragma once
#include "Knight.hpp"
#include "Pegasus.hpp"
#include "Dragon.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type, int x, int y, const std::string& name) {
        if (type == "Knight") return std::make_shared<Knight>(x, y, name);
        if (type == "Pegasus") return std::make_shared<Pegasus>(x, y, name);
        if (type == "Dragon") return std::make_shared<Dragon>(x, y, name);
        throw std::runtime_error("Unknown NPC type");
    }
};
