#include <cassert>
#include <iostream>

#include <player.hpp>

int Player::getMultiplier(const Card& card) const {
    int score { 0 };
    
    if (card.getValue() < Value::jack || card.getValue() != royal)
        score += static_cast<int>(card.getValue());
    else
        score += 25;
    
    if (card.getSuit() == primarySuit)
        score *= 4;
    else if (card.getSuit() == secondarySuit)
        score *= 2;
      
    return score;
}

CPUPlayer::CPUPlayer() {
    
}

void CPUPlayer::takeTurn(const Card& card) {
    score += getMultiplier(card);
    roundNum++;
}

CLIPlayer::CLIPlayer() {

}

void CLIPlayer::takeTurn(const Card& card) {
    std::cout << "Press enter to take card...";

    {
    std::string bin {};
    getline(std::cin, bin);
    } // Scope to delete bin.

    std::cout << "You got a " << card << ".\n";
    std::cout << "Your score is now " << score << " at round #" << roundNum << "\n\n";

    roundNum++;
}
