#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "World.hpp"
#include "NPCFactory.hpp"
#include "Observer.hpp"

// -------------------------
// Observer для тестов
// -------------------------
struct TestObserver : public Observer {
    std::vector<std::string> messages;
    void onEvent(const std::string& msg) override {
        messages.push_back(msg);
    }
};

// -------------------------
// NPCFactory TESTS
// -------------------------
TEST(NPCFactoryTest, CreateKnight) {
    auto npc = NPCFactory::create("Knight", 10, 20, "SirTest");
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Knight");
    EXPECT_EQ(npc->getName(), "SirTest");
}

TEST(NPCFactoryTest, CreateDragon) {
    auto npc = NPCFactory::create("Dragon", 5, 5, "Draco");
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Dragon");
}

TEST(NPCFactoryTest, UnknownTypeThrows) {
    EXPECT_THROW(NPCFactory::create("Unknown", 0, 0, "NoName"), std::runtime_error);
}

// -------------------------
// NPC Kill / isDead TESTS
// -------------------------
TEST(NPCTest, CanKillLogic) {
    auto knight = NPCFactory::create("Knight", 0, 0, "K");
    auto dragon = NPCFactory::create("Dragon", 0, 0, "D");
    auto pegasus = NPCFactory::create("Pegasus", 0, 0, "P");

    EXPECT_TRUE(knight->canKill(*dragon));
    EXPECT_FALSE(knight->canKill(*pegasus));

    EXPECT_TRUE(dragon->canKill(*pegasus));
    EXPECT_FALSE(dragon->canKill(*knight));

    EXPECT_FALSE(pegasus->canKill(*dragon));
    EXPECT_FALSE(pegasus->canKill(*knight));
}

// -------------------------
// FightVisitor TESTS
// -------------------------
TEST(FightVisitorTest, FightKillsCorrectly) {
    World world;
    auto knight = NPCFactory::create("Knight", 0, 0, "K");
    auto dragon = NPCFactory::create("Dragon", 0, 0, "D");

    world.add(knight);
    world.add(dragon);

    FightVisitor visitor;
    TestObserver observer;
    visitor.addObserver(std::make_shared<TestObserver>(observer));

    // Knight убивает Dragon
    visitor.fight(*knight, *dragon);

    EXPECT_TRUE(dragon->isDead());
    EXPECT_FALSE(knight->isDead());
}

// -------------------------
// World fightAll TEST
// -------------------------
TEST(WorldTest, FightAllRemovesDead) {
    World world;
    auto knight = NPCFactory::create("Knight", 0, 0, "K");
    auto dragon = NPCFactory::create("Dragon", 0, 0, "D");

    world.add(knight);
    world.add(dragon);

    FightVisitor visitor;
    world.fightAll(10.0, visitor); // радиус большой, чтобы встретились

    // Dragon должен умереть, удалиться из вектора
    for (auto& npc : world.getNpcs()) {
        EXPECT_FALSE(npc->isDead());
    }
}

// -------------------------
// World save/load TEST
// -------------------------
TEST(WorldTest, SaveLoad) {
    World world;
    auto knight = NPCFactory::create("Knight", 1, 2, "K");
    world.add(knight);

    world.save("test_world.txt");

    World loaded;
    loaded.load("test_world.txt");

    ASSERT_EQ(loaded.getNpcs().size(), 1);
    EXPECT_EQ(loaded.getNpcs()[0]->getType(), "Knight");
    EXPECT_EQ(loaded.getNpcs()[0]->getName(), "K");
    EXPECT_EQ(loaded.getNpcs()[0]->getX(), 1);
    EXPECT_EQ(loaded.getNpcs()[0]->getY(), 2);
}

// -------------------------
// main
// -------------------------
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
