
#include <SFML\Graphics.hpp>
#include<iostream>
#include "movent.h"
#include "Menu.h"
#include "PartOf.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

struct P
{
	bool dataAUX[4][4];
	Vector2f auxFormPos;
	int colorAUX;
}v[100];



void fill(bool data[4][4], int rotate, int whichForm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = Forms[whichForm][rotate][i][j];
}
void generate(int &rotate, int &whichForm,int &color,bool data[4][4],bool activate_rotate)
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
			if ((data[y][x] && (posX + x + xOffset >= windowX /SIZE-10 )) || (data[y][x] && (posX + x + xOffset <10)) || (data[y][x] && (posY+y+yOffset>=windowY/SIZE-11)))
				return false;
	return true;
}




using namespace std;
using namespace sf;
int main()
{
	//Setarile ferestrei
	RenderWindow window(VideoMode(800, 720), "Tetris V1.2");
	
	//window.setFramerateLimit(30);
	Vector2f windowActualSize,formPos;
	windowActualSize.x = (float)window.getSize().x;
	windowActualSize.y = (float)window.getSize().y;
	formPos.x = windowActualSize.x/SIZE/2;
	formPos.y = 0;
	
	// Incarc iaginiile
	Texture tetrisPices, background,ingame;
	tetrisPices.loadFromFile("IMG/tiles.png");
	background.loadFromFile("IMG/p3.png");
	ingame.loadFromFile("IMG/11.jpg");
	// Background si fiecare patratel
	Sprite spriteBack(background);
	Sprite in(ingame);
	Sprite blue(tetrisPices), red(tetrisPices), green(tetrisPices), yellow(tetrisPices);
	Sprite Form[5][5] = { blue };
	// Delimitez fiecare patratel din imagine "mama"
	//in.setPosition(formPos.x, 50);
	blue.setTextureRect(IntRect(0, 0, 18, 18));
	red.setTextureRect(IntRect(18, 0, 18, 18));
	green.setTextureRect(IntRect(36, 0, 18, 18));
	yellow.setTextureRect(IntRect(54, 0, 18, 18));

	
	Menu menu(window.getSize().x, window.getSize().y);

	//declaratii
	int optionMenu = -1;
	bool data[4][4], lock = 1, lock2 = 1, exit = 1, free = 1, pass = 1,activate_rotate=0;
	int rotate, Table[25][20] = { 0 };
	int whichForm;
	int nr = 0;
	int color;
	
	// program
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
					{
						for (int i = 0; i < 25; i++)
						{
							for (int j = 0; j < 20; j++)
								cout << Table[i][j]<<" ";
							cout << endl;
						}
					}
					if (event.key.code == Keyboard::Space)
					{
						
						cout << rotate << endl;

					}
					if (event.key.code == Keyboard::Left)
						if (isValid(-1, 0, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y))
						{
					
							formPos.x--;
							cout << formPos.x << endl;
							int j = 0;
							free = 1;
							while (j < 20 && free==1)
							{
								for (int i = 0; i < 25; i++)
									if (Table[i][j] == 2)
										if (Table[i][j +1] == 1)
										{
											free = 0;
										}
								if (free == 1)
								{
									
									for (int i = 0; i < 25; i++)
										if(Table[i][j]==0)
										if (Table[i][j + 1] == 1)
											
											Table[i][j] = 1;
									for (int i = 0; i < 25; i++)
										if (Table[i][j] == 1)
											if (Table[i][j + 1] == 0)
												Table[i][j] = 0;
									j++;
								}
							}
						}
					if (event.key.code == Keyboard::Right)
					{
						if (isValid(1, 0, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y))
						{
							
							formPos.x++;
							cout << formPos.x << endl;
							int j = 19;
							free = 1;
							while (j > 0 && free==1)
							{
								
								for(int i=0;i<25;i++)
									if(Table[i][j]==2)
										if (Table[i][j - 1] == 1)
											free = 0;
								if (free != 0)
								{
									for (int i = 1; i < 25; i++)
										if (Table[i][j - 1] == 1)	
											Table[i][j] = 1;
										
									for (int i = 0; i < 25; i++)
										if (Table[i][j] == 1)
											if (Table[i][j - 1] == 0)
												Table[i][j] = 0;
								}
								
								j--;
							}
						}

					}
					if (event.key.code == Keyboard::Down) {
						if (isValid(0, 1, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && exit == 1)
						{
							
							
								formPos.y++;
							cout << formPos.y << endl;
							int i = 24;
							free = 1;
							while (i > 0 && exit==1)
							{
								
								for (int j = 0; j < 20; j++)
									if (Table[i - 1][j] == 1)
										if (Table[i][j] == 2)
										{
											free = 0;
											exit = 0;

										}
										
								if (free == 1)
								{
									for (int j = 0; j < 20; j++)
										if(Table[i-1][j]==1)
										Table[i][j] = 1;
									for (int j = 0; j < 20; j++)
										if (Table[i][j] == 1 && Table[i - 1][j] == 0)
											Table[i][j] = 0;
								}
									
								
								i--;
							}
							
						}
						
					} 
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
			window.draw(in);

			if (lock == 1)
			{
				generate(rotate, whichForm, color, data,activate_rotate);
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
					{
						
						if (data[i][j] == 1)
							Table[i][j + (int)formPos.x/2 ] = data[i][j];
					}
			}
			lock = 0;
			
			
			for (int i = 0; i < 25; i++)
				for (int j = 0; j < 20; j++)
				{
					if (Table[i][j] == 1 || Table[i][j]==2)
						drawForm(window, (j)*SIZE, (i)* SIZE, color[colors]);

				
				}
			
			if (formPos.y == windowActualSize.y/SIZE-15 || exit==0)
			{
				cout << "intra";
				lock = 1;
				exit = 1;
				for (int i = 0; i < 25; i++)
					for (int j = 0; j < 20; j++)
						if (Table[i][j])
							Table[i][j] = 2;
						

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
