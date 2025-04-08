#pragma once

#include <vector>
#include <fstream>

#include <player.hpp>
#include <deck.hpp>

namespace Logger {

struct Move {
    int roundNum;
    bool playerOne;
    Suit suit;
    Value value;
    int totalPoints;
};

struct Game {
    std::vector<Move> moves;
};

class Holder {
    std::vector<Game> gameList;

public:
    inline Holder() {}

    void addGame(const Game& game);

    void retrieveList() const;
};

class Writer {
    std::ofstream outFile;

public:
    inline Writer() {}
};

}
