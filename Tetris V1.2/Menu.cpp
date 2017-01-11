#include "Menu.h"
#include <iostream>
using namespace sf;
using namespace std;

Menu::Menu(float width,float height)
{
	if (!font.loadFromFile("fonts/Springmarch-Roman.otf"))
	{
		//handle error
	}
	menuText[0].setFillColor(sf::Color::Red);
	menuText[0].setFont(font);
	menuText[0].setString("Play");
	menuText[0].setPosition(Vector2f(width / 4, height / (MAX_OF_MENU_ITEMS+1) * 1.25));
	menuText[0].setOrigin(Vector2f(menuText[0].getOrigin().x + menuText[0].getPosition().y / 2, menuText[0].getOrigin().y));
	//cout << menuText[0].getOrigin().x << " " << menuText[0].getOrigin().y << endl;
	//cout << menuText[0].getPosition().x << " " << menuText[0].getPosition().y << endl;


	menuText[1].setFillColor(sf::Color::White);
	menuText[1].setFont(font);
	menuText[1].setString("Best score:");
	menuText[1].setPosition(Vector2f(width / 4, height / (MAX_OF_MENU_ITEMS+1) * 1.5));
	menuText[1].setOrigin(Vector2f(menuText[1].getOrigin().x + menuText[1].getPosition().y / 2, menuText[1].getOrigin().y));
	//cout << menuText[1].getOrigin().x << " " << menuText[1].getOrigin().y << endl;
	//cout << menuText[1].getPosition().x << " " << menuText[1].getPosition().y << endl;

	menuText[2].setFillColor(sf::Color::White);
	//menuText[2].setOrigin(Vector2f(width / 2, height / 2));
	menuText[2].setFont(font);
	menuText[2].setString("Iesire");
	menuText[2].setPosition(Vector2f(width / 4, height / (MAX_OF_MENU_ITEMS+1) * 1.75));
	menuText[2].setOrigin(Vector2f(menuText[2].getOrigin().x + menuText[2].getPosition().y / 2, menuText[2].getOrigin().y));
//	cout << menuText[0].getOrigin().x << " " << menuText[0].getOrigin().y << endl;
//	cout << menuText[0].getPosition().x << " " << menuText[0].getPosition().y << endl;
}


Menu::~Menu()
{
}

void Menu::draw(RenderWindow &window)
{
	for (int i=0; i < MAX_OF_MENU_ITEMS;i++)
		window.draw(menuText[i]);
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menuText[selectedItem].setFillColor(Color::White);
		selectedItem--;
		menuText[selectedItem].setFillColor(Color::Red);
		
	}
	if (selectedItem == -1)
		selectedItem = 2;
}

void Menu::MoveDown()
{
	if (selectedItem + 1 <MAX_OF_MENU_ITEMS)
	{
		menuText[selectedItem].setFillColor(Color::White);
		selectedItem++;
		menuText[selectedItem].setFillColor(Color::Red);
		if (selectedItem == MAX_OF_MENU_ITEMS)
			selectedItem = 0;
	}
	if (selectedItem == MAX_OF_MENU_ITEMS)
		selectedItem = 0;
}