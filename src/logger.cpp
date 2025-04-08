#include <2SRException.hpp>
#include <logger.hpp>

namespace Logger {

Trial::Trial(Player* const p1, Player* const p2)
: p1 { p1 }, p2 { p2 } {}

const Move& Trial::getMove(int index) const {
    return moves[index];
}

Player* Trial::getP1() const {
    return p1;
}

Player* Trial::getP2() const {
    return p2;
}

Trial& Trial::addMove(const Move& move) {
    moves.push_back(move);
    return *this;
}

Trial::~Trial() {
    delete p1;
    delete p2;
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

Simulation::~Simulation() noexcept(false) {
    outFile.close();

    if (outFile.fail())
        throw LoggerException("Could not close the file.");
}

}
