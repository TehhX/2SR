#include <sstream>

#include <2SRException.hpp>
#include <logger.hpp>

namespace Logger {

Trial::Trial(Player* const p1, Player* const p2)
: p1 { p1 }, p2 { p2 } {}

const std::vector<Move>& Trial::getMoves() const {
    return moves;
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
    for (const auto& trial : trials) {
        outFile << "RoundNum,Suit,Value,TotalPoints\n";

        for (const auto& move : trial.getMoves())
            outFile << getRow(move);

        outFile << std::endl;
    }

    outFile.close();

    if (outFile.fail())
        throw LoggerException("Could not close the file.");
}

}
