#include "CardGame.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>       
#include <cstdlib> 




Hand::Hand() : cards({}) {}
Hand::Hand(std::vector<Card> card_list) : cards(card_list) {}



void Hand::CardIn(Card new_card) {
    suitCounts[new_card.Suit()]++;
    cards.push_back(new_card);
}

void Hand::CardOut(int played_card_position) {
    suitCounts[cards[played_card_position].Suit()]--;
    cards.erase(cards.begin() + played_card_position);
}

Card& Hand::ReadCard(int i) {
    return cards[i];
}

int Hand::HandSize() {
    return cards.size();
}

void Hand::Order() {
    sort(cards.begin(), cards.end());
}

void Hand::Shuffle() {
    std::srand(unsigned(std::time(0)));
    std::random_shuffle(cards.begin(), cards.end());
}
void Hand::PrintHand() {
    for (size_t i = 0; i < cards.size(); i++) {
        std::cout << cards[i].CardName() << " ";
    }
}

int Hand::countSuit(std::string suitcheck) {
    return suitCounts[suitcheck];
}