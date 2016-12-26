#include <SFML/Graphics.hpp>
#include<iostream>
#include "movent.h"

using namespace std;
using namespace sf;



int main()
{
	RenderWindow window(VideoMode(1024, 720), "Tetris V1.2");

	RectangleShape jucator;
	jucator.setPosition(500, 500);
	jucator.setFillColor(Color::Black);
	jucator.setSize(Vector2f(20,30));

	
	Texture tetrisPices;
	tetrisPices.loadFromFile("IMG/tiles.png");
	Sprite sprite(tetrisPices);
	sprite.setPosition(24, 24);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));
	sprite.setOrigin(9, 9);
	Vector2f sizeOfTetrisPices;

	/*sizeOfTetrisPices = 
	cout << sizeOfTetrisPices.x << " " << sizeOfTetrisPices.y << endl;*/



	Vector2u windowActualSize;
	windowActualSize = window.getSize();
	bool ok = 1;
	while (window.isOpen())
	{
		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			
		}
		
		if(ok==1)
		moveDown(sprite);
		if (sprite.getOrigin().y + sprite.getPosition().y >500.f)
			ok = 0;
		else ok = 1;
		if (Mouse::getPosition(window).x > 500 && Mouse::getPosition(window).y > 500 && Mouse::getPosition(window).x < 520 && Mouse::getPosition(window).y < 530)
			if (Mouse::isButtonPressed(Mouse::Left))
				cout << "buton patratel apasat";
			
		
		move(sprite,windowActualSize.x,windowActualSize.y);
		window.clear(Color::White);
		window.draw(sprite);
		window.draw(jucator);
		window.display();
	}

}