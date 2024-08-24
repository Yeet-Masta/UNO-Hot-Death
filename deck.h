#pragma once
#include "card.h"
#include <vector>
#include <map>
#include <random>

class Deck {
public:
    Deck();
    void initialize(const std::map<std::string, std::string>& cardImagePaths);
    void shuffle();
    Card drawCard();
    bool isEmpty() const { return cards.empty(); }

private:
    std::vector<Card> cards;
    std::mt19937 rng;

    std::string getCardImagePath(Card::Color color, Card::Value value, const std::map<std::string, std::string>& cardImagePaths);
};