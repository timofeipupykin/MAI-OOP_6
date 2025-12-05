#pragma once
#include "NPC.hpp"
#include "FightVisitor.hpp"

class Knight : public NPC {
public:
    Knight(int x, int y, std::string name)
        : NPC(x, y, name) {}

    std::string getType() const override { return "Knight"; }

    bool canKill(const NPC& other) const override {
        return other.getType() == "Dragon";
    }

    void accept(FightVisitor& v, NPC& other) override {
        v.fight(*this, other);
    }
};
