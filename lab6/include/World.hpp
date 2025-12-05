#pragma once
#include <algorithm>
#include <vector>
#include <memory>
#include <fstream>
#include <cmath>
#include "NPCFactory.hpp"
#include "FightVisitor.hpp"


class World {
    private:
        std::vector<std::shared_ptr<NPC>> npcs;

    public:
        void add(std::shared_ptr<NPC> npc) {
            npcs.push_back(npc);
        }

        void print() {
            for (auto& npc : npcs) {
                if (!npc) continue;
                std::cout << npc->getType() << " " << npc->getName() << " (" << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }

        void save(const std::string& filename) {
            std::ofstream f(filename);
            for (auto& npc : npcs) {
                if (!npc) continue;
                f << npc->getType() << " "
                    << npc->getName() << " "
                    << npc->getX() << " " << npc->getY() << "\n";
            }
        }

        void load(const std::string& filename) {
            npcs.clear();
            std::ifstream f(filename);
            std::string type, name;
            double x, y;

            while (f >> type >> name >> x >> y) {
                npcs.push_back(NPCFactory::create(type, x, y, name));
            }
        }

        void fightAll(double radius, FightVisitor& v) {
            for (size_t i = 0; i < npcs.size(); i++) {
                for (size_t j = i + 1; j < npcs.size(); j++) {
                    auto& a = npcs[i];
                    auto& b = npcs[j];

                    if (!a || !b) continue;

                    double dx = a->getX() - b->getX();
                    double dy = a->getY() - b->getY();
                    double dist = sqrt(dx*dx + dy*dy);

                    if (dist <= radius) {
                        v.fight(*a, *b);
                    }
                }
            }

            npcs.erase(std::remove_if(npcs.begin(), npcs.end(), [](auto& p){ return p == nullptr; }), npcs.end());
        }
};
