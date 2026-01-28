#ifndef DECK_ENGINE_HPP
#define DECK_ENGINE_HPP

#include "Card.hpp"
#include "Evaluator.hpp"
#include <vector>
#include <iostream>

class DeckEngine {
private:
    std::vector<Card> cardDb;
    std::vector<int> bestDeck;
    float maxScore = -1e9;
    long long permutationsProcessed = 0;

public:
    DeckEngine(const std::vector<Card>& db) : cardDb(db) {}

    void backtrack(int startIdx, std::vector<int>& currentDeck, int currentElixir) {
        // Pruning: Early exit if average elixir is obviously too high
        if (currentDeck.size() > 0 && (float)currentElixir / currentDeck.size() > 5.0f) {
            return;
        }

        // Target: 8 cards
        if (currentDeck.size() == 8) {
            permutationsProcessed++;
            float score = Evaluator::getScore(currentDeck, cardDb);
            if (score > maxScore) {
                maxScore = score;
                bestDeck = currentDeck;
            }
            return;
        }

        // State-space search
        for (int i = startIdx; i < cardDb.size(); ++i) {
            currentDeck.push_back(i);
            backtrack(i + 1, currentDeck, currentElixir + cardDb[i].elixir);
            currentDeck.pop_back();

            // Safety limit for demonstration
            if (permutationsProcessed >= 1000000) return;
        }
    }

    const std::vector<int>& getBestDeck() const { return bestDeck; }
    float getMaxScore() const { return maxScore; }
    long long getPermCount() const { return permutationsProcessed; }
};

#endif