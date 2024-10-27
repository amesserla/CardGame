#include "CardGame.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

textBox::textBox(std::string newText,
	sf::Font& font,
	sf::Vector2f position,
	std::function<void()> buttonThing) : sf::Drawable(),
										 boxType{ Button },
										 position{ position },
										 textString{ newText }
										 
{
	text = sf::Text();
	text.setString(textString);
	text.setFont(font);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setPosition(position + sf::Vector2f(2.5, 2.5));
	doButtonThing = buttonThing;

	backgroundSize = sf::Vector2f(text.getLocalBounds().width + 20, 
								text.getLocalBounds().height + 20);

	background = sf::RectangleShape(backgroundSize);
	background.setFillColor(sf::Color::Red);
	background.setPosition(position);




}

textBox::textBox(int i, sf::Font& font) : sf::Drawable(),
										 boxType{ NameSlot },
										 textString{ "Player "+std::to_string(i)}
{
	text = sf::Text();
	text.setString(textString);
	text.setFont(font);
	position = sf::Vector2f(50 + 200 * (i - 1), 50);
	text.setPosition(position+sf::Vector2f(2.5,2.5));
	text.setFillColor(sf::Color::Black);
	backgroundSize = sf::Vector2f(text.getLocalBounds().width + 20,
								text.getLocalBounds().height + 20);
	
	background = sf::RectangleShape(backgroundSize);
	background.setFillColor(sf::Color::White);
	background.setPosition(position);


	
}


void textBox::setText(std::string newText) {
	text.setString(newText);
}

void textBox::onClick() {
	switch (boxType) {
		case Button:
			doButtonThing();
			break;
		case NameSlot: 
		{
			std::cin >> textString;
			std::cout << "the new name is going to hopefully be: " << textString << '\n';
			setText(textString);
			std::cout << textString << '\n';
			//resize background

			break;
		}

		default:
			std::cout << "something broke. Nothing happened.";
			break;
	}
}

bool textBox::isHovered(sf::Vector2i mp) {
	return background.getGlobalBounds().contains(mp.x, mp.y);
}

