#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class Card {
public:
    enum class Color { RED, BLUE, GREEN, YELLOW, WILD };
    enum class Value { ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DRAW_TWO, REVERSE, SKIP, WILD, WILD_DRAW_FOUR, SWAP_HANDS, DISCARD_PILE_SWAP, SIXTY_NINE, AIDS, BACKSTAB, BLUE_SHIELD, CLONE, COMMUNISM, CONQUEST, CURE, DEATH, DELAYED_BLAST, DODGE, DOUBLE_SKIP, FAMINE, FUCK_THIS_PERSON_IN_PARTICULAR, FUCK_YOU, GIFT, GLASNOST, GOLD_COIN, HARVESTER_OF_SORROWS, HOLY_DEFENDER, HOT_DEATH, I_DONT_LIKE_THESE, LUCK, M_A_D, MAGIC_5, MARTYR, MYSTERY_DRAW, NECROMANCER, PENN_STATE, PING, PLAGUE, PROPHET, QUITTER, RECYCLER, REVERSE_SKIP, SPREADER, SWAP, TASTE_THE_RAINBOW, THE_CHOSEN_ONE, THE_FLOOD, VIRUS, YIN, YANG };

    Card(Color color, Value value, const std::string& imagePath);

    // Rule of five
    Card(const Card& other);
    Card& operator=(const Card& other);
    Card(Card&& other) noexcept;
    Card& operator=(Card&& other) noexcept;
    ~Card() = default;

    Color getColor() const { return color; }
    Value getValue() const { return value; }
    const sf::Sprite& getSprite() const { return sprite; }
    void draw(sf::RenderWindow& window, float x, float y) const;

    bool isField = false;
    bool isAttack = false;
    bool isDefense = false;
    bool isGlobal = false;
    bool isTechnical = false;
    bool isDirectedAttack = false;

private:
    Color color;
    Value value;
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;

    void loadTexture(const std::string& imagePath);
};