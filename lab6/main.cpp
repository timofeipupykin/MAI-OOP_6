#include <iostream>
#include "World.hpp"
#include "Observer.hpp"

int main() {
    World w;

    // Добавление NPC
    w.add(NPCFactory::create("Knight", 100, 100, "Arthur"));
    w.add(NPCFactory::create("Dragon", 120, 110, "Smaug"));
    w.add(NPCFactory::create("Pegasus", 130, 130, "Light"));

    std::cout << "=== Объекты ===\n";
    w.print();

    // Настраиваем бой
    FightVisitor visitor;
    visitor.addObserver(std::make_shared<ConsoleObserver>());
    visitor.addObserver(std::make_shared<FileObserver>());

    std::cout << "\n=== Бой ===\n";
    w.fightAll(50, visitor);

    std::cout << "\n=== После боя ===\n";
    w.print();

    // Сохранение и загрузка
    w.save("world.txt");

    return 0;
}
