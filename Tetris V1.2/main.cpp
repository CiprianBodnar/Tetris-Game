#include "SFML/Graphics.hpp"
#include<iostream>
#include "movent.h"
#include "Menu.h"
using namespace std;
using namespace sf;



int main()
{

	RenderWindow window(VideoMode(1024, 720), "Tetris V1.2");
	
	

	
	Texture tetrisPices,background;
	tetrisPices.loadFromFile("IMG/tiles.png");
	background.loadFromFile("IMG/p2.png");
	Sprite spriteBack(background);
	Sprite sprite(tetrisPices);
	sprite.setPosition(24, 24);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));
	sprite.setOrigin(9, 9);
	
	Vector2f windowActualSize;
	windowActualSize.x = window.getSize().x;
	windowActualSize.y = window.getSize().y;
	Menu menu(window.getSize().x ,window.getSize().y);
	
	bool ok = 1;
	int optionMenu = -1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (Event::KeyPressed == event.type)
			{
				if (event.key.code == Keyboard::Down)
					menu.MoveDown();
				if (event.key.code == Keyboard::Up)
					menu.MoveUp();
				if (event.key.code == Keyboard::Return)
				{
					if (menu.GetPressItem() == 0)
						optionMenu = 0;
				
					if (menu.GetPressItem() == 1)
						optionMenu = 1;
					if (menu.GetPressItem() == 2)
						window.close();
				}
			}
					
				
			
		}
		
		
		//OP 1
		if( optionMenu == 0)
		{
			RectangleShape jucator;
			jucator.setPosition(500, 500);
			jucator.setFillColor(Color::Blue);
			jucator.setSize(Vector2f(20, 30));
			move(sprite, windowActualSize.x, windowActualSize.y);
			window.clear(Color::White);
			window.draw(sprite);
			window.draw(jucator);
			if (ok == 1)
				moveDown(sprite);
			if (sprite.getOrigin().y + sprite.getPosition().y >500.f)
				ok = 0;
			else ok = 1;
			if (Mouse::getPosition(window).x > 500 && Mouse::getPosition(window).y > 500 && Mouse::getPosition(window).x < 520 && Mouse::getPosition(window).y < 530)
				if (Mouse::isButtonPressed(Mouse::Left))
					cout << "buton patratel apasat";
		}

		// OP2
		if (optionMenu == 1)
		{
			window.clear(Color::White);
		}

		if (optionMenu == -1)
		{
			window.draw(spriteBack);
			menu.draw(window);
		}
		
	window.display();
	}

}