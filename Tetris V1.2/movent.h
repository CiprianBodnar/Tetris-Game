#include<SFML\Graphics.hpp>

using namespace sf;
using namespace std;
float normalSpeed = 0.25f;

Vector2f elementPosition, elementOrigin;
void move(Sprite &sprite, unsigned windowXsize,unsigned windowYsize)
{
	
	elementPosition = sprite.getPosition();
	elementOrigin = sprite.getOrigin();
	if (Keyboard::isKeyPressed(Keyboard::D) )
		if(elementPosition.x+elementOrigin.x<windowXsize)
		sprite.move(Vector2f(normalSpeed, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::S) )
		if(elementPosition.y+elementOrigin.y<windowYsize)
		sprite.move(Vector2f(0.0f, normalSpeed));
	if (Keyboard::isKeyPressed(Keyboard::W))
		sprite.move(Vector2f(0.0f, -normalSpeed));
	if (Keyboard::isKeyPressed(Keyboard::A))
		if(elementPosition.x+elementOrigin.x>0)
		sprite.move(Vector2f(-normalSpeed,0.0f ));
}
float normalSpeedOfPiece = 0.05f;
void moveDown(Sprite &sprite)
{
	sprite.move(Vector2f(0.0f, normalSpeedOfPiece));
}