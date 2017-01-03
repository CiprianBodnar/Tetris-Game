
#include <SFML\Graphics.hpp>
#include<iostream>
#include "movent.h"
#include "Menu.h"
#include "PartOf.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

void fill(bool data[4][4], int rotate, int whichForm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = Forms[whichForm][rotate][i][j];
}
void generate(int &rotate, int &whichForm,int &color,bool data[4][4])
{
	whichForm = rand() % 7;
	rotate = rand() % 4;
	color = rand() % 5;
	fill(data, rotate, whichForm);
}

bool isValid(int xOffset , int yOffset ,bool data[4][4],int posX,int posY,float windowX,float windowY)
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if ((data[y][x] && (posX + x + xOffset >= windowX /SIZE )) || (data[y][x] && (posX + x + xOffset <0)) || (data[y][x] && (posY+y+yOffset>=windowY/SIZE)))
				return false;
	return true;
}



struct P
{
	bool dataAUX[4][4];
	Vector2f auxFormPos;
	int colorAUX;
}v[100];





using namespace std;
using namespace sf;
int main()
{
	//Setarile ferestrei
	RenderWindow window(VideoMode(1020, 720), "Tetris V1.2");
	
	//window.setFramerateLimit(30);
	Vector2f windowActualSize,formPos;
	windowActualSize.x = (float)window.getSize().x;
	windowActualSize.y = (float)window.getSize().y;
	formPos.x = windowActualSize.x/SIZE/2;
	formPos.y = 0;
	
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

	//declaratii
	int optionMenu = -1;
	bool data[4][4], lock = 1, lock2 = 0, Table[51][36] = { 0 };
	int rotate;
	int whichForm;
	int nr = 0;
	int color;
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
					if (event.key.code == Keyboard::F)
						lock = 1;

					if (event.key.code == Keyboard::Left)
						if(isValid(-1,0,data,formPos.x,formPos.y,windowActualSize.x,windowActualSize.y))
						formPos.x--;
					if (event.key.code == Keyboard::Right)
					{
						if(isValid(1,0,data,formPos.x,formPos.y,windowActualSize.x,windowActualSize.y))
							formPos.x++;
					}
					if(event.key.code==Keyboard::Down)
						if (isValid(0, 1, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y))
							formPos.y++;
					
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
				window.clear(Color::Black);
				for(int k=1;k<=nr;k++)
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						if (v[k].dataAUX[i][j] == 1)
							drawForm(window, (j + v[k].auxFormPos.x)*SIZE, (i + v[k].auxFormPos.y)*SIZE, colors[v[k].colorAUX]);
				if (lock == 1)
					generate(rotate, whichForm, color, data);
				lock = 0;
				for (int i = 0; i<4; i++)
					for (int j = 0; j<4; j++)
						if (data[i][j] == 1)
							drawForm(window, (j +formPos.x)*SIZE, (i + formPos.y)*SIZE, colors[color]);
				
				if (formPos.y + 4 == windowActualSize.y / SIZE)
				{
					
					lock = 1;
					nr++;
					v[nr].auxFormPos.x = formPos.x;
					v[nr].auxFormPos.y = formPos.y;
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							v[nr].dataAUX[i][j] = data[i][j];
					v[nr].colorAUX = color;
					formPos.x = windowActualSize.x / SIZE / 2;
					formPos.y = 0;

					
				}
				
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
