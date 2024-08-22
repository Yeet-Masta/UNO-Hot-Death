#include "uno_game.h"
#include <algorithm>
#include <random>
#include <chrono>

UnoGame::UnoGame() {
    // Initialize the deck
    initializeDeck();
    shuffleDeck();
}

void UnoGame::play() {
    // Set up the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Uno Game");

    // Set up the game state
    std::vector<Card> playerHand, computerHand;
    dealCards(playerHand, computerHand);
    Card currentCard = discardPile.back();
    discardPile.pop_back();

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the game elements
        drawCards(window, playerHand, currentCard, 200, 400);
        drawCards(window, computerHand, currentCard, 200, 200);
        drawCard(window, currentCard, 400, 300);

        // Update the window
        window.display();
    }
}

void UnoGame::initializeDeck() {
    deck.clear();
    deck.reserve(108);  // Reserve space for all cards (adjust number if needed)

    for (int i = 0; i < 4; i++) {
        Card::Color color = static_cast<Card::Color>(i);

        // Number cards (0-9)
        for (int j = 0; j < 10; j++) {
            Card::Value value = static_cast<Card::Value>(j);
            std::string imagePath = cardImagePaths[getCardImagePath(color, value)];
            deck.emplace_back(color, value, imagePath);

            // Add a second card for 1-9
            if (j != 0) {
                deck.emplace_back(color, value, imagePath);
            }
        }

        // Action cards (DRAW_TWO, REVERSE, SKIP)
        for (Card::Value action : {Card::Value::DRAW_TWO, Card::Value::REVERSE, Card::Value::SKIP}) {
            std::string imagePath = cardImagePaths[getCardImagePath(color, action)];
            deck.emplace_back(color, action, imagePath);
            deck.emplace_back(color, action, imagePath);  // Add two of each
        }
    }
    //deck.emplace_back(Card::Color::RED, Card::Value::ZERO, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::ZERO)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::ZERO, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::ZERO)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::ZERO, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::ZERO)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::ZERO, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::ZERO)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::ONE, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::ONE)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::ONE, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::ONE)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::ONE, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::ONE)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::ONE, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::ONE)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::TWO, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::TWO)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::TWO, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::TWO)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::TWO, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::TWO)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::TWO, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::TWO)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::THREE, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::THREE)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::THREE, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::THREE)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::THREE, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::THREE)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::THREE, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::THREE)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::FOUR, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::FOUR)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::FOUR, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::FOUR)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::FOUR, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::FOUR)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::FOUR, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::FOUR)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::FIVE, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::FIVE)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::FIVE, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::FIVE)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::FIVE, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::FIVE)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::FIVE, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::FIVE)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::SIX, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::SIX)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::SIX, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::SIX)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::SIX, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::SIX)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::SIX, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::SIX)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::SEVEN, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::SEVEN)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::SEVEN, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::SEVEN)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::SEVEN, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::SEVEN)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::SEVEN, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::SEVEN)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::EIGHT, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::EIGHT)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::EIGHT, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::EIGHT)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::EIGHT, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::EIGHT)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::EIGHT, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::EIGHT)]);
    //deck.emplace_back(Card::Color::RED, Card::Value::NINE, cardImagePaths[getCardImagePath(Card::Color::RED, Card::Value::NINE)]);
    //deck.emplace_back(Card::Color::BLUE, Card::Value::NINE, cardImagePaths[getCardImagePath(Card::Color::BLUE, Card::Value::NINE)]);
    //deck.emplace_back(Card::Color::GREEN, Card::Value::NINE, cardImagePaths[getCardImagePath(Card::Color::GREEN, Card::Value::NINE)]);
    //deck.emplace_back(Card::Color::YELLOW, Card::Value::NINE, cardImagePaths[getCardImagePath(Card::Color::YELLOW, Card::Value::NINE)]);


    // Add wild cards
    for (int i = 0; i < 4; i++) {
        deck.emplace_back(Card::Color::WILD, Card::Value::WILD, cardImagePaths[getCardImagePath(Card::Color::WILD, Card::Value::WILD)]);
        deck.emplace_back(Card::Color::WILD, Card::Value::WILD_DRAW_FOUR, cardImagePaths[getCardImagePath(Card::Color::WILD, Card::Value::WILD_DRAW_FOUR)]);
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
}

std::string UnoGame::getCardImagePath(Card::Color color, Card::Value value) {
    std::string colorStr;
    switch (color) {
    case Card::Color::RED:
        colorStr = "RED";
        break;
    case Card::Color::BLUE:
        colorStr = "BLUE";
        break;
    case Card::Color::GREEN:
        colorStr = "GREEN";
        break;
    case Card::Color::YELLOW:
        colorStr = "YELLOW";
        break;
    case Card::Color::WILD:
        colorStr = "WILD";
        break;
    }

    std::string valueStr;
    switch (value) {
    case Card::Value::ZERO:
    case Card::Value::ONE:
    case Card::Value::TWO:
    case Card::Value::THREE:
    case Card::Value::FOUR:
    case Card::Value::FIVE:
    case Card::Value::SIX:
    case Card::Value::SEVEN:
    case Card::Value::EIGHT:
    case Card::Value::NINE:
        valueStr = std::to_string(static_cast<int>(value));
        break;
    case Card::Value::DRAW_TWO:
        valueStr = "DRAW_TWO";
        break;
    case Card::Value::REVERSE:
        return "REVERSE"; // No color prefix
    case Card::Value::SKIP:
        return "SKIP"; // No color prefix
    case Card::Value::WILD:
        return "WILD"; // Already handled in color switch
    case Card::Value::WILD_DRAW_FOUR:
        return "WILD_DRAW_FOUR"; // No color prefix
    //case Card::Value::SWAP_HANDS:
    //    valueStr = "SWAP_HANDS";
    //    break;
    //case Card::Value::DISCARD_PILE_SWAP:
    //    valueStr = "DISCARD_PILE_SWAP";
    //    break;
    //case Card::Value::SIXTY_NINE:
    //    valueStr = "SIXTY_NINE";
    //    break;
    //case Card::Value::AIDS:
    //    valueStr = "AIDS";
    //    break;
    //case Card::Value::BACKSTAB:
    //    valueStr = "BACKSTAB";
    //    break;
    //case Card::Value::BLUE_SHIELD:
    //    valueStr = "BLUE_SHIELD";
    //    break;
    //case Card::Value::CLONE:
    //    valueStr = "CLONE";
    //    break;
    //case Card::Value::COMMUNISM:
    //    valueStr = "COMMUNISM";
    //    break;
    //case Card::Value::CONQUEST:
    //    valueStr = "CONQUEST";
    //    break;
    //case Card::Value::CURE:
    //    valueStr = "CURE";
    //    break;
    //case Card::Value::DEATH:
    //    valueStr = "DEATH";
    //    break;
    //case Card::Value::DELAYED_BLAST:
    //    valueStr = "DELAYED_BLAST";
    //    break;
    //case Card::Value::DODGE:
    //    valueStr = "DODGE";
    //    break;
    //case Card::Value::DOUBLE_SKIP:
    //    valueStr = "DOUBLE_SKIP";
    //    break;
    //case Card::Value::FAMINE:
    //    valueStr = "FAMINE";
    //    break;
    //case Card::Value::FUCK_THIS_PERSON_IN_PARTICULAR:
    //    valueStr = "FUCK_THIS_PERSON_IN_PARTICULAR";
    //    break;
    //case Card::Value::FUCK_YOU:
    //    valueStr = "FUCK_YOU";
    //    break;
    //case Card::Value::GIFT:
    //    valueStr = "GIFT";
    //    break;
    //case Card::Value::GLASNOST:
    //    valueStr = "GLASNOST";
    //    break;
    //case Card::Value::GOLD_COIN:
    //    valueStr = "GOLD_COIN";
    //    break;
    //case Card::Value::HARVESTER_OF_SORROWS:
    //    valueStr = "HARVESTER_OF_SORROWS";
    //    break;
    //case Card::Value::HOLY_DEFENDER:
    //    valueStr = "HOLY_DEFENDER";
    //    break;
    //case Card::Value::HOT_DEATH:
    //    valueStr = "HOT_DEATH";
    //    break;
    //case Card::Value::I_DONT_LIKE_THESE:
    //    valueStr = "I_DONT_LIKE_THESE";
    //    break;
    //case Card::Value::LUCK:
    //    valueStr = "LUCK";
    //    break;
    //case Card::Value::M_A_D:
    //    valueStr = "M_A_D";
    //    break;
    //case Card::Value::MAGIC_5:
    //    valueStr = "MAGIC_5";
    //    break;
    //case Card::Value::MARTYR:
    //    valueStr = "MARTYR";
    //    break;
    //case Card::Value::MYSTERY_DRAW:
    //    valueStr = "MYSTERY_DRAW";
    //    break;
    //case Card::Value::NECROMANCER:
    //    valueStr = "NECROMANCER";
    //    break;
    //case Card::Value::PENN_STATE:
    //    valueStr = "PENN_STATE";
    //    break;
    //case Card::Value::PING:
    //    valueStr = "PING";
    //    break;
    //case Card::Value::PLAGUE:
    //    valueStr = "PLAGUE";
    //    break;
    //case Card::Value::PROPHET:
    //    valueStr = "PROPHET";
    //    break;
    //case Card::Value::QUITTER:
    //    valueStr = "QUITTER";
    //    break;
    //case Card::Value::RECYCLER:
    //    valueStr = "RECYCLER";
    //    break;
    //case Card::Value::REVERSE_SKIP:
    //    valueStr = "REVERSE_SKIP";
    //    break;
    //case Card::Value::SPREADER:
    //    valueStr = "SPREADER";
    //    break;
    //case Card::Value::SWAP:
    //    valueStr = "SWAP";
    //    break;
    //case Card::Value::TASTE_THE_RAINBOW:
    //    valueStr = "TASTE_THE_RAINBOW";
    //    break;
    //case Card::Value::THE_CHOSEN_ONE:
    //    valueStr = "THE_CHOSEN_ONE";
    //    break;
    //case Card::Value::THE_FLOOD:
    //    valueStr = "THE_FLOOD";
    //    break;
    //case Card::Value::VIRUS:
    //    valueStr = "VIRUS";
    //    break;
    //case Card::Value::YIN:
    //    valueStr = "YIN";
    //    break;
    //case Card::Value::YANG:
    //    valueStr = "YANG";
    //    break;
    // default: return "";
    }

    if (color != Card::Color::WILD && value != Card::Value::REVERSE && value != Card::Value::SKIP) {
        return colorStr + valueStr;
    }

    return "";
}

void UnoGame::shuffleDeck() {
    // Shuffle the deck
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void UnoGame::dealCards(std::vector<Card>& playerHand, std::vector<Card>& computerHand) {
    for (int i = 0; i < 7; i++) {
        if (!deck.empty()) {
            playerHand.push_back(deck.back());
            deck.pop_back();
        }
        if (!deck.empty()) {
            computerHand.push_back(deck.back());
            deck.pop_back();
        }
        if (deck.empty()) {
            // Reshuffle discard pile if deck is empty
            deck = discardPile;
            discardPile.clear();
            shuffleDeck();
        }
    }
}

void UnoGame::drawCards(sf::RenderWindow& window, const std::vector<Card>& hand, const Card& currentCard, int x, int y) {
    // Draw the player's or computer's cards
    for (size_t i = 0; i < hand.size(); i++) {
        drawCard(window, hand[i], x + i * 50, y);
    }
}

void UnoGame::drawCard(sf::RenderWindow& window, const Card& card, int x, int y) {
    card.draw(window, static_cast<float>(x), static_cast<float>(y));
}