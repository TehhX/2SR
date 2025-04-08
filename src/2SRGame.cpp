#include <iostream>

#include <inputExceptions.hpp>
#include <deck.hpp>
#include <player.hpp>

bool shouldEnd(Player* p1, Player* p2, const Deck& deck) {
    constexpr unsigned short endScore { 300 };

    return (p1->getScore() > endScore) || (p2->getScore() > endScore) || (deck.isEmpty());
}

bool playGame(Player* p1, Player* p2, const unsigned long long int& trialIndex) {
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

int main(int argc, char* argv[]) {
try {
    if (argc != 3)
        throw TSRInputException("Unexpected arguments, need: numTrials numPlayers.");
    
    if (argv[1][0] == ' ')
        throw TSRInputException("Remove all whitespace in CLI arguments.");

    auto trials { static_cast<unsigned long long int>(std::stoull(argv[1])) };
    if (trials < 1 || trials % 1 != 0 || argv[1][0] == '-' || argv[1][0] == ' ')
        throw TSRInputException("Bad numTrials, must be { nT in N | 1 <= nT <= ULL_MAX } and without whitespace.");

    auto numPlayers { static_cast<unsigned short int>(std::stoi(argv[2])) };
    if (numPlayers < 0 || 2 < numPlayers)
        throw TSRInputException("Bad numPlayers, must be { nP in W | 0 <= nP <= 2 }.");

    Player *p1, *p2;
    
    unsigned long long int p1Wins { 0 };
    unsigned long long int trialIndex { 0 };
    while (trialIndex++ < trials) {
        p1 = createPlayer(numPlayers > 0);
        p2 = createPlayer(numPlayers > 1);

        p1Wins += playGame(p1, p2, trialIndex);
    }

    std::cout << "You " << (p1Wins > trials / 2 ? "won" : "lost") << ' ' << p1Wins << " to " << trials - p1Wins << '\n' <<
                 "That is a ratio of " << p1Wins / static_cast<float>(trials / 2) << " to 1.\n";
    
    return 0;
} catch (const TSRInputException& tsrie) {
    std::cerr << "2SR command line input error occured: " << tsrie.what() << '\n';
    return -1;
} catch (const std::exception& stde) {
    std::cerr << "Standard library exception occured: " << stde.what() << '\n';
    return -2;
} catch (...) {
    std::cerr << "Unknown error occured.\n";
    return -3;
}
}
