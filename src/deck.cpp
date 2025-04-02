#include <algorithm>

#include <deck.hpp>
#include <randomNumbers.hpp>

Deck::Deck() {
    deck.reserve(deckSize);
    reset();
}

void Deck::reset() {
    deck.clear();

    for (int suitIndex { 0 }; suitIndex < static_cast<int>(Suit::max); suitIndex++)
        for (int valueIndex { 0 }; valueIndex < static_cast<int>(Value::max); valueIndex++)
            deck.push_back({ static_cast<Suit>(suitIndex), static_cast<Value>(valueIndex) });

    std::shuffle(deck.begin(), deck.end(), rnd::getGenerator());
}

Card Deck::takeCard() {
    Card card { deck.back() };
    deck.pop_back();
    return card;
}
