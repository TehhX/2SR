#include <iostream>
#include <memory>

#include <deck.hpp>
#include <player.hpp>

unsigned int trials;

bool playGame(Player& p1, Player& p2) {
    Deck deck {};

    constexpr int endScore { 600 };
    while (!(p1.getScore() < endScore || p2.getScore() < endScore || deck.isEmpty())) {
        p1.takeTurn(deck.takeCard());
        p2.takeTurn(deck.takeCard());
    }

    return p1.getScore() > p2.getScore();
}

int main(int argc, char* argv[]) {
    if (argc != 4)
        throw "Unexpected arguments. Need: numTrials cliOne cliTwo\n";

    bool cliOne { *argv[2] == '1' };
    bool cliTwo { *argv[3] == '1' };

    trials = std::stoi(argv[1]);
    int wins { 0 };

    unsigned int trialInd { 0 };
    if (trials == 0)
        return -1;

    while (trialInd++ < trials) {
        Player* p1;
        Player* p2;
        
        if (cliOne)
            p1 = new CLIPlayer {};
        else
            p1 = new CPUPlayer {};
        
        if (cliTwo)
            p2 = new CLIPlayer {};
        else
            p2 = new CPUPlayer {};

        wins += playGame(*p1, *p2);

        delete p1;
        delete p2;
    }

    std::cout << wins << '\n';
}