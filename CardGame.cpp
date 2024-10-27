#include "CardGame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

const std::vector<std::string> Deck::suits = { "C", "D", "H", "S" };
const std::vector<int> Deck::values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };


//int main()
//{
//	Deck fullDeck = Deck();
//	Player human = Player();
//	Player computer = Player(2);
//	Card::LoadSheet();
//	GameState newGame(human, computer, fullDeck);
//	bool isLead = true;
//	Card leadCard;
//	Card followCard;
//	Card DecreeCard = newGame.GetDecree();
//	DecreeCard.setPosition(1300.f, 325.f);
//
//	int countPlayedCards = 0;
//
//
//
//
//	sf::RenderWindow window(sf::VideoMode(1430, 700), "Strategic War Card Game");
//	sf::RectangleShape shape(sf::Vector2f(1430.f, 1000.f));
//	shape.setFillColor(sf::Color::Green);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//			if (event.type == sf::Event::MouseButtonPressed) {
//				std::cout << "It is " << newGame.isTurn().GetName() << " turn.\n";
//				for(int i = 0; i<newGame.isTurn().ShowHand().HandSize(); i++){
//					if (newGame.isTurn()
//						       .ShowHand()
//						       .ReadCard(i)
//						       .IsHovered(sf::Mouse::getPosition(window))) {
//						std::cout << i << '\n';
//						newGame.tryToPlay(i);
//						countPlayedCards++;
//					}
//						
//				}
//			}
//		}
//	
//
//		if (countPlayedCards == 2) {
//			std::cout << newGame.findWinner().GetName() << " wins!\n";
//			countPlayedCards = 0;
//			if (human.ShowHand().HandSize() == 0) {
//				std::cout << fullDeck.position << '\n';
//				int i{ 0 };
//				while (i < 7) {
//					human.ShowHand().CardIn(fullDeck.flipACard());
//					computer.ShowHand().CardIn(fullDeck.flipACard());
//					i++;
//				}
//			}
//			human.ShowHand().Order();
//		}
//
//
//
//		window.clear();
//		window.draw(shape);
//
//		if (newGame.turn) {
//			if (newGame.PlayerLeads()) {
//				newGame.lead.setPosition(0.f, 500.f);
//			}
//			else {
//				newGame.lead.setPosition(0.f, 200.f);
//			}
//			window.draw(newGame.lead);
//		}
//		
//
//		for (int i = 0; i < human.ShowHand().HandSize(); i++) {
//			Card& cardtodraw = human.ShowHand().ReadCard(i);
//			cardtodraw.setPosition(200 + 100.f * i, 400.f);
//
//
//			window.draw(cardtodraw);
//
//		}
//		for (int i = 0; i < computer.ShowHand().HandSize(); i++) {
//			Card& computerToDraw = computer.ShowHand().ReadCard(i);
//			computerToDraw.setPosition(200 + 100.f * i, 200.f);
//
//			window.draw(computerToDraw);
//		}
//
//		window.draw(leadCard);
//		window.draw(followCard);
//		window.draw(DecreeCard);
//		window.display();
//	}
//
//
//
//	return 0;
//
//}

int main() {

	sf::Font font;
	font.loadFromFile("../arial.ttf");
	sf::RenderWindow window(sf::VideoMode(1430, 700), "Strategic War Card Game");
	sf::RectangleShape shape(sf::Vector2f(1430.f, 1000.f));
	shape.setFillColor(sf::Color (8, 117, 25));
	std::function<void()> closeWindow = [&window](void) {window.close(); };

	sf::Text tester("Tester", font, 16);

	tester.setPosition(sf::Vector2f(100, 100));
	tester.setFillColor(sf::Color::Black);
	

	std::vector<textBox> buttonList{ textBox(1, font), textBox(2, font), textBox("Exit", font, sf::Vector2f(500.f, 500.f), closeWindow) };
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				std::cout << "Mouse Click \n";
				for (auto& button : buttonList) {
					if (button.boxType == Button && 
						button.isHovered(sf::Mouse::getPosition(window))) {
						button.onClick();
						std::cout << "Button Pressed. Did it work?\n";
					}
					else if (button.boxType == NameSlot &&
						button.isHovered(sf::Mouse::getPosition(window))) {
						std::cout << "please enter a name?:\n";
						button.onClick();
						std::cout << "printing new button textString: " << button.textString << '\n';
					}
					else {
						std::cout << button.textString << '\n';
					}
				}
			}
		}
		window.clear();
		window.draw(shape);

		window.draw(tester);

		for (textBox& button : buttonList) {
			window.draw(button);
		}
		window.display();
	}

}