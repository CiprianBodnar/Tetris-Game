
#include <SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

#include<iostream>
#include "movent.h"
#include "Menu.h"
#include "Forms.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include<string>
#include<fstream>
using namespace std;
using namespace sf;
bool l= 1;




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
void gravity(int data[4][4],bool &exit,int Table[TableH][TableW],Vector2f &formPos,Vector2f windowActualSize,int &bug)
{
	if (isValid(0, 1, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && exit == 1)
	{


		formPos.y++;
		
		int i = 24;
		 int free = 1;
		 for (int i = 0; i<TableH; i++)
			 for (int j = 0; j < TableW; j++)
				 if (Table[i][j] == 1 || Table[i][j] == 3)
					 if (Table[i + 1][j] == 2)
						 exit = 0;
			 
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
				 l = 1;
				for (int j = 0; j < TableW; j++)
				{
					if (Table[i - 1][j] == 1)
					{
						Table[i][j] = 1;
						l = 0;
					}
					if (Table[i - 1][j] == 3)
						Table[i][j] = 3;
					
				}
				
				for (int j = 0; j < TableW; j++)
					if (Table[0][j] == 1)
					{
						Table[0][j] = 0;
						Table[4][j] = 1;
						
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
		while (checkt==1)
		{


			for (int j = 0; j < TableW; j++)
				if (Table[i][j] == 0)
					checkt = 0;
			if (checkt == 1)
			{
				for (int k = i; k > 0; k--)
					for (int t = 0; t < TableW; t++)
						Table[k][t] = Table[k - 1][t];
				score = score + 100;
			}
		}
	}
	
}

void sortare(int v[4])
{
	for(int i=0;i<9;i++)
		for(int j=i+1;j<10;j++)
			if (v[i] < v[j])
			{
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
}

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
	Texture tetrisPices, background,ingame,gameover,scoreBack;
	Text Score,Score_text,Time,Time2,Time_text,time_min,car,PlayerScore,playerscoretext;
	Font font;
	font.loadFromFile("fonts/Springmarch-Roman.otf");
	scoreBack.loadFromFile("IMG/5.jpg");
	tetrisPices.loadFromFile("IMG/tiles.png");
	background.loadFromFile("IMG/p33.jpg");
	ingame.loadFromFile("IMG/gameBg2.jpg");
	gameover.loadFromFile("IMG/game-over.jpg");
	// Background si fiecare patratel
	Sprite over(gameover);
	Sprite ScoreBack(scoreBack);
	Sprite spriteBack(background);
	Sprite in(ingame);
	Sprite blue(tetrisPices), red(tetrisPices), green(tetrisPices), yellow(tetrisPices);
	Sprite Form[5][5] = { blue };
	
	Music music,musicCol,musicMenu;
	musicCol.setVolume(15);
	musicMenu.setVolume(25);
	if (!music.openFromFile("songs/OMFG_-_Wonderful.ogg"))
		cout << "ERORR";
	
	if (!musicCol.openFromFile("songs/col.ogg"))
		cout << "Col Music ERORR";
	if (!musicMenu.openFromFile("songs/menu.ogg"))
		cout << "Error";
	// Delimitez fiecare patratel din imagine "mama"
	//in.setPosition(formPos.x, 50);
	blue.setTextureRect(IntRect(0, 0, 18, 18));
	red.setTextureRect(IntRect(18, 0, 18, 18));
	green.setTextureRect(IntRect(36, 0, 18, 18));
	yellow.setTextureRect(IntRect(54, 0, 18, 18));

	
	Menu menu(window.getSize().x, window.getSize().y);

	//declaratii
	int optionMenu = -1;
	int data[4][4], next[4][4], stop[4][4] = { 0 }, auxStop[4][4] = { 0 };
	bool lock = 1, lock2 = 1, exit = 1, free = 1, pass = 1, activate_rotate = 0, go = 1, deseneaza = 0, deseneaza2 = 0, spaceactivate = 1, Song = 1, down = 1;

	int nr = 0, min = 0, v[10] = { 0 }, color, m = 1, whichForm = rand() % 7, score = 0, rotate = rand() % 4, Table[25][20] = { 0 }, auxf,bug=0;
	float timer=0, delay = 0.3f,timer2=0;
	Clock clock,clock2;
	srand(time ( NULL));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			next[i][j] = Forms[whichForm][rotate][i][j];
	

	auxf = whichForm;
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
					if (event.key.code == Keyboard::M)
					{
						if (m == -1)
						{
							ingame.loadFromFile("IMG/gameBg2.jpg");
							music.play();
						}
						if (m == 1)
						{
							ingame.loadFromFile("IMG/GameBg.jpg");
							music.stop();
						}
						m = m*-1;

					}
					if (event.key.code == Keyboard::Down)
					{
						musicMenu.play();
						menu.MoveDown();
						m = -1;
					}
					if (event.key.code == Keyboard::Up)
					{
						m = -1;
						musicMenu.play();
						menu.MoveUp();
					}
					
					if (event.key.code == Keyboard::Escape)
					{
						if (optionMenu == -1)
							window.close();
						if (pass == 0)
						{
							formPos.x = windowActualSize.x / SIZE / 2;
							formPos.y = 0;
							optionMenu = -1;
							pass=1;
							go = 1;
							for (int i = 0; i <= TableH; i++)
								for (int j = 0; j <= TableW; j++)
									Table[i][j] = 0;
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									stop[i][j] = 0;
							clock2.restart();
							score = 0;
							exit = 0;
							Song = 1;
							m = -1;
						}
						if (optionMenu == 0)
						{
							formPos.x = windowActualSize.x / SIZE / 2;
							formPos.y = 0;
							optionMenu = -1;
							for (int i = 0; i <= TableH; i++)
								for (int j = 0; j <= TableW; j++)
									Table[i][j] = 0;
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									stop[i][j] = 0;
							go = 1;
							exit = 0;
							music.stop();
							clock2.restart();
							score = 0;
							Song = 1;
							m = -1;
						}
						if (optionMenu == 1)
						{
							formPos.x = windowActualSize.x / SIZE / 2;
							formPos.y = 0;
							optionMenu = -1;
							go = 1;
							Song = 1;
						}
						
					}
					if(spaceactivate==1)
					if (event.key.code == Keyboard::Space)
					{
						spaceactivate = 0;
						bool este1 = 1;
						for (int i = 0; i < 4; i++)
							for (int j = 0; j < 4; j++)
								if (stop[i][j] == 1)
									este1 = 0;
						if (este1 == 1)
						{
							
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									stop[i][j] = data[i][j];
							for (int i = 0; i < TableH; i++)
								for (int j = 0; j < TableW; j++)
									if (Table[i][j] == 1 || Table[i][j] == 3)
										Table[i][j] = 0;
							lock = 1;
							
							deseneaza = 1;
							formPos.x = windowActualSize.x / SIZE / 2;
							formPos.y = 0;
						}
						else
						{
							
							for(int i=0;i<4;i++)
								for (int j = 0; j < 4; j++)
								{
									auxStop[i][j] = stop[i][j];
									stop[i][j] = data[i][j];
								}
									for (int i = 0; i < TableH; i++)
										for (int j = 0; j < TableW; j++)
											if (Table[i][j] == 1 || Table[i][j] == 3)
												Table[i][j] = 0;
									formPos.x = windowActualSize.x / SIZE / 2;
									formPos.y = 0;
									lock = 0;
									deseneaza2 = 1;
								
						}

					}
					if (event.key.code == Keyboard::Left)
					{
						free = 1;
						if (isValid(-1, 0, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && free == 1)
						{

							formPos.x--;
							int j = 0;
							free = 1;
							for (int i = 0; i < TableH; i++)
								for (int j = 0; j < TableW; j++)
									if (Table[i][j] == 1 || Table[i][j] == 3)
										if (Table[i][j - 1] == 2)
											free = 0;
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
							
							int j = 19;
							free = 1;
							for (int i = 0; i < TableH; i++)
								for (int j = 0; j < TableW; j++)
									if (Table[i][j] == 1 || Table[i][j] == 3)
										if (Table[i][j + 1] == 2)
											free = 0;
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
										if (Table[i][j] == 1 || Table[i][j] == 3)
										{
											if (Table[i][j - 1] == 0 || Table[i][j - 1] == 2)
												Table[i][j] = 0;
											
										}
									
								}
								
								j--;
							}
						}

					}
					if (event.key.code == Keyboard::Down) 
					{
						if (isValid(0, 1, data, formPos.x, formPos.y, windowActualSize.x, windowActualSize.y) && exit == 1)
						{
							
							
								formPos.y++;
							
							int i = 24;
							free = 1;
							for (int i = 0; i<TableH; i++)
								for (int j = 0; j < TableW; j++)
									if (Table[i][j] == 1 || Table[i][j] == 3)
										if (Table[i + 1][j] == 2)
											exit = 0;
								
							
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
									 l = 1;
									for (int j = 0; j < TableW; j++)
									{
										if (Table[i - 1][j] == 1)
										{
											Table[i][j] = 1;
											l = 0;
										}
										if (Table[i - 1][j] == 3)
											Table[i][j] = 3;
										for (int j = 0; j < TableW; j++)
											if (Table[0][j] == 1)
											{
												Table[0][j] = 0;
												Table[4][j] = 1;

											}
									}
									for (int j = 0; j < TableW; j++)
										if ((Table[i][j] == 1 || Table[i][j]>=3) &&( Table[i - 1][j] == 0 || Table[i-1][j]==2) )
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
			if (down == 1)
			{
				formPos.x = windowActualSize.x / SIZE / 2;
				formPos.y = 0;

			}
			down = 0;
			if (Song == 1)
			{
				music.play();
				music.setVolume(15);
			}
			Song = 0;
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
							if (Table[j][TableW-1] == 1 || Table[j][TableW-1]==3)
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
							drawForm(window,(  TABLE_POS+23+j)*SIZE, (TableH-5+ i)*SIZE, red);
				
				if(deseneaza==1)
					for (int i = 0; i<4; i++)
						for (int j = 0; j<4; j++)
							if (stop[i][j] == 1 || stop[i][j] == 3)
								drawForm(window, (TABLE_POS-7  + j)*SIZE, (TableH -5 + i)*SIZE, red);
				if (deseneaza2 == 1)
				{
					
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							if (stop[i][j] == 1 || stop[i][j] == 3)
								drawForm(window, (TABLE_POS-7 + j)*SIZE, (TableH - 5 + i)*SIZE, red);
					for (int i = 0; i < 4; i++)
						for (int j = 0; j < 4; j++)
							if (auxStop[i][j] == 1 || auxStop[i][j] == 3)
								Table[i][j + (int)formPos.x / 2] = auxStop[i][j];
					lock = 0;
				}
				deseneaza2 = 0;
				// gravity
				if (timer > delay)
				{
					gravity(data, exit, Table, formPos, windowActualSize,bug);
					timer = 0;
				}
				//exit & score & time
				string Sc,tm,tmin;
				
				
				Sc=to_string(score);
				Score.setString(Sc);
				Score.setFont(font);
				Score.setFillColor(Color::White);
				Score.setPosition(Vector2f((SCORE_POS_ON_GAME-1)*SIZE, TableW*2));
				Score_text.setString("Score:");
				Score_text.setFont(font);
				Score_text.setFillColor(Color::White);
				Score_text.setPosition(Vector2f((TableW + 10)*SIZE, TableW*2));
				Time_text.setString("Time: ");
				Time_text.setFont(font);
				Time_text.setFillColor(Color::White);
				Time_text.setPosition(Vector2f((TableW + 10)*SIZE , TableW * 8));
				
				

				tm = to_string(clock2.getElapsedTime().asSeconds());
				Time.setString(tm[0]);
				Time.setFillColor(Color::White);
				Time.setFont(font);
				Time.setPosition(Vector2f((SCORE_POS_ON_GAME-1)*SIZE, TableW * 8));
				if(tm[1]!='.')
				{
					tm = to_string(clock2.getElapsedTime().asSeconds());
					Time2.setString(tm[1]);
					Time2.setFillColor(Color::White);
					Time2.setFont(font);
					Time2.setPosition(Vector2f((SCORE_POS_ON_GAME)*SIZE, TableW * 8));
					window.draw(Time2);
				}
				if (tm[0] == '6' && tm[1] == '0')
				{
					min++;
					clock2.restart();
					
					
				}
				car.setString(".");
				car.setFillColor(Color::White);
				car.setFont(font);
				car.setPosition(Vector2f((SCORE_POS_ON_GAME - 2)*SIZE, TableW * 8));
				tmin = to_string(min);
				time_min.setString(tmin);
				time_min.setFillColor(Color::White);
				time_min.setFont(font);
				time_min.setPosition(Vector2f((SCORE_POS_ON_GAME - 3)*SIZE, TableW * 8));

				window.draw(Score);
				window.draw(Score_text);
				window.draw(Time_text);
				window.draw(Time);
				window.draw(time_min);
				window.draw(car);
				if (formPos.y == windowActualSize.y / SIZE - LIMIT_H2 || exit == 0)
				{
					bug = 0;
					musicCol.play();
					auxf = whichForm;
					score = score + min+1;
					spaceactivate = 1;
					generate(rotate, whichForm, color, data, activate_rotate);
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
				music.stop();
				String playerScore = to_string(score);
				PlayerScore.setFillColor(Color::Black);
				PlayerScore.setFont(font);
				PlayerScore.setPosition(Vector2f(SIZE*25, SIZE*12));
				PlayerScore.setString(playerScore);

				playerscoretext.setFillColor(Color::Black);
				playerscoretext.setFont(font);
				playerscoretext.setString("Your score:");
				playerscoretext.setPosition(Vector2f(SIZE*15 , SIZE * 12));
				if (lock2 == 1)
				{
					ifstream f2("new.txt");

					for (int i = 0; i < 9; i++)
						f2 >> v[i];
					

					v[9] = score;
					sortare(v);
					

					ofstream g("new.txt");
					for (int i = 0; i < 9; i++)
						g << v[i]<<endl;
				}
				lock2 = 0;
				window.clear();
				window.draw(over);
				window.draw(playerscoretext);
				window.draw(PlayerScore);
			}
			
		
		}

			// OP2
			if (optionMenu == 1)
			{
				music.stop();
				window.clear();
				window.draw(ScoreBack);
				int v2[10];
				if (go == 1)
				{
					ifstream f2("new.txt");
					
					
					while (!f2.eof())
					{
						f2>> v2[nr];
						nr++;
					}
				}
				go = 0;
				Text S[10],Contor[10],Punct[10];
				String SS[10],ContorS[10];
				int Spos = 150;
				for (int i = 0; i < 9; i++)
				{
					ContorS[i] = to_string(i + 1);
					Contor[i].setFillColor(Color::Black);
					Contor[i].setFont(font);
					Contor[i].setString(ContorS[i]);
					Contor[i].setPosition(Vector2f(55, Spos));
					Punct[i].setFillColor(Color::Black);
					Punct[i].setFont(font);
					Punct[i].setString(".");
					Punct[i].setPosition(Vector2f(72, Spos));
					SS[i] = to_string(v2[i]);
					S[i].setString(SS[i]);
					S[i].setFillColor(Color::Black);
					S[i].setFont(font);
					S[i].setPosition(Vector2f(85, Spos));
					window.draw(S[i]);
					window.draw(Contor[i]);
					window.draw(Punct[i]);
					Spos = Spos + 50;
				}
			}

			if (optionMenu == -1)
			{
				window.draw(spriteBack);
				menu.draw(window);
			}
			window.display();
		}

	}
