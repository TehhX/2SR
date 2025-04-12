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

Simulation::Simulation(littleInt logLevel)
: logLevel { logLevel } {
    outFile.open("log.csv");

    if (outFile.fail())
        throw LoggerException("Could not open log.csv.\n");
}

Simulation& Simulation::addTrial(const Trial& trial) {
    totalMoves += trial.getMoveCount();
    
    if (trial.getMoveCount() % 2 != 0)
        ++p1Wins;

    firstMovePoints += trial.getMoves()[0].totalPoints;

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

trialFloat Simulation::perTrial(trialInt total) const {
    return total / static_cast<trialFloat>(trials.size());
}

Simulation::~Simulation() noexcept(false) {
    std::cout << "Writing data to log.csv...\n";

    if (logLevel > 0)
        outFile << "TotalMoves,AvgMoves,P1Wins,P1WinRatio,TotalFirstMoveValue,AvgFirstMoveValue\n" <<
            totalMoves << ',' << perTrial(totalMoves) << ',' << p1Wins << ',' << perTrial(p1Wins) << ',' << firstMovePoints << ',' << perTrial(firstMovePoints) << '\n';
    if (logLevel > 1) {
        outFile << "\nRoundNum,Suit,Value,TotalPoints\n";
        for (const auto& trial : trials) {
            for (const auto& move : trial.getMoves())
                outFile << getRow(move);
        }
    }

    outFile.close();

    if (outFile.fail())
        throw LoggerException("Could not close log.csv.");
    
    std::cout << "Finished writing to log.csv.\n";
}

}
