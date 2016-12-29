#include<SFML\Graphics.hpp>

using namespace sf;
using namespace std;
float normalSpeed = 0.25f;

Vector2f elementPosition, elementOrigin;
void move(Sprite &sprite, unsigned windowXsize,unsigned windowYsize,unsigned line,unsigned column,int M[5][5])
{
	unsigned up = 0, down = 0, left = 0, right = 0;
	for (int i = column; i < 5; i++)
		if (M[line][i] == 1)
			right++;
	for (int i = column; i >= 0; i--)
		if (M[line][i] == 1)
			left++;
	for (int i = line; i >= 0; i--)
		if (M[i][column] == 1)
			up++;
	for (int i = line; i < 4; i++)
		if (M[i][column] == 1)
			down++;
	right = right * 18;
	left = left * 18;
	up = up * 18;
	down = down * 18;
	
	

	elementPosition = sprite.getPosition();
	elementOrigin = sprite.getOrigin();
	if (Keyboard::isKeyPressed(Keyboard::D) )
		if(elementPosition.x+elementOrigin.x<windowXsize-right)
		sprite.move(Vector2f(normalSpeed, 0.0f));
	if (Keyboard::isKeyPressed(Keyboard::S) )
		if(elementPosition.y+elementOrigin.y<windowYsize-down)
		sprite.move(Vector2f(0.0f, normalSpeed));
	if (Keyboard::isKeyPressed(Keyboard::A))
		if(elementPosition.x+elementOrigin.x-left>18)
		sprite.move(Vector2f(-normalSpeed,0.0f ));
}
float normalSpeedOfPiece = 0.05f;
void moveDown(Sprite &sprite)
{
	sprite.move(Vector2f(0.0f, normalSpeedOfPiece));
}