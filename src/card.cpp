#include <cassert>
#include <vector>

#include <card.hpp>
#include <randomNumbers.hpp>

Card::Card(Suit suit, Value value)
: suit { suit }, value { value }
{
    assert(suit != Suit::max);
    assert(value != Value::max);
}

Suit randSuit() {
    return static_cast<Suit>(rnd::randomInt(0, static_cast<int>(Suit::max)));
}

Suit randSuit(Suit exclude) {
    std::vector<Suit> possibleSuits {
        static_cast<Suit>(0),
        static_cast<Suit>(1),
        static_cast<Suit>(2),
        static_cast<Suit>(3)
    };

    possibleSuits.erase(possibleSuits.begin() + static_cast<int>(exclude) - 1);

    return possibleSuits[rnd::randomInt(0, 2)];
}

Value randRoyal() {
    return static_cast<Value>(rnd::randomInt(static_cast<int>(Value::jack), static_cast<int>(Value::king)));
}

Suit takeSuit(std::string_view input) {
    if      (input == getSuitString(Suit::spades))   return Suit::spades;
    else if (input == getSuitString(Suit::clubs))    return Suit::clubs;
    else if (input == getSuitString(Suit::diamonds)) return Suit::diamonds;
    else if (input == getSuitString(Suit::hearts))   return Suit::hearts;

    else
        throw "Bad value passed to takeSuit.\n";
}

Value takeValue(std::string_view input) {
    if      (input == getValueString(Value::ace))   return Value::ace;
    else if (input == getValueString(Value::two))   return Value::two;
    else if (input == getValueString(Value::three)) return Value::three;
    else if (input == getValueString(Value::four))  return Value::four;
    else if (input == getValueString(Value::five))  return Value::five;
    else if (input == getValueString(Value::six))   return Value::six;
    else if (input == getValueString(Value::seven)) return Value::seven;
    else if (input == getValueString(Value::eight)) return Value::eight;
    else if (input == getValueString(Value::nine))  return Value::nine;
    else if (input == getValueString(Value::ten))   return Value::ten;
    else if (input == getValueString(Value::jack))  return Value::jack;
    else if (input == getValueString(Value::queen)) return Value::queen;
    else if (input == getValueString(Value::king))  return Value::king;

    else
        throw "Bad value passed to takeValue.\n";
}

const Suit& Card::getSuit() const {
    return suit;
}

const Value& Card::getValue() const {
    return value;
}

bool isFace(Value value) {
    return value >= Value::jack;
}

std::string_view getSuitString(Suit suit) {
    switch(suit) {
    case Suit::spades:   return "spades";
    case Suit::clubs:    return "clubs";
    case Suit::diamonds: return "diamonds";
    case Suit::hearts:   return "hearts";

    default:
        throw "Bad suit passed to getSuitString.\n";
    }
}

std::string_view getSuitString(const Card& card) {
    return getSuitString(card.getSuit());
}

std::string_view getValueString(Value value) {
    switch(value) {
    case Value::ace:   return "ace";
    case Value::two:   return "two";
    case Value::three: return "three";
    case Value::four:  return "four";
    case Value::five:  return "five";
    case Value::six:   return "six";
    case Value::seven: return "seven";
    case Value::eight: return "eight";
    case Value::nine:  return "nine";
    case Value::ten:   return "ten";
    case Value::jack:  return "jack";
    case Value::queen: return "queen";
    case Value::king:  return "king";

    default:
        throw "Bad value passed to getValueString.\n";
    }
}

std::string_view getValueString(const Card& card) {
    return getValueString(card.getValue());
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
    std::string toRet { getValueString(card) };
    toRet.append(" of ");
    toRet.append(getSuitString(card));

    return out << toRet;
}