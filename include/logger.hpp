#pragma once

#include <vector>
#include <fstream>

#include <player.hpp>
#include <deck.hpp>
#include <card.hpp>

namespace Logger {

struct Move {
    int roundNum;
    bool playerOne;
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

    Player* getP1() const;
    Player* getP2() const;

    Trial& addMove(const Move& move);
};

class Simulation {
    std::ofstream outFile;
    std::vector<Trial> trials;

public:
    Simulation();

    Simulation& addTrial(const Trial& trial);

    std::string getRow(const Logger::Move& move) const;

    ~Simulation() noexcept(false);
};

}
