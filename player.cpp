#include "player.h"

void Player::addCard(const Card& card) {
    hand.push_back(card);
}

bool Player::playCard(size_t index, Card& playedCard) {
    if (index >= hand.size()) {
        return false;
    }
    playedCard = hand[index];
    hand.erase(hand.begin() + index);
    return true;
}