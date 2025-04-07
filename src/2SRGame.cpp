#include <iostream>
#include <memory>

#include <deck.hpp>
#include <player.hpp>

unsigned int trials;

bool shouldEnd(Player* p1, Player* p2, Deck& deck) {
    constexpr int endScore { 300 };

    return (p1->getScore() > endScore) || (p2->getScore() > endScore) || (deck.isEmpty());
}

bool playGame(Player* p1, Player* p2) {
    Deck deck {};

    while (true) {
        if (shouldEnd(p1, p2, deck))
            break;
        p1->takeTurn(deck.takeCard());
        
        if (shouldEnd(p1, p2, deck))
            break;
        p2->takeTurn(deck.takeCard());
    }

    return p1->getScore() > p2->getScore();
}

Player* createPlayer(bool cli) {
    return (cli ? static_cast<Player*>(new CLIPlayer {}) : static_cast<Player*>(new CPUPlayer {}));
}

int main(int argc, char* argv[]) { try { // Try/catch for entire main(...)
    if (argc != 4)
        throw "Unexpected arguments. Need: numTrials cliOne cliTwo\n";

    // CLI Arguments
    trials = std::stoi(argv[1]);
    if (trials == 0)
        throw "Trials cannot be zero.\n";

    bool cliOne { *argv[2] == '1' };
    bool cliTwo { *argv[3] == '1' };

    Player *p1, *p2;
    int p1Wins { 0 };

    unsigned int trialIndex { 0 };
    while (trialIndex++ < trials) {       
        p1 = createPlayer(cliOne);
        p2 = createPlayer(cliTwo);

        p1Wins += playGame(p1, p2);

        delete p1;
        delete p2;
    }

    std::cout << "You " << (p1Wins > trials / 2 ? "won" : "lost") << ' ' << p1Wins << " to " << trials - p1Wins << '\n';
} catch (const char e[]) {
    std::cerr << e;
    return -1;
} catch (...) {
    std::cerr << "Unknown error.\n";
    return -2;
}}
