#pragma once

#include <vector>
#include <fstream>

#include <2SRDefinitions.hpp>
#include <player.hpp>
#include <deck.hpp>
#include <card.hpp>

namespace Logger {

struct Move {
    int roundNum;
    Suit suit;
    Value value;
    int totalPoints;
};

class Trial {
    std::vector<Move> moves;
    Player* const p1;
    Player* const p2;

public:
    Trial(Player* const p1, Player* const p2);

    const std::vector<Move>& getMoves() const;

    size_t getMoveCount() const;

    Trial& addMove(const Move& move);
};

class Simulation {
    const littleInt logLevel;

    std::ofstream outFile;

    std::vector<Trial> trials;
    trialInt totalMoves { 0 };
    trialInt p1Wins { 0 };
    trialInt firstMovePoints { 0 };

public:
    Simulation(littleInt logLevel);

    Simulation& addTrial(const Trial& trial);

    std::string getRow(const Logger::Move& move) const;

    trialFloat perTrial(trialInt total) const;

    // Destructor will also write and close the file
    ~Simulation() noexcept(false);
};

}
