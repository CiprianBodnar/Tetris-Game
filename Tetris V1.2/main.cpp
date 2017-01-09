
#include <SFML\Graphics.hpp>
#include<iostream>
#include "movent.h"
#include "Menu.h"
#include "PartOf.h"
#include <ctime>
#include <cstdlib>
#include <sstream>

void fill(int data[4][4], int rotate, int whichForm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			data[i][j] = Forms[whichForm][rotate][i][j];
}
void generate(int &rotate, int &whichForm,int &color,int data[4][4],bool activate_rotate)
{
	srand(time(NULL));
	whichForm = rand() % 7;
	rotate = rand() % 4;
	
	color = rand() % 5;
	fill(data, rotate, whichForm);
}

bool isValid(int xOffset , int yOffset ,int data[4][4],int posX,int posY,float windowX,float windowY)
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			if ((data[y][x] && (posX + x + xOffset >= windowX /SIZE-LIMIT_RL )) || (data[y][x] && (posX + x + xOffset <LIMIT_RL)) || (data[y][x] && (posY+y+yOffset>=windowY/SIZE-LIMIT_H1)))
				return false;
	return true;
}
void gravity(int data[4][4],bool &exit,int Table[TableH][TableW],Vector2f &formPos,Vector2f windowActualSize)
{
	if (isValid(0, 1, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && exit == 1)
	{


		formPos.y++;
		
		int i = 24;
		 int free = 1;
		while (i > 0 && exit == 1)
		{
			
			for (int j = 0; j < TableW; j++)
				if (Table[i - 1][j] == 1 || Table[i - 1][j] == 3)
					if (Table[i][j] == 2)
					{
						free = 0;
						exit = 0;

					}

			if (free == 1)
			{
				for (int j = 0; j < TableW; j++)
				{
					if (Table[i - 1][j] == 1)
						Table[i][j] = 1;
					if (Table[i - 1][j] == 3)
						Table[i][j] = 3;
				}
				for (int j = 0; j < TableW; j++)
					if ((Table[i][j] == 1 || Table[i][j] == 3) && (Table[i - 1][j] == 0 || Table[i - 1][j] == 2))
						Table[i][j] = 0;
			}


			i--;
		}

	}
}
void check(int Table[TableH][TableW],int &score)
{

	for (int i = TableH-1; i >=0; i--)
	{
		bool checkt = 1;
		for (int j = 0; j < TableW; j++)
			if (Table[i][j] == 0)
				checkt = 0;
		if (checkt == 1)
		{
			for (int k = i; k > 0; k--)
				for (int t = 0; t < TableW; t++)
					Table[k][t] = Table[k - 1][t];
			score = score + 100;
			cout << score << endl;
		}
	}
	
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
	Texture tetrisPices, background,ingame,gameover;
	tetrisPices.loadFromFile("IMG/tiles.png");
	background.loadFromFile("IMG/p3.png");
	ingame.loadFromFile("IMG/11.jpg");
	gameover.loadFromFile("IMG/game-over.jpg");
	// Background si fiecare patratel
	Sprite over(gameover);
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
	int data[4][4],next[4][4];
	bool lock = 1, lock2 = 1, exit = 1, free = 1, pass = 1, activate_rotate = 0;
	int rotate=rand()%4, Table[25][20] = { 0 };
	int whichForm=rand()%7,score=0;
	int nr = 0;
	int color;
	float timer=0, delay = 0.3f;
	Clock clock;
	srand(time ( NULL));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			next[i][j] = Forms[whichForm][rotate][i][j];
	// program
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
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
						for (int i = 0; i < TableH; i++)
						{
							for (int j = 0; j < TableW; j++)
								cout << Table[i][j]<<" ";
							cout << endl;
						}
					}
					if (event.key.code == Keyboard::Space)
					{
						
						int iaux, jaux;
						activate_rotate = 1;
						if (rotate == 3)
							rotate = 0;
						else
							rotate++;
						for(int i=0;i<TableH;i++)
							for(int j=0;j<TableW;j++)
								if(Table[i][j]==3)
								{
									iaux = i;
									jaux = j;
								}
						for (int i = 0; i < TableH; i++)
							for (int j = 0; j < TableW; j++)
								if (Table[i][j]==1 || Table[i][j]==3)
									Table[i][j] = 0;
						for (int i = 0; i < 4; i++)
							for (int j = 0; j < 4; j++)
							{

								if (Forms[whichForm][rotate][i][j] == 1 || Forms[whichForm][rotate][i][j]==3)
									Table[i+iaux][j+jaux] = Forms[whichForm][rotate][i][j];
							}
					}
					if (event.key.code == Keyboard::Left)
					{
						free = 1;
						if (isValid(-1, 0, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && free == 1)
						{

							formPos.x--;
							cout << formPos.x << endl;
							int j = 0;
							free = 1;
							while (j < TableW && free == 1)
							{
								for (int i = 0; i < TableH; i++)
									if (Table[i][j] == 2)
										if (Table[i][j + 1] == 1 || Table[i][j + 1] == 3)
											free = 0;

								if (free == 1)
								{

									for (int i = 0; i < TableH; i++)
										if (Table[i][j] == 0)
										{
											if (Table[i][j + 1] == 1)
												Table[i][j] = 1;
											if (Table[i][j + 1] == 3)
												Table[i][j] = 3;
										}
									for (int i = 0; i < TableH; i++)
										if (Table[i][j] == 1 || Table[i][j] == 3)
											if (Table[i][j + 1] == 0 || Table[i][j + 1] == 2)
												Table[i][j] = 0;
									j++;
								}
							}
						}
					}
					if (event.key.code == Keyboard::Right)
					{
						if (isValid(1, 0, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) )
							
						{
							
							formPos.x++;
							cout << formPos.x << endl;
							int j = 19;
							free = 1;
							while (j >0 && free==1)
							{
								
								for(int i=0;i<TableH;i++)
									if(Table[i][j]==2)
										if (Table[i][j - 1] == 1 || Table[i][j]==3)
											free = 0;
								if (free != 0)
								{
									for (int i = 1; i < TableH; i++)
									{
										if (Table[i][j - 1] == 1)
											Table[i][j] = 1;
										if (Table[i][j - 1] == 3)
											Table[i][j] = 3;
									}
										
									for (int i = 0; i < TableH; i++)
										if (Table[i][j] == 1 || Table[i][j]==3)
											if (Table[i][j - 1] == 0 || Table[i][j-1]==2)
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
								
								for (int j = 0; j < TableW; j++)
									if (Table[i - 1][j] == 1 || Table[i-1][j]==3)
										if (Table[i][j] == 2)
										{
											free = 0;
											exit = 0;

										}
										
								if (free == 1)
								{
									for (int j = 0; j < TableW; j++)
									{
										if (Table[i - 1][j] == 1)
											Table[i][j] = 1;
										if (Table[i - 1][j] == 3)
											Table[i][j] = 3;
									}
									for (int j = 0; j < TableW; j++)
										if ((Table[i][j] == 1 || Table[i][j]>=3) &&( Table[i - 1][j] == 0 || Table[i-1][j]==2))
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
		if (optionMenu == 0 )
		{
			if (pass == 1)
			{
				window.clear();
				window.draw(in);

				for (int i = 0; i < TableW; i++)
					if (Table[2][i] == 2)
						pass = 0;
				//NEW FORM	
				if (lock == 1 && pass == 1)
				{
					
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							data[i][j] = next[i][j];
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							if (data[i][j] == 1 || data[i][j] == 3)
								Table[i][j + (int)formPos.x / 2] = data[i][j];
					generate(rotate, whichForm, color, next, activate_rotate);

				}
				lock = 0;
				//bug fix
				for (int i = 0; i < TableH; i++)
					if (Table[i][0] == 1)
						for (int j = 0; j < TableH; j++)
							if (Table[j][TableW-1] == 1)
								Table[j][TableW-1]= 0;
				//draW
				for (int i = 0; i < TableH; i++)
					for (int j = 0; j < TableW; j++)
					{
						if (Table[i][j] == 1 || Table[i][j] == 2 || Table[i][j] == 3)
							drawForm(window, (j+TABLE_POS)*SIZE, (i)* SIZE,red);


					}
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						if (next[i][j] == 1 || next[i][j] == 3)
							drawForm(window,(  TABLE_POS+10+j)*SIZE, (TableH+ 1+ i)*SIZE, red);
				// table border
				for (int i = 0; i < 25; i++)
				{
					drawForm2(window, (TABLE_POS - 1)*SIZE, i * SIZE);
					drawForm2(window, (TABLE_POS+TableW)*SIZE, i * SIZE);
				}
				for(int i=-1;i<=20;i++)
					drawForm2(window, (i+TABLE_POS)*SIZE, TableH* SIZE);
				// gravity
				if (timer > delay)
				{
					gravity(data, exit, Table, formPos, windowActualSize);
					timer = 0;
				}
				//exit & score
				if (formPos.y == windowActualSize.y / SIZE - LIMIT_H2 || exit == 0)
				{
					generate(rotate, whichForm, color, data, activate_rotate);
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 4; j++)
							cout << data[i][j] << " ";
						cout << endl;
					}
					cout << endl;
					lock = 1;
					exit = 1;
					for (int i = 0; i < TableH; i++)
						for (int j = 0; j < TableW; j++)
							if (Table[i][j] == 1 || Table[i][j] == 3)
								Table[i][j] = 2;
					check(Table,score);

					formPos.x = windowActualSize.x / SIZE / 2;
					formPos.y = 0;

				}

			}
			//OP 1.1
			if (pass == 0)
			{
				window.clear();
				window.draw(over);
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
