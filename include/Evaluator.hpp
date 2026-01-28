#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "Card.hpp"
#include <vector>

class Evaluator {
public:
    // Global synergy matrix: synergyMatrix[id1][id2]
    static float synergyMatrix[100][100];

    static float getScore(const std::vector<int>& deck, const std::vector<Card>& db) {
        float score = 0.0f;
        uint32_t combinedRoles = 0;
        int totalElixir = 0;

        for (size_t i = 0; i < deck.size(); ++i) {
            const Card& c1 = db[deck[i]];
            combinedRoles |= c1.roles;
            totalElixir += c1.elixir;

            // Synergy O(N^2) where N=8
            for (size_t j = i + 1; j < deck.size(); ++j) {
                score += synergyMatrix[deck[i]][deck[j]];
            }
        }

        // Heuristic: Elixir Balance (Target 3.0 - 4.0)
        float avgElixir = totalElixir / 8.0f;
        if (avgElixir < 3.0f || avgElixir > 4.0f) score -= 150.0f;

        // Heuristic: Role Coverage
        if (!(combinedRoles & WIN_CONDITION)) score -= 300.0f;
        if (!(combinedRoles & AIR_DEFENSE))   score -= 200.0f;
        if (!(combinedRoles & SPELL))         score -= 100.0f;

        return score;
    }
};

#endif