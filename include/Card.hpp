#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <cstdint>

// Bitmask for fast heuristic evaluation
enum CardRole : uint32_t {
    NONE = 0,
    WIN_CONDITION = 1 << 0,
    AOE_DAMAGE    = 1 << 1,
    AIR_DEFENSE   = 1 << 2,
    SPELL         = 1 << 3,
    TANK          = 1 << 4,
    CYCLE_CARD    = 1 << 5
};

struct Card {
    int id;
    std::string name;
    int elixir;
    uint32_t roles; // Combined bitmask
};

#endif