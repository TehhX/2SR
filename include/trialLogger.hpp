#pragma once

#include <vector>
#include <fstream>

#include <player.hpp>
#include <deck.hpp>

class Trial final {
private:
    Deck startDeck;
    Player* p1;
    Player* p2;

public:
    inline Trial() {}

    void setStartingDeck(const Deck& deck);

    Trial& setPlayerOne(Player* player);

    Trial& setPlayerTwo(Player* player);

    ~Trial();
};

class TrialLogger {
private:
    bool active;
    std::ofstream fileOut;
    std::vector<Trial> trials;

public:
    TrialLogger();

    void addTrial(const Trial& trial);
    
    void writeTrials();
};
