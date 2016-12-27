#pragma once
#include "SFML\Graphics.hpp"
#include<iostream>
using namespace sf;
#define MAX_OF_MENU_ITEMS 3
class Menu
{
public:
	Menu(float width,float height);
	~Menu();

	void draw(RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressItem()
	{
		return selectedItem;
	}
private:
	int selectedItem = 0;
	Font font;
	Text menuText[MAX_OF_MENU_ITEMS];
};

