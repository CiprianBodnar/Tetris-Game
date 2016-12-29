
#include <SFML\Graphics.hpp>
#include<iostream>
#include "movent.h"
#include "Menu.h"
#include "PartOf.h"

#include <ctime>
#include <cstdlib>
#include <sstream>



using namespace std;
using namespace sf;
int main()
{
	//Setarile ferestrei
	RenderWindow window(VideoMode(1024, 720), "Tetris V1.2");
	PartOf part;
	//window.setFramerateLimit(30);
	Vector2f windowActualSize;
	windowActualSize.x = (float)window.getSize().x;
	windowActualSize.y = (float)window.getSize().y;

	// Incarc iaginiile
	Texture tetrisPices, background;
	tetrisPices.loadFromFile("IMG/tiles.png");
	background.loadFromFile("IMG/p3.png");
	// Background si fiecare patratel
	Sprite spriteBack(background);
	Sprite blue(tetrisPices), red(tetrisPices), green(tetrisPices), yellow(tetrisPices);
	Sprite Form[5][5] = { blue };
	// Delimitez fiecare patratel din imagine "mama"
	blue.setTextureRect(IntRect(0, 0, 18, 18));
	red.setTextureRect(IntRect(18, 0, 18, 18));
	green.setTextureRect(IntRect(36, 0, 18, 18));
	yellow.setTextureRect(IntRect(54, 0, 18, 18));


	Menu menu(window.getSize().x, window.getSize().y);


	bool ok = 1;
	int optionMenu = -1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			{
				PartOf p = part;
				part.move(1, 0);
				
				/*if (map.isCollision(part))
					part = p;*/
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			{
				PartOf p = part;
				part.move(-1, 0);
				/*	if (map.isCollision(part))
						part = p;*/
			}
			/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
			{
				while (!map.isCollision(part))
				{
					part.move(0, 1);
				}
			}*/
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
			if (optionMenu == 0)
			{
				window.clear(Color::White);
				part.generate();
				//part.getElement();
				//part.move(1, 1);
				part.draw(window);
				



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
