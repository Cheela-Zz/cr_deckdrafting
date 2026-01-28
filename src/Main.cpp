#include "DeckEngine.hpp"
#include "Card.hpp"
#include <iostream>
#include <chrono>
#include <string>

extern std::vector<Card> initializeDatabase();

// Declarations of tests from Test.cpp
void runSynergyTest();
void runWinConTest();
void runPerformanceTest();

int main(int argc, char* argv[]) {
    // Check if the user wants to run tests
    if (argc > 1 && std::string(argv[1]) == "--test") {
        std::cout << "=== RUNNING PROJECT UNIT TESTS ===" << std::endl;
        runSynergyTest();
        runWinConTest();
        runPerformanceTest();
        return 0;
    }

    // Default: Run the AI
    auto cardDb = initializeDatabase();
    DeckEngine engine(cardDb);

    std::cout << "Starting AI Deck Search..." << std::endl;
    std::vector<int> current;
    engine.backtrack(0, current, 0);

    std::cout << "Best Deck Found Score: " << engine.getMaxScore() << std::endl;
    for (int id : engine.getBestDeck()) {
        std::cout << " - " << cardDb[id].name << std::endl;
    }

    return 0;
}