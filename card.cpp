#include "card.h"
#include <stdexcept>
#include <iostream>
#include <filesystem>

Card::Card() : color(Color::WILD), value(Value::WILD), texture(std::make_shared<sf::Texture>()) {
    // Load a default "back of card" texture here
    loadTexture("C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/back.png");
}

Card::Card(Color color, Value value, const std::string& imagePath)
    : color(color), value(value), texture(std::make_shared<sf::Texture>()) {
    loadTexture(imagePath);
}

Card::Card(const Card& other)
    : color(other.color), value(other.value), texture(other.texture) {
    sprite = other.sprite;
    sprite.setTexture(*texture, true);
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        color = other.color;
        value = other.value;
        texture = other.texture;
        sprite = other.sprite;
        sprite.setTexture(*texture, true);
    }
    return *this;
}

Card::Card(Card&& other) noexcept
    : color(other.color), value(other.value), texture(std::move(other.texture)), sprite(std::move(other.sprite)) {
}

Card& Card::operator=(Card&& other) noexcept {
    if (this != &other) {
        color = other.color;
        value = other.value;
        texture = std::move(other.texture);
        sprite = std::move(other.sprite);
    }
    return *this;
}

void Card::draw(sf::RenderWindow& window, float x, float y) const {
    sf::Sprite tempSprite = sprite;
    tempSprite.setPosition(x, y);
    window.draw(tempSprite);
}

void Card::loadTexture(const std::string& imagePath) {
    if (imagePath.empty()) {
        std::cerr << "Warning: Empty image path for card " << static_cast<int>(color)
            << " " << static_cast<int>(value) << std::endl;
        // Load a default texture or leave the sprite blank
        sprite.setColor(sf::Color::White); // Make the sprite visible even without texture
        return;
    }

    if (!texture) {
        texture = std::make_shared<sf::Texture>();
    }

    if (!texture->loadFromFile(imagePath)) {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
        // Load a default texture or leave the sprite blank
        sprite.setColor(sf::Color::White); // Make the sprite visible even without texture
    }
    else {
        sprite.setTexture(*texture, true);
        sprite.setScale(0.2f, 0.2f);
    }
}