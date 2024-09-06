#include "CardGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

const std::vector<std::string> Deck::suits = { "C", "D", "H", "S" };
const std::vector<int> Deck::values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };



int main()
{	
	sf::Clock clock;
	float pauseBreakLength = 2.f;
	float smallPauselength = .5;
	Deck fullDeck = Deck();
	Player human = Player();
	Player computer = Player(2);
	Card::LoadSheet();
	GameState newGame(human, computer, fullDeck);
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
				std::cout << "It is " << newGame.isTurn().GetName() << " turn.\n";
				for(int i = 0; i<newGame.isTurn().ShowHand().HandSize(); i++){
					if (newGame.isTurn()
						       .ShowHand()
						       .ReadCard(i)
						       .IsHovered(sf::Mouse::getPosition(window))) {
						std::cout << i << '\n';
						if (newGame.tryToPlay(i)) {
							std::cout << "card played \n";
							countPlayedCards++;
						}
					}
						
				}
			}
		}
		if ((countPlayedCards == 0 && not newGame.PlayerLeads()) || (countPlayedCards == 1 && newGame.PlayerLeads())) {
			newGame.playBestCard(computer);
			countPlayedCards++;
		}
		bool needPause = false;
	

		if (countPlayedCards == 2) {
			std::cout << newGame.findWinner().GetName() << " wins!\n";
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

		if (countPlayedCards == 0 && not newGame.PlayerLeads()) {
			needPause = true;
		}





		window.clear();
		window.draw(shape);

		newGame.printGameState(window);

		window.display();
		if (needPause) {
			clock.restart();
			while (clock.getElapsedTime().asSeconds() < pauseBreakLength) {}
		}
	}



	return 0;

}