#include <sstream>

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
    trials.push_back(trial);
    totalMoves += trial.getMoveCount();
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
    outFile << "TotalMoves,AvgMoves\n";
    outFile << totalMoves << ',' << (totalMoves / static_cast<double>(trials.size())) << '\n';
    outFile << "RoundNum,Suit,Value,TotalPoints\n";

    for (const auto& trial : trials) {
        for (const auto& move : trial.getMoves())
            outFile << getRow(move);
    }

    outFile.close();

    if (outFile.fail())
        throw LoggerException("Could not close log.csv.");
}

}
