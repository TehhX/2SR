#include <cassert>

#include <playerDetails.hpp>

PlayerDetails::PlayerDetails(Suit primarySuit, Suit secondarySuit, Value royal)
: primarySuit { primarySuit }, secondarySuit { secondarySuit }, royal { royal } {
    assert(royal >= Value::jack); // Can't be a pip-card
}

Suit PlayerDetails::getPrimarySuit() const {
    return primarySuit;
}

Suit PlayerDetails::getSecondarySuit() const {
    return secondarySuit;
}

Value PlayerDetails::getRoyal() const {
    return royal;
}

void PlayerDetails::addPoints(const Card& card) {
    // TODO
}