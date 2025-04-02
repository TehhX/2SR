#pragma once

#include <card.hpp>

class Player {
protected:
    int roundNum { 1 };
    int score { 0 };

    Suit primarySuit;
    Suit secondarySuit;
    Value royal;

public:
    int getMultiplier(const Card& card) const;

    virtual void takeTurn(const Card& card) = 0;
};

class CPUPlayer : public Player {
    CPUPlayer();

    virtual void takeTurn(const Card& card) override;
};

class CLIPlayer : public Player {
    CLIPlayer();

    virtual void takeTurn(const Card& card) override;
};