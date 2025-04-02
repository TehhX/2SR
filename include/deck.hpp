#pragma once

#include <vector>

#include <card.hpp>

constexpr size_t deckSize { 52 };

class Deck {
private:
    std::vector<Card> deck;

public:
    Deck();

    Card takeCard();
    void reset();
};