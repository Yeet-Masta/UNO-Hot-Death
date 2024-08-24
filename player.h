#pragma once
#include "card.h"
#include <vector>

class Player {
public:
    void addCard(const Card& card);
    bool playCard(size_t index, Card& playedCard);
    const std::vector<Card>& getHand() const { return hand; }
    bool hasUno() const { return hand.size() == 1; }
    bool hasWon() const { return hand.empty(); }

private:
    std::vector<Card> hand;
};