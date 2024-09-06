#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

class Card : public sf::Sprite {
	int value;
	std::string suit;
	static sf::Texture texture;
public:
	// Make the back of a card show with nonsense values, i.e. for draw pile or computer hand
	Card();

	//Make a card with the given suit and value,  such as when initializing the deck.
	Card(std::string the_suit, int the_value);

	//define < so that .sort() method works on hands
	bool operator<(Card after) {
		return ((suit > after.Suit()) || (suit == after.Suit() && value < after.Value()));
	}

	//determine if the mouse is over the card
	bool IsHovered(sf::Vector2i mp);


	std::string Suit();
	std::string CardName();

	int Value();

	//call once to get texture set for cards
	static void LoadSheet();

	//call once per card to set the image on the sprite
	void SetCardSprite();

};




class Hand {
	std::vector<Card> cards;
	//used to track number of each suit in the hand, for example to determine which cards are playable
	std::unordered_map<std::string, int> suitCounts = {
		{"C",0},{"D",0},{"H",0},{"S",0}
	};

public:
	


	Hand(std::vector<Card> card_list);
	Hand();

	//use srand and random shuffle to shuffle a hand.
	void Shuffle();

	//place cards in hand in order, see operator< in Card class
	void Order();

	//add card to hand such as in dealing
	void CardIn(Card card);

	//remove card in ith position from hand
	void CardOut(int played_card_position);

	//give card in ith position, for example to check if it is hovered.
	Card& ReadCard(int i);
	
	int HandSize();

	//std::cout card names in hand, for debugging mostly
	void PrintHand();

	//returns number of cards of the given suit in hand, for example to determine playble cards.
	int countSuit(std::string suitcheck);
};








class Player {
	Hand hand;
	int number;
	int score;
	std::string player_name;
public:
	Player(int number=1, std::string name = "", Hand hand = Hand(), int score = 0);
	Hand& ShowHand();
	void GiveName(std::string name);
	void GiveHand(Hand new_hand);
	void GiveNumber(int i);
	int GetNumber();
	void PlayCard(int i);
	std::string GetName();
	int Score();
	
};

class Deck : public Hand {
	static const std::vector<std::string> suits;
	static const std::vector<int> values;
	const int handsize = 7;
	const int decksize = suits.size()*values.size();
public:
	int position = 0;
	//initialize the full deck
	Deck() : Hand() {

		for (size_t i = 0; i < suits.size(); ++i) {
			for (size_t j = 0; j < values.size(); ++j) {
				Card nextCard = Card(suits[i], values[j]);
				nextCard.SetCardSprite();
				CardIn(nextCard);
			}
		}
	}
	
	//take a card out of the deck and return it
	Card& flipACard() {
		Card& newCard = ReadCard(position);
		position++;
		if (position >= decksize) {
			position = 0;
		}
		std::cout << position << '\n';
		return newCard;
	}


	void ShuffleAndDeal(Player& P1, Player& P2) {
		Shuffle();
		Card card1;
		Card card2;
		for (int i = 0; i < handsize; i++) {
			P1.ShowHand().CardIn(flipACard());
			P2.ShowHand().CardIn(flipACard());
		}
		P1.ShowHand().Order();
		return;
	}
};

class GameState
{
public:

	GameState(Player& player1, Player& player2, Deck& FullDeck);

	Player findWinner();
	bool PlayerLeads();
	Card& GetDecree();
	bool IsPlayable(Hand handToCheck, Card cardToCheck);
	void nextTurn();
	Player& isTurn();
	bool tryToPlay(int triedToPlay);
	void printGameState(sf::RenderWindow& window);
	void playBestCard(Player& computerturn);


private:
	bool turn;													// turn is true if a lead card has been played this round.
	Player& p1;
	Player& p2;
	Deck& deck;
	Card decree;
	Card follow;
	Card lead;
	bool playerLeads = true;
	int cardsPlayed = 0;
	

};
