#include <SFML/Graphics.hpp>
#include<iostream>
#include "movent.h"
using namespace std;
using namespace sf;



int main()
{
	RenderWindow window(VideoMode(1024, 720), "Tetris V1.2");
	Texture tetrisPices;
	tetrisPices.loadFromFile("IMG/miniSquer.png");
	Sprite sprite(tetrisPices);
	
	sprite.setPosition(24, 24);
	Vector2f origineCurenta;
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		move(sprite);
			
		window.clear(Color::White);
		window.draw(sprite);
		window.display();
	}

}