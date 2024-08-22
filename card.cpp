#include "card.h"
#include <stdexcept>

Card::Card(Color color, Value value, const std::string& imagePath)
    : color(color), value(value), texture(std::make_shared<sf::Texture>()) {
    loadTexture(imagePath);
}

Card::Card(const Card& other)
    : color(other.color), value(other.value), texture(other.texture), sprite(other.sprite) {
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        color = other.color;
        value = other.value;
        texture = other.texture;
        sprite = other.sprite;
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
    sf::Texture tempTexture;
    if (!tempTexture.loadFromFile(imagePath)) {
        throw std::runtime_error("Failed to load card image: " + imagePath);
    }
    *texture = tempTexture;
    sprite.setTexture(*texture);
    sprite.setScale(0.2f, 0.2f);
}