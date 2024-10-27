#include "CardGame.h"
#include <iostream>
#include <utility>
#include<tuple>
#include<unordered_map>

GameState::GameState(Player& player1, Player& player2, Deck& FullDeck): p1(player1), p2(player2), deck(FullDeck), turn(false), lead(Card()), follow(Card()) {
	deck.ShuffleAndDeal(p1, p2);
	decree = deck.flipACard();
	decree.setPosition(1300.f, 325.f);
	


}

Player GameState::findWinner() {
	if (lead.Suit() == follow.Suit() && lead.Value() > follow.Value()) {
		if (playerLeads) {
			std::cout << "Case A\n";
			cardsPlayed = 0;
			return p1;
		}
		std::cout << "Case B\n";
		return p2;
	}
	else if (lead.Suit() == follow.Suit() && lead.Value() < follow.Value()) {
		if (playerLeads) {
			playerLeads = false;
			std::cout << "Case C\n";
			cardsPlayed = 0;
			return p2;
		}
		playerLeads = true;
		std::cout << "Case D\n";
		cardsPlayed = 0;
		return p1;
	}
	else if (follow.Suit() == decree.Suit()) {
		if (playerLeads) {
			playerLeads = false;
			std::cout << "Case E\n";
			cardsPlayed = 0;
			return p2;
		}
		playerLeads = true;
		std::cout << "Case F\n";
		cardsPlayed = 0;
		return p1;

	}
	else {
		if (playerLeads) {
			std::cout << "Case G\n";
			cardsPlayed = 0;
			return p1;
		}
		std::cout << "Case H\n";
		cardsPlayed = 0;
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
		std::cout << "no lead card. \n";
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
	if ((playerLeads && !turn) || (!playerLeads && turn)) {
		return p1;
	}
	else {
		return p2;
	}
}

bool GameState::tryToPlay(int triedToPlayPosition) {
/*	Player& playerWithTurn = isTurn();
	Hand& playerWithTurnHand = playerWithTurn.ShowHand();*/
	Card triedToPlayCard = isTurn().ShowHand().ReadCard(triedToPlayPosition);
	if (IsPlayable(isTurn().ShowHand(), triedToPlayCard)) {
		
		if (turn){
			follow = triedToPlayCard;
			if (playerLeads) {
				follow.setPosition(0.f, 150.f);
			}
			else {
				follow.setPosition(0.f, 500.f);
			}
			isTurn().ShowHand().CardOut(triedToPlayPosition);
			cardsPlayed = 2;
			nextTurn();
			return true;
		}
		else {
			follow = Card();
			lead = triedToPlayCard;
			if (playerLeads) {
				lead.setPosition(0.f, 500.f);
			}
			else {
				lead.setPosition(0.f, 150.f);
			}
			isTurn().ShowHand().CardOut(triedToPlayPosition);
			cardsPlayed = 1;
			nextTurn();
			return true;
		}
	}
	return false;
}

void GameState::printGameState(sf::RenderWindow& window) {



	for (int i = 0; i < p1.ShowHand().HandSize(); i++) {
		Card& cardtodraw = p1.ShowHand().ReadCard(i);
		cardtodraw.setPosition(200 + 100.f * i, 400.f - 5*cardtodraw.IsHovered(sf::Mouse::getPosition(window))*GameState::IsPlayable(p1.ShowHand(),cardtodraw));


		window.draw(cardtodraw);

	}
	for (int i = 0; i < p2.ShowHand().HandSize(); i++) {
		Card& computerToDraw = p2.ShowHand().ReadCard(i);
		computerToDraw.setPosition(200 + 100.f * i, 200.f);

		window.draw(computerToDraw);
	}

	window.draw(lead);
	window.draw(follow);
	window.draw(decree);
}

void GameState::playBestCard(Player& computerturn) {
	Hand& computerHand=computerturn.ShowHand();
	int bestCardPostition = -1;
	int bestVal = 0;
	int winvalue = lead.Value();
	int minvalue = 100;
	int minposition = -1;
	if (not turn)
	{
		for (int i = 0; i < computerHand.HandSize(); i++)
		{
			if (bestVal < computerHand.ReadCard(i).Value()) 
			{
				bestVal = computerHand.ReadCard(i).Value();
				bestCardPostition = i;
			}
		}
	}
	else
	{
		if (computerHand.countSuit(lead.Suit()) == 0) {
			if (computerHand.countSuit(decree.Suit()) == 0) {
				bestVal = 100;
				for (int i = 0; i < computerHand.HandSize(); i++) {
					if (bestVal > computerHand.ReadCard(i).Value()) {
						bestVal = computerHand.ReadCard(i).Value();
						bestCardPostition = i;
					}
				}

			}
			else {
				bestVal = 100;
				for (int i = 0; i < computerHand.HandSize(); i++) {
					if (computerHand.ReadCard(i).Suit() == decree.Suit() && computerHand.ReadCard(i).Value() < bestVal) {
						bestVal = computerHand.ReadCard(i).Value();
						bestCardPostition = i;
					}
				}
			}
		}
		else {

			bestVal = 100;
			for (int i = 0; i < computerHand.HandSize(); i++) {
				if (IsPlayable(computerHand, computerHand.ReadCard(i))) {
					if (computerHand.ReadCard(i).Value() > winvalue && computerHand.ReadCard(i).Value() < bestVal) {
						bestCardPostition = i;
						bestVal = computerHand.ReadCard(i).Value();
					}
					else if (computerHand.ReadCard(i).Value() < minvalue) {
						minposition = i;
						minvalue = computerHand.ReadCard(i).Value();
					}
				}
			}
		}
	}
	if (bestCardPostition != -1) {
		std::cout << "Best card is in "<<bestCardPostition << '\n';
		tryToPlay(bestCardPostition);
		return;
	}
	else {
		std::cout <<"min card is in " << minposition << '\n';
		tryToPlay(minposition);
		return;
	}
}