#include <iostream>

#include <2SRException.hpp>
#include <deck.hpp>
#include <player.hpp>
#include <logger.hpp>

Logger::Simulation simul {};

bool shouldEnd(Player* p1, Player* p2, const Deck& deck) {
    constexpr unsigned short endScore { 300 };

    return (p1->getScore() > endScore) || (p2->getScore() > endScore) || (deck.isEmpty());
}

bool playGame(Player* p1, Player* p2, const unsigned long long int& trialIndex) {
    int moveNum { 1 };
    Logger::Trial trial { p1, p2 };
    Deck deck {};

    while (true) {
        if (shouldEnd(p1, p2, deck))
            break;
        Logger::Move p1Move {
            moveNum++,
            true,
            deck.peekCard().getSuit(),
            deck.peekCard().getValue()
        };

        p1->takeTurn(deck.takeCard());

        p1Move.totalPoints = p1->getScore();
        trial.addMove(p1Move);

        if (shouldEnd(p1, p2, deck))
            break;
        Logger::Move p2Move {
            moveNum++,
            false,
            deck.peekCard().getSuit(),
            deck.peekCard().getValue()
        };

        p2->takeTurn(deck.takeCard());

        p2Move.totalPoints = p2->getScore();
        trial.addMove(p2Move);
    }

    simul.addTrial(trial);
    return p1->getScore() > p2->getScore();
}

int main(int argc, char* argv[]) {
try {
    if (argc != 3)
        throw CLIInputException("Unexpected arguments, need: numTrials numPlayers.");
    
    if (argv[1][0] == ' ')
        throw CLIInputException("Remove all whitespace in CLI arguments.");

    auto trials { static_cast<unsigned long long int>(std::stoull(argv[1])) };
    if (trials < 1 || trials % 1 != 0 || argv[1][0] == '-' || argv[1][0] == ' ')
        throw CLIInputException("Bad numTrials, must be { nT in N | 1 <= nT <= ULL_MAX } and without whitespace.");

    auto numPlayers { static_cast<unsigned short int>(std::stoi(argv[2])) };
    if (numPlayers < 0 || 2 < numPlayers)
        throw CLIInputException("Bad numPlayers, must be { nP in W | 0 <= nP <= 2 }.");

    Player *p1, *p2;
    
    unsigned long long int p1Wins { 0 };
    unsigned long long int trialIndex { 0 };
    while (trialIndex++ < trials) {
        p1 = createPlayer(numPlayers > 0);
        p2 = createPlayer(numPlayers > 1);

        p1Wins += playGame(p1, p2, trialIndex);
    }
    
    return 0;
} catch (const CLIInputException& cliie) {
    std::cerr << "2SR command line input error occured: " << cliie.what() << '\n';
    return -1;
} catch (const std::exception& stde) {
    std::cerr << "Standard library exception occured: " << stde.what() << '\n';
    return -2;
} catch (...) {
    std::cerr << "Unknown error occured.\n";
    return -3;
}
}
