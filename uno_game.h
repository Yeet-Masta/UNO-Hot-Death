#pragma once

#include "card.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class UnoGame {
public:
    UnoGame();
    void play();

private:
    std::vector<Card> deck, discardPile;
    std::map<std::string, std::string> cardImagePaths = {
        {"RED0", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_0.png"},
        {"RED1", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_1.png"},
        {"RED2", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_2.png"},
        {"RED3", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_3.png"},
        {"RED4", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_4.png"},
        {"RED5", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_5.png"},
        {"RED6", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_6.png"},
        {"RED7", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_7.png"},
        {"RED8", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_8.png"},
        {"RED9", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/red_9.png"},
        {"BLUE0", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_0.png"},
        {"BLUE1", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_1.png"},
        {"BLUE2", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_2.png"},
        {"BLUE3", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_3.png"},
        {"BLUE4", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_4.png"},
        {"BLUE5", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_5.png"},
        {"BLUE6", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_6.png"},
        {"BLUE7", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_7.png"},
        {"BLUE8", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_8.png"},
        {"BLUE9", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/blue_9.png"},
        {"YELLOW0", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_0.png"},
        {"YELLOW1", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_1.png"},
        {"YELLOW2", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_2.png"},
        {"YELLOW3", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_3.png"},
        {"YELLOW4", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_4.png"},
        {"YELLOW5", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_5.png"},
        {"YELLOW6", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_6.png"},
        {"YELLOW7", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_7.png"},
        {"YELLOW8", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_8.png"},
        {"YELLOW9", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/yellow_9.png"},
        {"GREEN0", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_0.png"},
        {"GREEN1", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_1.png"},
        {"GREEN2", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_2.png"},
        {"GREEN3", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_3.png"},
        {"GREEN4", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_4.png"},
        {"GREEN5", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_5.png"},
        {"GREEN6", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_6.png"},
        {"GREEN7", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_7.png"},    
        {"GREEN8", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_8.png"},
        {"GREEN9", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/green_9.png"},
        {"DRAW_TWO", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/r_draw2.png"},
        //{"REDDRAW_TWO", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/r_draw2.png"},
        //{"BLUEDRAW_TWO", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/b_draw2.png"},
        //{"YELLOWDRAW_TWO", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/y_draw2.png"},
        //{"GREENDRAW_TWO", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/g_draw2.png"},
        {"REVERSE", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/revse.png"},
        {"SKIP", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/skip.png"},
        // Add more card image paths here
        {"WILDWILD", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/wild.png"},
        {"WILDWILD_DRAW_FOUR", "C:/Users/Aaron Scheffler/Desktop/UNO Hot Death/cards/wild_draw_four.png"},
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
        //{"YANG", "cards/yang.png"}
    };

    void initializeDeck();
    std::string getCardImagePath(Card::Color color, Card::Value value);
    void shuffleDeck();
    void dealCards(std::vector<Card>& playerHand, std::vector<Card>& computerHand);
    void drawCards(sf::RenderWindow& window, const std::vector<Card>& hand, const Card& currentCard, int x, int y);
    void drawCard(sf::RenderWindow& window, const Card& card, int x, int y);
};