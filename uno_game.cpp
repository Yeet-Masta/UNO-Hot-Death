#include "uno_game.h"
#include <algorithm>
#include <chrono>
#include <iostream>

UnoGame::UnoGame() : playerTurn(true), cardBackPath("C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/back.png") {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Uno Game");

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);

    initializeDeck();
    shuffleDeck();

    if (cardBackPath.empty()) {
        std::cerr << "Warning: Card back path is empty" << std::endl;
        cardBackPath = "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/back.png";
    }

    if (!font.loadFromFile("C:/Users/Aaron Scheffler/Documents/Fonts/Lato/Lato-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
}

void UnoGame::play() {
    std::vector<Card> playerHand, computerHand;
    dealCards(playerHand, computerHand);

    currentCard = drawInitialCard();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (playerTurn && event.type == sf::Event::MouseButtonPressed) {
                handlePlayerMove(event, playerHand);
            }
        }

        if (!playerTurn) {
            handleComputerMove(computerHand);
            playerTurn = true;
        }

        window->clear(sf::Color::Green);
        drawGameState(playerHand, computerHand);
        window->display();

        if (isGameOver(playerHand, computerHand)) {
            displayWinner(playerHand.empty());
            sf::sleep(sf::seconds(3));
            break;
        }
    }
}

void UnoGame::handlePlayerMove(const sf::Event& event, std::vector<Card>& playerHand) {
    if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
        return;
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Check if the player clicked on the deck to draw a card
    sf::FloatRect deckBounds(window->getSize().x / 2 + 100, window->getSize().y / 2 - 75, 100, 150);
    if (deckBounds.contains(mousePosF)) {
        drawCardFromDeck(playerHand);
        playerTurn = false;
        return;
    }

    // Check if the player clicked on a card in their hand
    for (size_t i = 0; i < playerHand.size(); ++i) {
        sf::FloatRect cardBounds(200 + i * 50, 800, 100, 150);
        if (cardBounds.contains(mousePosF)) {
            if (isValidMove(playerHand[i])) {
                currentCard = playerHand[i];
                playerHand.erase(playerHand.begin() + i);
                discardPile.push_back(currentCard);
                applyCardEffect(currentCard, playerHand);
                playerTurn = false;

                // Check for Uno condition
                if (playerHand.size() == 1) {
                    // You might want to add some visual or audio cue here for "Uno!"
                    std::cout << "Uno!" << std::endl;
                }

                return;
            }
            else {
                // Provide feedback that the move is invalid
                std::cout << "Invalid move. Try another card or draw from the deck." << std::endl;
                return;
            }
        }
    }
}

void UnoGame::handleComputerMove(std::vector<Card>& computerHand) {
    for (size_t i = 0; i < computerHand.size(); ++i) {
        if (isValidMove(computerHand[i])) {
            currentCard = computerHand[i];
            computerHand.erase(computerHand.begin() + i);
            return;
        }
    }

    // If no valid move, draw a card
    drawCardFromDeck(computerHand);
}

bool UnoGame::isValidMove(const Card& playedCard) const {
    return playedCard.getColor() == currentCard.getColor() ||
        playedCard.getValue() == currentCard.getValue() ||
        playedCard.getColor() == Card::Color::WILD;
}

void UnoGame::drawCardFromDeck(std::vector<Card>& hand) {
    if (!deck.empty()) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
    else if (!discardPile.empty()) {
        deck = discardPile;
        discardPile.clear();
        shuffleDeck();
        hand.push_back(deck.back());
        deck.pop_back();
    }
}

bool UnoGame::isGameOver(const std::vector<Card>& playerHand, const std::vector<Card>& computerHand) const {
    return playerHand.empty() || computerHand.empty();
}

void UnoGame::displayWinner(bool playerWon) const {
    sf::Text winnerText;
    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setFillColor(sf::Color::Black);
    winnerText.setString(playerWon ? "You Win!" : "Computer Wins!");
    winnerText.setPosition(window->getSize().x / 2 - winnerText.getGlobalBounds().width / 2,
        window->getSize().y / 2 - winnerText.getGlobalBounds().height / 2);
    window->clear(sf::Color::White);
    window->draw(winnerText);
    window->display();
}

void UnoGame::drawGameState(const std::vector<Card>& playerHand, const std::vector<Card>& computerHand) {
    drawCards(playerHand, 200, 800, true);
    drawCards(computerHand, 200, 100, false);
    drawCard(currentCard, window->getSize().x / 2 - 50, window->getSize().y / 2 - 75);
    drawCard(Card(Card::Color::WILD, Card::Value::WILD, cardImagePaths["CARD_BACK"]), window->getSize().x / 2 + 100, window->getSize().y / 2 - 75);

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(30);
    turnText.setFillColor(sf::Color::Black);
    turnText.setString(playerTurn ? "Your Turn" : "Computer's Turn");
    turnText.setPosition(20, 20);
    window->draw(turnText);
}

Card UnoGame::drawInitialCard() {
    while (!deck.empty()) {
        Card card = deck.back();
        deck.pop_back();
        if (card.getValue() <= Card::Value::NINE) {
            return card;
        }
        discardPile.push_back(card);
    }
    // If we've gone through all cards without finding a number card, shuffle and try again
    shuffleDeck();
    return drawInitialCard();
}

void UnoGame::initializeDeck() {
    deck.clear();
    deck.reserve(108);  // Reserve space for all cards (adjust number if needed)

    for (int i = 0; i < 4; i++) {
        Card::Color color = static_cast<Card::Color>(i);

        // Number cards (0-9)
        for (int j = 0; j < 10; j++) {
            Card::Value value = static_cast<Card::Value>(j);
            std::string key = getCardImagePath(color, value);
            if (!key.empty()) {
                std::string imagePath = cardImagePaths[key];
                if (imagePath.empty()) {
                    std::cerr << "Warning: Empty image path for key: " << key << std::endl;
                    // You might want to use a default image path here
                    imagePath = "path/to/default/card/image.png";
                }
                deck.emplace_back(color, value, imagePath);

                if (j != 0) {
                    deck.emplace_back(color, value, imagePath);
                }
            }
        }

        // Action cards (DRAW_TWO, REVERSE, SKIP)
        for (Card::Value action : {Card::Value::DRAW_TWO, Card::Value::REVERSE, Card::Value::SKIP}) {
            std::string key = getCardImagePath(color, action);
            if (!key.empty()) {
                std::string imagePath = cardImagePaths[key];
                std::cout << "Adding action card: " << key << " -> " << imagePath << std::endl;
                deck.emplace_back(color, action, imagePath);
                std::cout << "Adding second action card: " << key << " -> " << imagePath << std::endl;
                deck.emplace_back(color, action, imagePath);
            }
        }
    }

    // Add wild cards
    for (int i = 0; i < 4; i++) {
        std::string wildKey = getCardImagePath(Card::Color::WILD, Card::Value::WILD);
        std::string wildDrawFourKey = getCardImagePath(Card::Color::WILD, Card::Value::WILD_DRAW_FOUR);

        if (!wildKey.empty()) {
            std::string wildPath = cardImagePaths[wildKey];
            std::cout << "Adding wild card: " << wildKey << " -> " << wildPath << std::endl;
            deck.emplace_back(Card::Color::WILD, Card::Value::WILD, wildPath);
        }

        if (!wildDrawFourKey.empty()) {
            std::string wildDrawFourPath = cardImagePaths[wildDrawFourKey];
            std::cout << "Adding wild draw four: " << wildDrawFourKey << " -> " << wildDrawFourPath << std::endl;
            deck.emplace_back(Card::Color::WILD, Card::Value::WILD_DRAW_FOUR, wildDrawFourPath);
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
    if (cardImagePaths.find("CARD_BACK") == cardImagePaths.end() || cardImagePaths["CARD_BACK"].empty()) {
        std::cerr << "Warning: CARD_BACK image path is not set or empty" << std::endl;
        cardImagePaths["CARD_BACK"] = "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/back.png";
    }
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
    default:
        std::cout << "Warning: Unknown color: " << static_cast<int>(color) << std::endl;
        return "";
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
        valueStr = "REVERSE"; 
        break;
    case Card::Value::SKIP: 
        valueStr = "SKIP"; 
        break;
    case Card::Value::WILD: 
        valueStr = "WILD"; 
        break;
    case Card::Value::WILD_DRAW_FOUR: 
        valueStr = "WILD_DRAW_FOUR"; 
        break;
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
    default:
        std::cout << "Warning: Unknown value: " << static_cast<int>(value) << std::endl;
        return "";
    }

    std::string key = colorStr + valueStr;
    if (cardImagePaths.find(key) == cardImagePaths.end()) {
        std::cerr << "Warning: No image path found for key: " << key << std::endl;
        return "";
    }
    if (cardImagePaths[key].empty()) {
        std::cerr << "Warning: Empty image path for key: " << key << std::endl;
        return "";
    }
    return key;
}

void UnoGame::shuffleDeck() {
    // Shuffle the deck
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void UnoGame::dealCards(std::vector<Card>& playerHand, std::vector<Card>& computerHand) {
    playerHand.clear();
    computerHand.clear();

    for (int i = 0; i < 7 && !deck.empty(); ++i) {
        playerHand.push_back(deck.back());
        deck.pop_back();

        if (!deck.empty()) {
            computerHand.push_back(deck.back());
            deck.pop_back();
        }
    }

    if (playerHand.empty() || computerHand.empty()) {
        std::cout << "Warning: Not enough cards to deal. Player: " << playerHand.size()
            << ", Computer: " << computerHand.size() << std::endl;
    }
}

void UnoGame::drawCards(const std::vector<Card>& hand, float x, float y, bool faceUp) {
    for (size_t i = 0; i < hand.size(); ++i) {
        if (faceUp) {
            drawCard(hand[i], x + i * 50, y);
        }
        else {
            drawCard(Card(Card::Color::WILD, Card::Value::WILD, cardImagePaths["CARD_BACK"]), x + i * 50, y);
        }
    }
}

void UnoGame::drawCard(const Card& card, float x, float y) {
    card.draw(*window, x, y);
}

void UnoGame::applyCardEffect(const Card& playedCard, std::vector<Card>& opponentHand) {
    switch (playedCard.getValue()) {
    case Card::Value::SKIP:
        std::cout << "Skip effect applied. ";
        if (playerTurn) {
            std::cout << "Computer's turn is skipped!" << std::endl;
        }
        else {
            std::cout << "Your turn is skipped!" << std::endl;
        }
        // In a two-player game, skipping the opponent's turn is equivalent to playing again
        playerTurn = !playerTurn;
        break;

    case Card::Value::REVERSE:
        std::cout << "Reverse effect applied. ";
        if (playerTurn) {
            std::cout << "It's your turn again!" << std::endl;
        }
        else {
            std::cout << "Computer plays again!" << std::endl;
        }
        // In a two-player game, Reverse acts like Skip
        playerTurn = !playerTurn;
        break;

    case Card::Value::DRAW_TWO:
        std::cout << "Draw Two effect applied. ";
        if (playerTurn) {
            std::cout << "Computer draws 2 cards!" << std::endl;
        }
        else {
            std::cout << "You draw 2 cards!" << std::endl;
        }
        for (int i = 0; i < 2; ++i) {
            drawCardFromDeck(opponentHand);
        }
        // The next player's turn is skipped
        playerTurn = !playerTurn;
        break;

    case Card::Value::WILD:
        chooseWildCardColor();
        break;

    case Card::Value::WILD_DRAW_FOUR:
        std::cout << "Wild Draw Four effect applied. ";
        if (playerTurn) {
            std::cout << "Computer draws 4 cards!" << std::endl;
        }
        else {
            std::cout << "You draw 4 cards!" << std::endl;
        }
        for (int i = 0; i < 4; ++i) {
            drawCardFromDeck(opponentHand);
        }
        chooseWildCardColor();
        // The next player's turn is skipped
        playerTurn = !playerTurn;
        break;

    default:
        // For number cards, no special effect is applied
        playerTurn = !playerTurn;
        break;
    }
}

// Helper function to choose a color for Wild cards
void UnoGame::chooseWildCardColor() {
    if (playerTurn) {
        // If it's the player's turn, prompt for color choice
        std::cout << "Choose a color (R)ed, (B)lue, (G)reen, (Y)ellow: ";
        char colorChoice;
        std::cin >> colorChoice;

        switch (std::toupper(colorChoice)) {
        case 'R':
            currentCard = Card(Card::Color::RED, Card::Value::WILD, cardImagePaths["WILD"]);
            break;
        case 'B':
            currentCard = Card(Card::Color::BLUE, Card::Value::WILD, cardImagePaths["WILD"]);
            break;
        case 'G':
            currentCard = Card(Card::Color::GREEN, Card::Value::WILD, cardImagePaths["WILD"]);
            break;
        case 'Y':
            currentCard = Card(Card::Color::YELLOW, Card::Value::WILD, cardImagePaths["WILD"]);
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Red." << std::endl;
            currentCard = Card(Card::Color::RED, Card::Value::WILD, cardImagePaths["WILD"]);
        }
    }
    else {
        // If it's the computer's turn, randomly choose a color
        Card::Color colors[] = { Card::Color::RED, Card::Color::BLUE, Card::Color::GREEN, Card::Color::YELLOW };
        Card::Color chosenColor = colors[rand() % 4];
        currentCard = Card(chosenColor, Card::Value::WILD, cardImagePaths["WILD"]);
        std::cout << "Computer chooses " << getColorName(chosenColor) << std::endl;
    }
}

// Helper function to get color name as string
std::string UnoGame::getColorName(Card::Color color) {
    switch (color) {
    case Card::Color::RED: return "Red";
    case Card::Color::BLUE: return "Blue";
    case Card::Color::GREEN: return "Green";
    case Card::Color::YELLOW: return "Yellow";
    default: return "Unknown";
    }
}