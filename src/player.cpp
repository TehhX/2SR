#include <cassert>
#include <iostream>

#include <player.hpp>

int Player::getMultiplier(const Card& card) const {
    int score { 1 };
    
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

int Player::getScore() const {
    return score;
}

CPUPlayer::CPUPlayer() {
    primarySuit = randSuit();
    secondarySuit = randSuit(primarySuit);
    royal = randValue();
}

void CPUPlayer::takeTurn(const Card& card) {
    score += getMultiplier(card);
}

CLIPlayer::CLIPlayer() {
    {
        std::cout << "Enter primary suit: ";
        std::string in;
        getline(std::cin >> std::ws, in);
        primarySuit = takeSuit(in);
    }

    {
        std::cout << "Enter secondary suit: ";
        std::string in;
        getline(std::cin >> std::ws, in);
        secondarySuit = takeSuit(in);
    }

    if (primarySuit == secondarySuit)
        throw "Primary suit cannot be equal to secondary suit.\n";

    {
        std::cout << "Enter royal: ";
        std::string in;
        getline(std::cin >> std::ws, in);
        royal = takeValue(in);
        if (!isFace(royal))
            throw "Bad royal input.\n";
    }
}

void CLIPlayer::takeTurn(const Card& card) {
    std::cout << "Press enter to take card...";
    score += getMultiplier(card);

    {
    std::string bin {};
    getline(std::cin, bin);
    } // Scope to delete bin.

    std::cout << "You got a " << card << ".\n"
              << "Your score is now " << score << "\n\n";
}
