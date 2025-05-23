#include <iostream>

#include <2SRException.hpp>
#include <deck.hpp>
#include <player.hpp>
#include <logger.hpp>
#include <2SRDefinitions.hpp>

constexpr littleInt endScore { 300 };

bool shouldContinue(Player* player, const Deck& deck) {
    return (player->getScore() < endScore) && (!deck.isEmpty());
}

void playGame(Player* p1, Player* p2, const trialInt& trialIndex, Logger::Simulation& sim) {
    Logger::Trial trial { p1, p2 };
    Deck deck {};
    
    littleInt moveNum { 1 };

    repeat {
        if (shouldContinue(p2, deck)) {
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

        if (shouldContinue(p1, deck)) {
            Card curentCard { deck.takeCard() };
            p2->takeTurn(curentCard);

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

    sim.addTrial(trial);
}

int main(int argc, char* argv[]) {
try {

    if (argc != 4)
        throw CLIInputException("Unexpected arguments, need: numTrials numPlayers logLevel.");

    if (argv[1][0] == ' ' || argv[2][0] == ' ')
        throw CLIInputException("Remove all whitespace in CLI arguments.");

    auto trials { static_cast<trialInt>(std::stoull(argv[1])) };
    if (trials < 1 || trials % 1 != 0 || argv[1][0] == '-')
        throw CLIInputException("Bad numTrials, must be { nT in N | 1 <= nT <= ULL_MAX } and without whitespace.");

    auto numPlayers { static_cast<littleInt>(std::stoi(argv[2])) };
    if (numPlayers > 2 || numPlayers % 1 != 0 || argv[2][0] == '-')
        throw CLIInputException("Bad numPlayers, must be { nP in W | 0 <= nP <= 2 }.");
    
    auto logLevel { static_cast<littleInt>(std::stoi(argv[3])) };
    if (logLevel < 0 || logLevel > 2 || argv[3][0] == '-')
        throw CLIInputException("Bad logLevel, must be { lL in W | 0 <= lL <= 2 }");

    Player *p1, *p2;
    trialInt trialIndex { 0 };

    Logger::Simulation sim { logLevel };

    std::cout << "Beginning simulation...\n";
    while (trialIndex++ < trials) {
        p1 = createPlayer(numPlayers > 0);
        p2 = createPlayer(numPlayers > 1);

        playGame(p1, p2, trialIndex, sim);
    }

    std::cout << "Ending simulation.\n\n";

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
