#pragma once

#include <SFML\Graphics.hpp>
using namespace sf;
#include<iostream>
using namespace std;
enum ShapeIndexes { I = 0, O = 4, S = 8, Z = 12, T = 16, L = 20, J = 24 };
int Forms[7][4][4][4] = 
{
	// I
	{
	{ { 1,0,0,0 },
	{ 1,0,0,0 },
	{ 1,0,0,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,1,1 } },

	{ { 1,0,0,0 },
	{ 1,0,0,0 },
	{ 1,0,0,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,1,1 } },
	},
	// O
{
	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 1,1,0,0 } },
		},
	// S
{
	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,1,1,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 1,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,1,1,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 1,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 } },
		},
	// Z
{
	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,1,0 } },

	{ { 0,0,0,0 },
	{ 0,1,0,0 },
	{ 1,1,0,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,1,0 } },

	{ { 0,0,0,0 },
	{ 0,1,0,0 },
	{ 1,1,0,0 },
	{ 1,0,0,0 } },
		},
	// T
{
	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,1,0,0 },
	{ 1,3,1,0 } },

	{ { 0,0,0,0 },
	{ 1,0,0,0 },
	{ 1,1,0,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,1,0 },
	{ 0,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,1,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 } },
		},
	// L
{
	{ { 0, 0, 0, 0 },
	{ 1,0,0,0 },
	{ 1,0,0,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,1,1,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 1,1,0,0 },
	{ 0,1,0,0 },
	{ 0,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 0,0,1,0 },
	{ 1,1,1,0 } },
},
	// J
{
	{ { 0, 0, 0, 0 },
	{ 0,1,0,0 },
	{ 0,3,0,0 },
	{ 1,1,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,0,0,0 },
	{ 1,3,1,0 } },

	{ { 0,0,0,0 },
	{ 1,1,0,0 },
	{ 3,0,0,0 },
	{ 1,0,0,0 } },

	{ { 0,0,0,0 },
	{ 0,0,0,0 },
	{ 1,3,1,0 },
	{ 0,0,1,0 } },
},
};

#define WIDTH  6
#define HEIGHT  10
#define SIZE	20
#define LIMIT_RL 10
#define LIMIT_H1 11
#define LIMIT_H2 15
#define TableH 25
#define TableW 20
Color colors[5] = {
Color::Red,
Color::Green,
Color::Blue,
Color::Yellow,
Color::Cyan,
};

void drawForm(RenderWindow & window, float x, float y, Color c)
{
	
	RectangleShape rect(Vector2f( SIZE - 2, SIZE - 2));
	rect.setPosition(x + 1, y + 1);
	rect.setFillColor(c);
	rect.setOrigin(9, 9);
	window.draw(rect);
}
