#pragma once

#include <string>

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

Suit randSuit();

Suit randSuit(Suit exclude);

Value randRoyal();

Suit takeSuit(std::string_view input);

Value takeValue(std::string_view input);

bool isFace(Value value);

class Card {
private:
    Suit suit;
    Value value;

public:
    Card(Suit suit, Value value);

    const Suit& getSuit() const;

    const Value& getValue() const;
};

std::string_view getSuitString(Suit suit);

std::string_view getSuitString(const Card& card);

std::string_view getValueString(Value value);

std::string_view getValueString(const Card& card);

std::ostream& operator<<(std::ostream& out, const Card& card);
