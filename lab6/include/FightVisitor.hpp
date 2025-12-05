#pragma once
#include <vector>
#include <memory>
#include <string>

#include "Observer.hpp"
#include "NPC.hpp"

class Knight;
class Pegasus;
class Dragon;

class FightVisitor {
    std::vector<std::shared_ptr<Observer>> observers;

    void notify(const std::string& msg);

    void resolve(NPC& a, NPC& b);

public:
    void addObserver(std::shared_ptr<Observer> o);

    virtual void fight(NPC& a, NPC& b);
    virtual void fight(Knight& a, NPC& b);
    virtual void fight(Pegasus& a, NPC& b);
    virtual void fight(Dragon& a, NPC& b);

    virtual void fight(NPC& a, Knight& b);
    virtual void fight(NPC& a, Pegasus& b);
    virtual void fight(NPC& a, Dragon& b);
};
