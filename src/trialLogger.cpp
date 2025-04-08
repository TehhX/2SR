#include <trialLogger.hpp>

void Trial::setStartingDeck(const Deck& deck) {
    startDeck = deck;
}

Trial& Trial::setPlayerOne(Player* const player) {
    p1 = player;

    return *this;
}

Trial& Trial::setPlayerTwo(Player* const player) {
    p2 = player;

    return *this;
}

Trial::~Trial() {
    delete p1;
    delete p2;
}

TrialLogger::TrialLogger() {
    fileOut.open("latestTrial.csv");

    if (!fileOut.is_open())
        /* TODO: Implement error handling here. */;
    
    active = true;
}

void TrialLogger::addTrial(const Trial& trial) {
    trials.push_back(trial);
}

void TrialLogger::writeTrials() {
    if (!active)
        /* TODO: Implement error handling for trying to write twice here. */;

    // TODO: Write to file here
    
    active = false;
}
