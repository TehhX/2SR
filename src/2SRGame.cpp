#include <iostream>
#include <memory>

#include <deck.hpp>
#include <player.hpp>

unsigned int trials;

bool playGame(Player* p1, Player* p2) {
    Deck deck {};

    constexpr int endScore { 600 };
    while (true) {
        p1->takeTurn(deck.takeCard());
        p2->takeTurn(deck.takeCard());
    }

    return p1->getScore() > p2->getScore();
}

Player* differentiatePlayer(bool cli) {
    if (cli) 
        return new CLIPlayer {};
    else
        return new CPUPlayer {};
}

int main(int argc, char* argv[]) { try { // Try/catch for entire main(...)
    if (argc != 4)
        throw "Unexpected arguments. Need: numTrials cliOne cliTwo\n";

    // CLI Arguments
    trials = std::stoi(argv[1]);
    bool cliOne { *argv[2] == '1' };
    bool cliTwo { *argv[3] == '1' };

    int p1Wins { 0 };

    if (trials == 0)
        return -1;

    Player *p1, *p2;

    unsigned int trialInd { 0 };
    while (trialInd++ < trials) {       
        p1 = differentiatePlayer(cliOne);
        p2 = differentiatePlayer(cliTwo);

        p1Wins += playGame(p1, p2);

        delete p1;
        delete p2;
    }

    std::cout << p1Wins << '\n';
} catch (const char e[]) {
    std::cerr << e;
    return -1;
} catch (...) {
    std::cerr << "Unknown error.\n";
    return -2;
}} // End of main(...) and try/catch
