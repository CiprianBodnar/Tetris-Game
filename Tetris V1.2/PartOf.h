#include "Forms.h"
#include<iostream>
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace std;
class PartOf
{
private:
	int shapeIndex;
	int data[4][4], posX, posY, color;
	int g;

	void fillData()
	{
			
		for (int i = 0; i < 4; i++)
			for (int m = 0; m < 4; m++)
				data[i][m] = Forms[shapeIndex][g][i][m];
	}
	
public:
	PartOf()
	{
		posX = 2;
		posY = -4;
		generate();
	}

	void generate()
	{
		
		int g = (rand() % 7) * 4;
		//shapeIndex = (ShapeIndexes)g;
		color = g / 4;
	
		fillData();
	}

	void move(int x, int y)
	{
		if (isValid(x, y))
		{
			posX += x;
			posY += y;
		}

	}

	void rotate()
	{
		int coIndex = shapeIndex;
		shapeIndex = ((shapeIndex + 1) % 4 == 0 ? shapeIndex - 3 : shapeIndex + 1);
	fillData();
		if (!isValid())
		{
			shapeIndex = coIndex;
			fillData();
		}
	}

	bool isValid(int xOffset = 0, int yOffset = 0)
	{
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				if ((data[y][x] && (posX + x + xOffset >= WIDTH || posX + xOffset < 0)) || (data[y][x] && (posY + y + yOffset > HEIGHT)))
				{
					return false;
				}

		return true;
	}

	/*void draw(RenderWindow & window)
	{
		for (int i = 0; i < 4; i++)
			for (int m = 0; m < 4; m++)
				if (data[i][m])
				{
					
					drawForm(window, (m + 20) * SIZE, (i +20) * SIZE, Form[color]);
					
				}
	}*/

	int getPosX()
	{
		return posX;
	}

	int getPosY()
	{
		return posY;
	}

	int getElement(int x, int y)
	{
		return data[y][x];
	}
};