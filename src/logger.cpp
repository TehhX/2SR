#include <sstream>
#include <iostream>

#include <2SRException.hpp>
#include <logger.hpp>

namespace Logger {

Trial::Trial(Player* const p1, Player* const p2)
: p1 { p1 }, p2 { p2 } {}

const std::vector<Move>& Trial::getMoves() const {
    return moves;
}

size_t Trial::getMoveCount() const {
    return moves.size();
}

Trial& Trial::addMove(const Move& move) {
    moves.push_back(move);
    return *this;
}

Simulation::Simulation() {
    outFile.open("log.csv");

    if (outFile.fail())
        throw LoggerException("Could not open log.csv.\n");
}

Simulation& Simulation::addTrial(const Trial& trial) {
    totalMoves += trial.getMoveCount();
    
    if (trial.getMoveCount() % 2 != 0)
        ++p1Wins;

    trials.push_back(trial);

    return *this;
}

std::string Simulation::getRow(const Logger::Move& move) const {
    std::stringstream out {};

    out << move.roundNum << ',' <<
       getSuitString(move.suit) << ',' <<
       getValueString(move.value) << ',' <<
       move.totalPoints << '\n';

    return out.str();
}

Simulation::~Simulation() noexcept(false) {
    std::cout << "Writing data to log.csv...\n";

    outFile << "TotalMoves,AvgMoves,P1Wins,P1WinRatio\n" <<
               totalMoves << ',' << (totalMoves / static_cast<double>(trials.size())) << ',' << p1Wins << ',' << p1Wins / static_cast<double>(trials.size()) << '\n' <<
               "RoundNum,Suit,Value,TotalPoints\n";

    for (const auto& trial : trials) {
        for (const auto& move : trial.getMoves())
            outFile << getRow(move);
    }

    outFile.close();

    std::cout << "Finished writing to log.csv.\n";

    if (outFile.fail())
        throw LoggerException("Could not close log.csv.");
}

}
