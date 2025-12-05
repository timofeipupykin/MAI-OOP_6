#pragma once

#include <string>
#include <stdexcept>


class FightVisitor;

class NPC{
    private:
        int x;
        int y;
        std::string name;

    protected:
        void valid() {
            if (x <= 0 && 500 <= x) {
                throw std::runtime_error("x is out of range(0, 500)");
            }
            if (y <= 0 && 500 <= y) {
                throw std::runtime_error("y is out of range(0, 500)");
            }
        }

    public:
        NPC(int x, int y, std::string name) : x(x), y(y), name(name) { valid(); }
        ~NPC() = default;

        int getX() const { return x; }
        int getY() const { return y; }
        std::string getName() const { return name; }
        virtual std::string getType() const = 0;
        
        virtual bool canKill(const NPC& other) const = 0;

        virtual void accept(FightVisitor& v, NPC& other) = 0;
};