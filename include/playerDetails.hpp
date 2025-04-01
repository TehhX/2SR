#pragma once

#include <card.hpp>

class PlayerDetails {
private:
    int score { 0 };

    const Suit primarySuit;
    const Suit secondarySuit;
    const Value royal;

public:
    PlayerDetails(Suit primarySuit, Suit secondarySuit, Value royal);

    Suit getPrimarySuit() const;
    Suit getSecondarySuit() const;
    Value getRoyal() const;

    void addPoints(const Card& card);
};