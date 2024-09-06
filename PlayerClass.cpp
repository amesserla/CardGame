#include "CardGame.h"
#include <iostream>

Player::Player(int pl_number, std::string name, Hand pl_hand, int score) :
	hand(pl_hand),
	number(pl_number),
	player_name(name),
	score(score) {
	if (player_name == ""){
		player_name = "Player " + std::to_string(pl_number);
	}
};

std::string Player::GetName() {
	return player_name;
}

int Player::GetNumber() {
	return number;
}

void Player::GiveHand(Hand new_hand) {
	hand = new_hand;
	return;
}

void Player::GiveName(std::string name) {
	player_name = name;
	return;
}

void Player::GiveNumber(int i) {
	number = i;
	return;
}

void Player::PlayCard(int i) {
	hand.CardOut(i);
	return;
}

Hand& Player::ShowHand() {
	return hand;
}

int Player::Score() {
	return score;
}