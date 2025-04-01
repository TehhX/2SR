#pragma once

enum class Suit {
    spades,
    clubs,
    diamonds,
    hearts

,   max
};

enum class Value {
    ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king

,   max
};

struct Card {
    Suit suit {};
    Value value {};
};