#include "uno_game.h"
#include <iostream>
#include <algorithm>
#include <filesystem>

UnoGame::UnoGame() : playerTurn(true), window(sf::VideoMode(1024, 768), "Uno Game") {
    if (!font.loadFromFile("C:/Users/Aaron Scheffler/Documents/Fonts/Lato/Lato-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    loadCardImagePaths();
    initializeGraphics();
    initializeGame();
}

void UnoGame::play() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (playerTurn && event.type == sf::Event::MouseButtonPressed) {
                handlePlayerMove(event);
            }
        }

        if (!playerTurn) {
            handleComputerMove();
        }

        drawGameState();

        if (player.hasWon() || computer.hasWon()) {
            statusText.setString(player.hasWon() ? "You Win!" : "Computer Wins!");
            window.draw(statusText);
            window.display();
            sf::sleep(sf::seconds(3));
            break;
        }
    }
}

void UnoGame::initializeGame() {
    std::cout << "Game Has Started!";
    deck.initialize(cardImagePaths);
    deck.shuffle();

    for (int i = 0; i < 7; i++) {
        player.addCard(deck.drawCard());
        computer.addCard(deck.drawCard());
    }

    currentCard = deck.drawCard();
    while (currentCard.getValue() == Card::Value::WILD || currentCard.getValue() == Card::Value::WILD_DRAW_FOUR) {
        deck.shuffle();
        currentCard = deck.drawCard();
    }
}

void UnoGame::handlePlayerMove(const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    const std::vector<Card>& playerHand = player.getHand();

    for (size_t i = 0; i < playerHand.size(); i++) {
        sf::FloatRect cardBounds(50 + i * 30, 600, 100, 150);
        if (cardBounds.contains(mousePos.x, mousePos.y)) {
            if (isValidMove(playerHand[i])) {
                Card playedCard;
                if (player.playCard(i, playedCard)) {
                    currentCard = playedCard;
                    applyCardEffect(playedCard);
                    playerTurn = false;
                }
            }
            break;
        }
    }

    // Check if player clicked on the deck to draw a card
    sf::FloatRect deckBounds(800, 300, 100, 150);
    if (deckBounds.contains(mousePos.x, mousePos.y)) {
        if (!deck.isEmpty()) {
            player.addCard(deck.drawCard());
            playerTurn = false;
        }
    }
}

void UnoGame::handleComputerMove() {
    const std::vector<Card>& computerHand = computer.getHand();
    for (size_t i = 0; i < computerHand.size(); i++) {
        if (isValidMove(computerHand[i])) {
            Card playedCard;
            if (computer.playCard(i, playedCard)) {
                currentCard = playedCard;
                applyCardEffect(playedCard);
                playerTurn = true;
                return;
            }
        }
    }

    // If no valid move, draw a card
    if (!deck.isEmpty()) {
        computer.addCard(deck.drawCard());
    }
    playerTurn = true;
}

bool UnoGame::isValidMove(const Card& card) const {
    return card.getColor() == currentCard.getColor() ||
        card.getValue() == currentCard.getValue() ||
        card.getColor() == Card::Color::WILD;
}

void UnoGame::applyCardEffect(const Card& playedCard) {
    switch (playedCard.getValue()) {
    case Card::Value::SKIP:
        playerTurn = !playerTurn;
        break;
    case Card::Value::REVERSE:
        // In a two-player game, Reverse acts like Skip
        playerTurn = !playerTurn;
        break;
    case Card::Value::DRAW_TWO:
        if (playerTurn) {
            computer.addCard(deck.drawCard());
            computer.addCard(deck.drawCard());
        }
        else {
            player.addCard(deck.drawCard());
            player.addCard(deck.drawCard());
        }
        playerTurn = !playerTurn;
        break;
    case Card::Value::WILD:
    case Card::Value::WILD_DRAW_FOUR:
        if (playedCard.getValue() == Card::Value::WILD_DRAW_FOUR) {
            if (playerTurn) {
                for (int i = 0; i < 4; i++) computer.addCard(deck.drawCard());
            }
            else {
                for (int i = 0; i < 4; i++) player.addCard(deck.drawCard());
            }
        }
        // TODO: Implement color choosing logic
        break;
    default:
        break;
    }
}

void UnoGame::drawGameState() {
    window.clear();
    window.draw(backgroundSprite);

    // Draw current card
    currentCard.draw(window, 462, 309);

    // Draw player's hand
    const std::vector<Card>& playerHand = player.getHand();
    for (size_t i = 0; i < playerHand.size(); i++) {
        playerHand[i].draw(window, 50 + i * 30, 600);
    }

    // Draw computer's hand (face down)
    const std::vector<Card>& computerHand = computer.getHand();
    for (size_t i = 0; i < computerHand.size(); i++) {
        Card().draw(window, 50 + i * 30, 50);  // Draw face-down card
    }

    // Draw deck
    Card().draw(window, 800, 300);

    // Draw turn indicator
    statusText.setString(playerTurn ? "Your Turn" : "Computer's Turn");
    window.draw(statusText);

    window.display();
}

void UnoGame::loadCardImagePaths() {
    const std::string basePath = "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/";
    const std::vector<std::string> colors = { "RED", "BLUE", "GREEN", "YELLOW" };
    const std::vector<std::string> numbers = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    const std::vector<std::string> specials = { "DRAW_TWO", "REVERSE", "SKIP" };

    // Load number cards
    for (const auto& color : colors) {
        for (const auto& number : numbers) {
            std::string key = color + number;
            std::string path = basePath + color.substr(0, 1) + "_" + number + ".png";
            cardImagePaths[key] = path;
        }
    }

    // Load special cards
    for (const auto& color : colors) {
        for (const auto& special : specials) {
            std::string key = color + special;
            std::string path = basePath + color.substr(0, 1) + "_" + special + ".png";
            std::transform(path.begin(), path.end(), path.begin(), ::tolower);
            cardImagePaths[key] = path;
        }
    }

    // Load wild cards
    cardImagePaths["WILDWILD"] = basePath + "wild.png";
    cardImagePaths["WILDWILD_DRAW_FOUR"] = basePath + "wild_draw_four.png";

    // Load special Hot Death Uno cards
        // Add more card image paths here
        //{"SWAP_HANDS", "cards/swap_hands.png"},
        //{"DISCARD_PILE_SWAP", "cards/discard_pile_swap.png"},
        //{"SIXTY_NINE", "cards/69.png"},
        //{"AIDS", "cards/aids.png"},
        //{"BACKSTAB", "cards/backstab.png"},
        //{"BLUE_SHIELD", "cards/blue_shield.png"},
        //{"CLONE", "cards/clone.png"},
        //{"COMMUNISM", "cards/communism.png"},
        //{"CONQUEST", "cards/conquest.png"},
        //{"CURE", "cards/cure.png"},
        //{"DEATH", "cards/death.png"},
        //{"DELAYED_BLAST", "cards/delayed_blast.png"},
        //{"DODGE", "cards/dodge.png"},
        //{"DOUBLE_SKIP", "cards/double_skip.png"},
        //{"FAMINE", "cards/famine.png"},
        //{"FUCK_THIS_PERSON_IN_PARTICULAR", "cards/fuck_this_person_in_particular.png"},
        //{"FUCK_YOU", "cards/fuck_you.png"},
        //{"GIFT", "cards/gift.png"},
        //{"GLASNOST", "cards/glasnost.png"},
        //{"GOLD_COIN", "cards/gold_coin.png"},
        //{"HARVESTER_OF_SORROWS", "cards/harvester_of_sorrows.png"},
        //{"HOLY_DEFENDER", "cards/holy_defender.png"},
        //{"HOT_DEATH", "cards/hot_death.png"},
        //{"I_DONT_LIKE_THESE", "cards/i_dont_like_these.png"},
        //{"LUCK", "cards/luck.png"},
        //{"M_A_D", "cards/M_A_D    .png"},
        //{"MAGIC_5", "cards/magic_5.png"},
        //{"MARTYR", "cards/martyr.png"},
        //{"MYSTERY_DRAW", "cards/mystery_draw.png"},
        //{"NECROMANCER", "cards/necromancer.png"},
        //{"PENN_STATE", "cards/penn_state.png"},
        //{"PING", "cards/ping.png"},
        //{"PLAGUE", "cards/plague.png"},
        //{"PROPHET", "cards/prophet.png"},
        //{"QUITTER", "cards/quitter.png"},
        //{"RECYCLER", "cards/recycler.png"},
        //{"REVERSE_SKIP", "cards/reverse_skip.png"},
        //{"SPREADER", "cards/spreader.png"},
        //{"SWAP", "cards/swap.png"},
        //{"TASTE_THE_RAINBOW", "cards/taste_the_rainbow.png"},
        //{"THE_CHOSEN_ONE", "cards/the_chosen_one.png"},
        //{"THE_FLOOD", "cards/the_flood.png"},
        //{"VIRUS", "cards/virus.png"},
        //{"YIN", "cards/yin.png"},
        //{"YANG", "cards/yang.png"},
    for (const auto& [key, path] : cardImagePaths) {
        if (!std::filesystem::exists(path)) {
            std::cerr << "Warning: Image file does not exist: " << path << std::endl;
        }
    }
}

void UnoGame::initializeGraphics() {
    if (!backgroundTexture.loadFromFile("C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/background.jpg")) {
        std::cerr << "Failed to load background image" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(10, 10);
}