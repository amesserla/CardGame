#include "CardGame.h"

#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

////////////////////
// To set up a text box, need to use sf::Font::loadFromFile to get a font .ttf file
// Then constructors below to make buttons with custom text, or default player boxes
// 
//
// 
// Change Colors for backgrounds to look cleaner at some point, maybe add a border to the
// rectangles for buttons?
//
////////////////////


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
		case NameSlot:                                  // Eventually want to do this in
		{												// game window instead of terminal
			std::cout << "Please enter player name: ";
			std::cin >> textString;

			setText(textString);

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

