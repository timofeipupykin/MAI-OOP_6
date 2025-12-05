#pragma once
#include "NPC.hpp"
#include "FightVisitor.hpp"

class Dragon : public NPC {
public:
    Dragon(int x, int y, std::string name)
        : NPC(x, y, name) {}

    std::string getType() const override { return "Dragon"; }

    bool canKill(const NPC& other) const override {
        return other.getType() == "Pegasus";
    }

    void accept(FightVisitor& v, NPC& other) override {
        v.fight(*this, other);
    }
};
