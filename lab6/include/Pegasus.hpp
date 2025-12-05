#pragma once
#include "NPC.hpp"
#include "FightVisitor.hpp"

class Pegasus : public NPC {
public:
    Pegasus(double x, double y, std::string name)
        : NPC(x, y, name) {}
    
    std::string getType() const override { return "Pegasus"; }

    bool canKill(const NPC& other) const override {
        return false;
    }

    void accept(FightVisitor& v, NPC& other) override {
        v.fight(*this, other);
    }
};
