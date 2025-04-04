#pragma once

#include <card.hpp>

class Player {
protected:
    int score { 0 };

    Suit primarySuit;
    Suit secondarySuit;
    Value royal;

public:
    int getMultiplier(const Card& card) const;

    int getScore() const;

    virtual void takeTurn(const Card& card) = 0;
};

class CPUPlayer : public Player {
public:
    CPUPlayer();

    virtual void takeTurn(const Card& card) override;
};

class CLIPlayer : public Player {
public:
    CLIPlayer();

    virtual void takeTurn(const Card& card) override;
};