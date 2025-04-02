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

Suit randSuit(const Suit& exclude) {
    std::vector<Suit> possibleSuits {
        static_cast<Suit>(0),
        static_cast<Suit>(1),
        static_cast<Suit>(2),
        static_cast<Suit>(3)
    };

    possibleSuits.erase(possibleSuits.begin() + static_cast<int>(exclude) - 1);

    return possibleSuits[rnd::randomInt(0, 2)];
}

Value randValue() {
    return static_cast<Value>(rnd::randomInt(0, static_cast<int>(Value::max)));
}

const Suit& Card::getSuit() const {
    return suit;
}

const Value& Card::getValue() const {
    return value;
}

bool isFace(const Value& value) {
    return value >= Value::jack;
}

std::string_view getSuitString(const Card& card) {
    switch(card.getSuit()) {

    case Suit::spades:   return "spades";
    case Suit::clubs:    return "clubs";
    case Suit::diamonds: return "diamonds";
    case Suit::hearts:   return "hearts";

    default: throw "Bad suit passed to get().\n";

    }
}

std::string_view getValueString(const Card& card) {
    switch(card.getValue()) {

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

    default: throw "Bad value passed to get().\n";

    }
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
    std::string toRet { getValueString(card) };
    toRet.append(" of ");
    toRet.append(getSuitString(card));

    return out << toRet;
}