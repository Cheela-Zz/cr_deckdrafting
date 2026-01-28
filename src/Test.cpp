#include "Card.hpp"
#include "Evaluator.hpp"
#include "DeckEngine.hpp"
#include <iostream>
#include <vector>
#include <chrono>

// Access the database initialization from Database.cpp
extern std::vector<Card> initializeDatabase();

void runSynergyTest() {
    auto db = initializeDatabase();
    // Manually set a massive synergy between Card 0 and Card 1
    Evaluator::synergyMatrix[0][1] = 500.0f;

    std::vector<int> deckWithSynergy = {0, 1, 10, 11, 12, 13, 14, 15};
    std::vector<int> deckNoSynergy   = {20, 21, 10, 11, 12, 13, 14, 15};

    float score1 = Evaluator::getScore(deckWithSynergy, db);
    float score2 = Evaluator::getScore(deckNoSynergy, db);

    std::cout << "[Test] Synergy Logic: ";
    if (score1 > score2) std::cout << "PASSED" << std::endl;
    else std::cout << "FAILED" << std::endl;
}

void runWinConTest() {
    auto db = initializeDatabase();
    // A deck of 8 random cards that are NOT Win Conditions (most are CYCLE_CARDs)
    // Assuming IDs 1-8 in our init logic are not WinCons
    std::vector<int> badDeck = {1, 2, 3, 4, 5, 6, 7, 8};
    
    float score = Evaluator::getScore(badDeck, db);
    
    std::cout << "[Test] Win-Condition Constraint: ";
    if (score < 0) std::cout << "PASSED (Penalty applied correctly)" << std::endl;
    else std::cout << "FAILED (No penalty for missing WinCon)" << std::endl;
}

void runPerformanceTest() {
    auto db = initializeDatabase();
    DeckEngine engine(db);
    std::vector<int> current;

    auto start = std::chrono::high_resolution_clock::now();
    engine.backtrack(0, current, 0); 
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    double permsPerSec = engine.getPermCount() / diff.count();

    std::cout << "[Test] Performance: " << permsPerSec << " perms/sec" << std::endl;
    if (permsPerSec >= 100000.0) std::cout << "      -> PASSED (Met 10^5 threshold)" << std::endl;
    else std::cout << "      -> FAILED (Below 10^5 threshold)" << std::endl;
}