#include "CardGame.h"
#include <iostream>
#include <utility>
#include<tuple>
#include<unordered_map>

GameState::GameState(Player& player1, Player& player2, Deck& FullDeck): p1(player1), p2(player2), deck(FullDeck), turn(false), cardsPlayed(0), lead(Card()), follow(Card()) {
	deck.ShuffleAndDeal(p1, p2);
	decree = deck.flipACard();
	


}

Player GameState::findWinner(Card lead, Card follow) {
	if (lead.Suit() == follow.Suit() && lead.Value() > follow.Value()) {
		if (playerLeads) {
			std::cout << "Case A\n";
			return p1;
		}
		std::cout << "Case B\n";
		return p2;
	}
	else if (lead.Suit() == follow.Suit() && lead.Value() < follow.Value()) {
		if (playerLeads) {
			playerLeads = false;
			std::cout << "Case C\n";
			return p2;
		}
		playerLeads = true;
		std::cout << "Case D\n";
		return p1;
	}
	else if (follow.Suit() == decree.Suit()) {
		if (playerLeads) {
			playerLeads = false;
			std::cout << "Case E\n";
			return p2;
		}
		playerLeads = true;
		std::cout << "Case F\n";
		return p1;

	}
	else {
		if (playerLeads) {
			std::cout << "Case G\n";
			return p1;
		}
		std::cout << "Case H\n";
		return p2;
	}

}

bool GameState::PlayerLeads() {
	return playerLeads;
}


Card& GameState::GetDecree() {
	return decree;
}

void GameState::nextTurn() {
	turn = !turn;
	return;
}

bool GameState::IsPlayable(Hand handToCheck, Card cardToCheck) {
	
	if (!turn) {
		return true;
	}
	else if (handToCheck.countSuit(lead.Suit()) == 0) {
		std::cout << "lead card is " << lead.CardName() << "and card to check is " << cardToCheck.CardName() << '\n';
		std::cout << "there are " << handToCheck.countSuit(lead.Suit()) << " " << lead.Suit() << "'s in the hand to check.\n";
		return true;
	}
	else if (cardToCheck.Suit() == lead.Suit()) {
		std::cout << "lead card is " << lead.CardName() << "and card to check is " << cardToCheck.CardName() << '\n';
		std::cout << "there are " << handToCheck.countSuit(lead.Suit()) << " " << lead.Suit() << "'s in the hand to check.\n";
		return true;
	}
	else {
		std::cout << "lead card is " << lead.CardName() << "and card to check is " << cardToCheck.CardName() << '\n';
		std::cout << "there are " << handToCheck.countSuit(lead.Suit()) << " " << lead.Suit() << "'s in the hand to check.\n";
		return false;
	}
}

Player& GameState::isTurn() {
	if ((playerLeads && cardsPlayed == 0) || !playerLeads && cardsPlayed == 1) {
		return p1;
	}
	else {
		return p2;
	}
}

void GameState::tryToPlay(int triedToPlayPosition) {
	Player& playerWithTurn = isTurn();
	Hand& playerWithTurnHand = playerWithTurn.ShowHand();
	Card& triedToPlayCard = playerWithTurnHand.ReadCard(triedToPlayPosition);
	if (IsPlayable(playerWithTurnHand, playerWithTurnHand.ReadCard(triedToPlayPosition))) {
		nextTurn();
		playerWithTurnHand.CardOut(triedToPlayPosition);
		if (turn){
			follow = triedToPlayCard;
		}
		else {
			lead = triedToPlayCard;
		}
	}
}