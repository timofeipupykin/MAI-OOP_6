#include "FightVisitor.hpp"
#include "Knight.hpp"
#include "Pegasus.hpp"
#include "Dragon.hpp"

void FightVisitor::notify(const std::string& msg) {
    for (auto& o : observers)
        o->onEvent(msg);
}

void FightVisitor::addObserver(std::shared_ptr<Observer> o) {
    observers.push_back(o);
}

void FightVisitor::resolve(NPC& a, NPC& b) {
    if (a.canKill(b)) {
        notify(a.getType() + " " + a.getName() +
               " убил " + b.getType() + " " + b.getName());
    }
    if (b.canKill(a)) {
        notify(b.getType() + " " + b.getName() +
               " убил " + a.getType() + " " + a.getName());
    }
}

// --- БАЗОВЫЙ СЛУЧАЙ ---
void FightVisitor::fight(NPC& a, NPC& b) {
    resolve(a, b);
}

// --- НАПАДАЕТ КОНКРЕТНЫЙ ТИП ---
void FightVisitor::fight(Knight& a, NPC& b) { resolve(a, b); }
void FightVisitor::fight(Pegasus& a, NPC& b) { resolve(a, b); }
void FightVisitor::fight(Dragon& a, NPC& b) { resolve(a, b); }

// --- ЗАЩИЩАЕТСЯ КОНКРЕТНЫЙ ТИП ---
void FightVisitor::fight(NPC& a, Knight& b) { resolve(a, b); }
void FightVisitor::fight(NPC& a, Pegasus& b) { resolve(a, b); }
void FightVisitor::fight(NPC& a, Dragon& b) { resolve(a, b); }
