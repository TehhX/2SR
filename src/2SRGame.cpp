#include <iostream>

#include <deck.hpp>
#include <player.hpp>

bool moreThanOneTrial { false };
constexpr unsigned int trials { 1'000'000 };

bool cliOne;
bool cliTwo;

bool playGame(Player& playerOne, Player& playerTwo) {
    
}

int main(int argc, char* argv[]) {
    if (argc != 3)
        throw "Unexpected arguments. Need to know if player one is real, and if player two is real i.e. 1 0.\n";

    cliOne = argv[1];
    cliTwo = argv[2];

    if (cliOne + cliTwo == 0) // Both CPU players
        moreThanOneTrial = true;

    int trialInd { 0 };
    if (trials == 0)
        return;

    while (trialInd++ < trials) {

    }
}