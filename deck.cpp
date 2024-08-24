#include "deck.h"
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <iostream>

Deck::Deck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
}

void Deck::initialize(const std::map<std::string, std::string>& cardImagePaths) {
    cards.clear();
    for (int i = 0; i < 4; i++) {
        Card::Color color = static_cast<Card::Color>(i);
        for (int j = 0; j < 13; j++) {
            Card::Value value = static_cast<Card::Value>(j);
            std::string imagePath = getCardImagePath(color, value, cardImagePaths);
            cards.emplace_back(color, value, imagePath);
            if (j != 0) { // Add a second card for all except 0
                cards.emplace_back(color, value, imagePath);
            }
        }
    }

    // Add Hot Death variant cards
    //for (int i = 0; i < 2; i++) {
    //    deck.emplace_back(Card::Color::WILD, Card::Value::SWAP_HANDS, cardImagePaths["SWAP_HANDS"]);
    //    deck.emplace_back(Card::Color::WILD, Card::Value::DISCARD_PILE_SWAP, cardImagePaths["DISCARD_PILE_SWAP"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::SIXTY_NINE, cardImagePaths["SIXTY_NINE"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::SIXTY_NINE, cardImagePaths["SIXTY_NINE"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::AIDS, cardImagePaths["AIDS"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::BACKSTAB, cardImagePaths["BACKSTAB"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::BLUE_SHIELD, cardImagePaths["BLUE_SHIELD"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::CLONE, cardImagePaths["CLONE"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::COMMUNISM, cardImagePaths["COMMUNISM"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::CONQUEST, cardImagePaths["CONQUEST"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::CURE, cardImagePaths["CURE"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::CURE, cardImagePaths["CURE"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::CURE, cardImagePaths["CURE"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::CURE, cardImagePaths["CURE"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::DEATH, cardImagePaths["DEATH"]);
    //    deck.emplace_back(Card::Color::WILD, Card::Value::DELAYED_BLAST, cardImagePaths["DELAYED_BLAST"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::DODGE, cardImagePaths["DODGE"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::DODGE, cardImagePaths["DODGE"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::DODGE, cardImagePaths["DODGE"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::DODGE, cardImagePaths["DODGE"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::DOUBLE_SKIP, cardImagePaths["DOUBLE_SKIP"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::DOUBLE_SKIP, cardImagePaths["DOUBLE_SKIP"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::DOUBLE_SKIP, cardImagePaths["DOUBLE_SKIP"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::DOUBLE_SKIP, cardImagePaths["DOUBLE_SKIP"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::FAMINE, cardImagePaths["FAMINE"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::FUCK_THIS_PERSON_IN_PARTICULAR, cardImagePaths["FUCK_THIS_PERSON_IN_PARTICULAR"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::FUCK_YOU, cardImagePaths["FUCK_YOU"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::GIFT, cardImagePaths["GIFT"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::GIFT, cardImagePaths["GIFT"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::GIFT, cardImagePaths["GIFT"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::GIFT, cardImagePaths["GIFT"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::GLASNOST, cardImagePaths["GLASNOST"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::GOLD_COIN, cardImagePaths["GOLD_COIN"]);
    //    deck.emplace_back(Card::Color::WILD, Card::Value::HARVESTER_OF_SORROWS, cardImagePaths["HARVESTER_OF_SORROWS"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::HOLY_DEFENDER, cardImagePaths["HOLY_DEFENDER"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::HOT_DEATH, cardImagePaths["HOT_DEATH"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::I_DONT_LIKE_THESE, cardImagePaths["I_DONT_LIKE_THESE"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::LUCK, cardImagePaths["LUCK"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::M_A_D, cardImagePaths["M_A_D"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::MAGIC_5, cardImagePaths["MAGIC_5"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::MARTYR, cardImagePaths["MARTYR"]);
    //    deck.emplace_back(Card::Color::WILD, Card::Value::MYSTERY_DRAW, cardImagePaths["MYSTERY_DRAW"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::NECROMANCER, cardImagePaths["NECROMANCER"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::PENN_STATE, cardImagePaths["PENN_STATE"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::PING, cardImagePaths["PING"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::PLAGUE, cardImagePaths["PLAGUE"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::PROPHET, cardImagePaths["PROPHET"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::QUITTER, cardImagePaths["QUITTER"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::RECYCLER, cardImagePaths["RECYCLER"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::REVERSE_SKIP, cardImagePaths["REVERSE_SKIP"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::REVERSE_SKIP, cardImagePaths["REVERSE_SKIP"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::REVERSE_SKIP, cardImagePaths["REVERSE_SKIP"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::REVERSE_SKIP, cardImagePaths["REVERSE_SKIP"]);
    //    deck.emplace_back(Card::Color::RED, Card::Value::SPREADER, cardImagePaths["SPREADER"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::SPREADER, cardImagePaths["SPREADER"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::SPREADER, cardImagePaths["SPREADER"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::SPREADER, cardImagePaths["SPREADER"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::SWAP, cardImagePaths["SWAP"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::SWAP, cardImagePaths["SWAP"]);
    //    deck.emplace_back(Card::Color::WILD, Card::Value::TASTE_THE_RAINBOW, cardImagePaths["TASTE_THE_RAINBOW"]);
    //    deck.emplace_back(Card::Color::YELLOW, Card::Value::THE_CHOSEN_ONE, cardImagePaths["THE_CHOSEN_ONE"]);
    //    deck.emplace_back(Card::Color::BLUE, Card::Value::THE_FLOOD, cardImagePaths["THE_FLOOD"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::VIRUS, cardImagePaths["VIRUS"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::YIN, cardImagePaths["YIN"]);
    //    deck.emplace_back(Card::Color::GREEN, Card::Value::YANG, cardImagePaths["YANG"]);
    //}

    // Add wild cards
    //for (int i = 0; i < 4; i++) {
    //    cards.emplace_back(Card::Color::WILD, Card::Value::WILD, cardImagePaths.at("WILD"));
    //    cards.emplace_back(Card::Color::WILD, Card::Value::WILD_DRAW_FOUR, cardImagePaths.at("WILD_DRAW_FOUR"));
    //}
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::drawCard() {
    if (isEmpty()) {
        throw std::runtime_error("Attempted to draw from an empty deck");
    }
    Card drawnCard = cards.back();
    cards.pop_back();
    return drawnCard;
}

std::string Deck::getCardImagePath(Card::Color color, Card::Value value, const std::map<std::string, std::string>& cardImagePaths) {
    std::string colorStr;
    switch (color) {
    case Card::Color::RED: colorStr = "RED"; break;
    case Card::Color::BLUE: colorStr = "BLUE"; break;
    case Card::Color::GREEN: colorStr = "GREEN"; break;
    case Card::Color::YELLOW: colorStr = "YELLOW"; break;
    case Card::Color::WILD: colorStr = "WILD"; break;
    default: colorStr = "UNKNOWN"; break;
    }

    std::string valueStr;
    switch (value) {
    case Card::Value::ZERO: valueStr = "0"; break;
    case Card::Value::ONE: valueStr = "1"; break;
    case Card::Value::TWO: valueStr = "2"; break;
    case Card::Value::THREE: valueStr = "3"; break;
    case Card::Value::FOUR: valueStr = "4"; break;
    case Card::Value::FIVE: valueStr = "5"; break;
    case Card::Value::SIX: valueStr = "6"; break;
    case Card::Value::SEVEN: valueStr = "7"; break;
    case Card::Value::EIGHT: valueStr = "8"; break;
    case Card::Value::NINE: valueStr = "9"; break;
    case Card::Value::DRAW_TWO: valueStr = "DRAW_TWO"; break;
    case Card::Value::REVERSE: valueStr = "REVERSE"; break;
    case Card::Value::SKIP: valueStr = "SKIP"; break;
    case Card::Value::WILD: valueStr = "WILD"; break;
    case Card::Value::WILD_DRAW_FOUR: valueStr = "WILD_DRAW_FOUR"; break;
    default: valueStr = "UNKNOWN"; break;
    }

    std::string key = colorStr + valueStr;
    auto it = cardImagePaths.find(key);
    if (it != cardImagePaths.end()) {
        return it->second;
    }
    else {
        std::cerr << "Warning: No image path found for card: " << key << std::endl;
        return "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/back.png"; // Default card back
    }
}