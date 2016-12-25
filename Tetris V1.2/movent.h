#include<SFML\Graphics.hpp>
using namespace sf;

float normalSpeed = 0.25f;

void move(Sprite &sprite)
{

	if (Keyboard::isKeyPressed(Keyboard::A))
		sprite.move(Vector2f(-normalSpeed, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::D))
		sprite.move(Vector2f(normalSpeed, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::S))
		sprite.move(Vector2f(0.0f, normalSpeed));
	if (Keyboard::isKeyPressed(Keyboard::W))
		sprite.move(Vector2f(0.0f, -normalSpeed));

}