#include "StrategicWarCardGame.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>       
#include <cstdlib> 
#include <SFML/Graphics.hpp>


Card::Card(std::string the_suit, int the_value) : suit(the_suit), value(the_value) {}
Card::Card() : suit("whoops"), value(0) {}
sf::Texture Card::texture;


void Card::LoadSheet() {
    texture.loadFromFile("C:\\Users\\amess\\Desktop\\realDeck.png");
}

std::string Card::Suit() {
    return suit;
}

int Card::Value() {
    return value;
}


std::string Card::CardName() {
    if (1 < value && value < 11) {
        return std::to_string(value) + suit;
    }
    else {
        switch (value) {
            case 11:
                return "J" + suit;
            case 12:
                return "Q" + suit;
            case 13:
                return "K" + suit;
            case 1:
                return "A" + suit;

        }
    }
}



void Card::SetCardSprite() {
    int xpos, ypos;
    int flag = 0;
    int cardHeight = 551;
    int cardWidth = 395;
    sf::Vector2<int> CardSize = sf::Vector2<int>(cardWidth, cardHeight);
    if (suit == "H") { ypos = 1654; }
    else if (suit == "S") { ypos = 2206; }
    else if (suit == "D") { ypos = 1102; }
    else if (suit == "C") { ypos = 550; }
    else { ypos = 0; xpos = 0; flag = 1; }
    if (flag == 0 && value < 14 && value >= 1) {
        xpos = std::floor(393.5 * (value - 1));                           // This is not ideal, but I don't know why the width of 395 is not the amount to shift by,
    }                                                                     // I don't know how to fix the drawing to make it better, but it works.
    else { xpos = 0; ypos = 0; }

    sf::Vector2<int> cardLocation = sf::Vector2<int>(xpos, ypos);
    sf::Rect<int> CardRect = sf::Rect<int>(cardLocation, CardSize);




    setTexture(texture);
    setTextureRect(CardRect);
    scale(.25f, .25f);
}

bool Card::IsHovered(sf::Vector2i mp) {
    return getGlobalBounds().contains(mp.x, mp.y);
}

