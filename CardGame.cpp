#include "StrategicWarCardGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

const std::vector<std::string> Deck::suits = { "C", "D", "H", "S" };
const std::vector<int> Deck::values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };



int main()
{
	Deck fullDeck = Deck();
	Player human = Player();
	Player computer = Player(2);
	Card::LoadSheet();
	GameState newGame(human, computer, fullDeck);
	bool isLead = true;
	Card leadCard;
	Card followCard;
	Card DecreeCard = newGame.GetDecree();
	DecreeCard.setPosition(1300.f, 325.f);

	int countPlayedCards = 0;




	sf::RenderWindow window(sf::VideoMode(1430, 700), "Strategic War Card Game");
	sf::RectangleShape shape(sf::Vector2f(1430.f, 1000.f));
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (isLead) {
					if (newGame.PlayerLeads()) {
						for (int i = 0; i < human.ShowHand().HandSize(); i++) {
							if (human.ShowHand().ReadCard(i).IsHovered(sf::Mouse::getPosition(window))) {
								leadCard = human.ShowHand().ReadCard(i);
								leadCard.setPosition(0.f, 500.f);
								isLead = false;
								human.ShowHand().CardOut(i);
								countPlayedCards = 1;
								newGame.lead = leadCard;
								newGame.nextTurn();
								
							}
						}
					}
					else {
						for (int i = 0; i < computer.ShowHand().HandSize(); i++) {
							if (computer.ShowHand().ReadCard(i).IsHovered(sf::Mouse::getPosition(window))) {
								leadCard = computer.ShowHand().ReadCard(i);
								leadCard.setPosition(0.f, 0.f);
								isLead = false;
								computer.ShowHand().CardOut(i);
								countPlayedCards = 1;
								newGame.lead = leadCard;
								newGame.nextTurn();
							}
						}
					}
				}
				else {
					if (newGame.PlayerLeads()) {
						for (int i = 0; i < computer.ShowHand().HandSize(); i++) {
							if (computer.ShowHand().ReadCard(i).IsHovered(sf::Mouse::getPosition(window)) && newGame.IsPlayable(computer.ShowHand(),computer.ShowHand().ReadCard(i))) {
								followCard = computer.ShowHand().ReadCard(i);
								followCard.setPosition(0.f, 0.f);
								isLead = true;
								computer.ShowHand().CardOut(i);
								countPlayedCards = 2;
								newGame.nextTurn();
								
							}
						}
					}
					else {
						for (int i = 0; i < human.ShowHand().HandSize(); i++) {
							if (human.ShowHand().ReadCard(i).IsHovered(sf::Mouse::getPosition(window)) && newGame.IsPlayable(human.ShowHand(), human.ShowHand().ReadCard(i))) {
								followCard = human.ShowHand().ReadCard(i);
								followCard.setPosition(0.f, 500.f);
								isLead = true;
								human.ShowHand().CardOut(i);
								countPlayedCards = 2;
								newGame.nextTurn();
								
							}
						}
					}
				}
				
			}

		}

		if (countPlayedCards == 2) {
			std::cout << newGame.findWinner(leadCard,followCard).GetName() << " wins!\n";
			countPlayedCards = 0;
			if (human.ShowHand().HandSize() == 0) {
				std::cout << fullDeck.position << '\n';
				int i{ 0 };
				while (i < 7) {
					human.ShowHand().CardIn(fullDeck.flipACard());
					computer.ShowHand().CardIn(fullDeck.flipACard());
					i++;
				}
			}
			human.ShowHand().Order();
		}

		

		window.clear();
		window.draw(shape);

		for (int i = 0; i < human.ShowHand().HandSize(); i++) {
			Card& cardtodraw = human.ShowHand().ReadCard(i);
			cardtodraw.setPosition(200+100.f*i, 400.f);
			

			window.draw(cardtodraw);
			
		}
		for (int i = 0; i < computer.ShowHand().HandSize(); i++) {
			Card& computerToDraw = computer.ShowHand().ReadCard(i);
			computerToDraw.setPosition(200 + 100.f * i, 200.f);

			window.draw(computerToDraw);
		}

		window.draw(leadCard);
		window.draw(followCard);
		window.draw(DecreeCard);
		window.display();
	}



	return 0;

}