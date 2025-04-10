#include <iostream>

#include <2SRException.hpp>
#include <deck.hpp>
#include <player.hpp>
#include <logger.hpp>
#include <2SRDefinitions.hpp>

Logger::Simulation simul {};

bool shouldContinue(Player* p1, Player* p2, const Deck& deck) {
    constexpr unsigned short endScore { 300 };

    return (p1->getScore() < endScore) && (p2->getScore() < endScore) && (!deck.isEmpty());
}

void playGame(Player* p1, Player* p2, const trialInt& trialIndex) {
    Logger::Trial trial { p1, p2 };
    Deck deck {};
    
    int moveNum { 1 };
    repeat {
        if (shouldContinue(p1, p2, deck)) {
            Card currentCard { deck.takeCard() };
            p1->takeTurn(currentCard);
    
            trial.addMove({
                moveNum++,
                currentCard.getSuit(),
                currentCard.getValue(),
                p1->getScore()
            });
        }
        else
            break;

        if (shouldContinue(p1, p2, deck)) {
            Card curentCard { deck.takeCard() };
            p1->takeTurn(curentCard);

            trial.addMove({
                moveNum++,
                curentCard.getSuit(),
                curentCard.getValue(),
                p2->getScore()
            });
        }
        else
            break;
    }

    simul.addTrial(trial);
}

int main(int argc, char* argv[]) {
try {

    if (argc != 3)
        throw CLIInputException("Unexpected arguments, need: numTrials numPlayers.");

    if (argv[1][0] == ' ' || argv[2][0] == ' ')
        throw CLIInputException("Remove all whitespace in CLI arguments.");

    auto trials { static_cast<trialInt>(std::stoull(argv[1])) };
    if (trials < 1 || trials % 1 != 0 || argv[1][0] == '-')
        throw CLIInputException("Bad numTrials, must be { nT in N | 1 <= nT <= ULL_MAX } and without whitespace.");

    auto numPlayers { static_cast<unsigned short>(std::stoi(argv[2])) };
    if (numPlayers > 2 || numPlayers % 1 != 0 || argv[2][0] == '-')
        throw CLIInputException("Bad numPlayers, must be { nP in W | 0 <= nP <= 2 }.");

    Player *p1, *p2;
    trialInt trialIndex { 0 };
    while (trialIndex++ < trials) {
        p1 = createPlayer(numPlayers > 0);
        p2 = createPlayer(numPlayers > 1);

        playGame(p1, p2, trialIndex);
    }

    delete p1;
    delete p2;
    
    return 0;

} catch (const CLIInputException& cliie) {
    std::cerr << "Command line input error occured: " << cliie.what() << '\n';
    return -1;
} catch (const LoggerException& le) {
    std::cerr << "Logger error occured: " << le.what() << '\n';
    return -2;
} catch (const CardConversionException& cce) {
    std::cerr << "Card conversion error occured: " << cce.what() << '\n';
    return -3;
} catch (const TSRException& tsre) {
    std::cerr << "Miscellanious gameplay error occured: " << tsre.what() << '\n';
    return -4;
} catch (const std::exception& stde) {
    std::cerr << "Standard library exception occured: " << stde.what() << '\n';
    return -5;
} catch (...) {
    std::cerr << "Unknown error occured.\n";
    return -6;
}
}
