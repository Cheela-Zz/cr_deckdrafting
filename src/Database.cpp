#include "Card.hpp"
#include "Evaluator.hpp"
#include <vector>

float Evaluator::synergyMatrix[100][100] = {0};

std::vector<Card> initializeDatabase() {
    std::vector<Card> db;
    for (int i = 0; i < 100; ++i) {
        uint32_t role = NONE;
        int cost = 2 + (i % 5);

        if (i % 12 == 0) role |= WIN_CONDITION | TANK;
        else if (i % 8 == 0) role |= SPELL;
        else if (i % 5 == 0) role |= AIR_DEFENSE | AOE_DAMAGE;
        else role |= CYCLE_CARD;

        db.push_back({i, "Card_" + std::to_string(i), cost, role});
    }

    // Pre-calculating some synergies (e.g., Tank + AOE Support)
    Evaluator::synergyMatrix[0][5] = 50.5f; 
    Evaluator::synergyMatrix[12][10] = 40.0f;
    
    return db;
}