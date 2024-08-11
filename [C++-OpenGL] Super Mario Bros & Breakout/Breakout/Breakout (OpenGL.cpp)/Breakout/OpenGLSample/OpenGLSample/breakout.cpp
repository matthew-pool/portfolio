/*
* Modify code to create a custom Breakout game demo
* @file: assignment_8_3.cpp
* @brief: Recreation of the popular game Breakout using modern OpenGL.
* @date: December 17, 2023
* @reviser: Matthew Pool
* @attributions:
*	original file: SNHU CS-330: Computational Graphics & Visualization
*	tutorial: https://learnopengl.com
* @note: potential update to use delta time and speed to determine distance for objects
*/
#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>
#include <ctime>

using namespace std;
//--------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------
namespace
{
	// Color
	struct Color {
		float r;	// red component
		float g;	// green component
		float b;	// blue component
		//float a;	// alpha component

		// parameterized constructor
		Color(float red, float green, float blue) : r(red), g(green), b(blue) {}
	};
	//--------------------------------------------------------------------------------
	const Color RED = Color(1.0f, 0.0f, 0.0f);  // optionally: const Color RED(1.0f, 0.0f, 0.0f);
	const Color GREEN = Color(0.0f, 1.0f, 0.0f);
	const Color BLUE = Color(0.0f, 0.0f, 1.0f);
	const Color YELLOW = Color(1.0f, 1.0f, 0.0f);
	const Color CYAN = Color(0.0f, 1.0f, 1.0f);
	const Color MAGENTA = Color(1.0f, 0.0f, 1.0f);
	const Color WHITE = Color(1.0f, 1.0f, 1.0f);
	const Color BLACK = Color(0.0f, 0.0f, 0.0f);
	const Color GRAY = Color(0.5f, 0.5f, 0.5f);
	const Color ORANGE = Color(1.0f, 0.5f, 0.0f);
	const Color PURPLE = Color(0.5f, 0.0f, 0.5f);
	const Color BROWN = Color(0.5f, 0.25f, 0.0f);
	const Color PINK = Color(1.0f, 0.75f, 0.8f);
	const Color DARK_RED = Color(0.5f, 0.0f, 0.0f);
	const Color DARK_GREEN = Color(0.0f, 0.5f, 0.0f);
	const Color DARK_BLUE = Color(0.0f, 0.0f, 0.5f);
	const Color DARK_YELLOW = Color(0.5f, 0.5f, 0.0f);
	const Color DARK_CYAN = Color(0.0f, 0.5f, 0.5f);
	const Color DARK_MAGENTA = Color(0.5f, 0.0f, 0.5f);
	const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f);
	const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f);
	const Color LIGHT_RED = Color(1.0f, 0.5f, 0.5f);
	const Color LIGHT_GREEN = Color(0.5f, 1.0f, 0.5f);
	const Color LIGHT_BLUE = Color(0.5f, 0.5f, 1.0f);
	const Color LIGHT_YELLOW = Color(1.0f, 1.0f, 0.5f);
	const Color LIGHT_CYAN = Color(0.5f, 1.0f, 1.0f);
	const Color LIGHT_MAGENTA = Color(1.0f, 0.5f, 1.0f);
	const Color LIGHT_ORANGE = Color(1.0f, 0.75f, 0.5f);
	const Color LIGHT_PURPLE = Color(0.75f, 0.5f, 1.0f);
	const Color LIGHT_BROWN = Color(0.75f, 0.5f, 0.25f);
	const Color LIGHT_PINK = Color(1.0f, 0.75f, 0.8f);
	//--------------------------------------------------------------------------------
	vector<Color> allColors = { RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK, GRAY, ORANGE, PURPLE, BROWN, PINK, DARK_RED, DARK_GREEN, DARK_BLUE, DARK_YELLOW, DARK_CYAN, DARK_MAGENTA, DARK_GRAY, LIGHT_GRAY, LIGHT_RED, LIGHT_GREEN, LIGHT_BLUE, LIGHT_YELLOW, LIGHT_CYAN, LIGHT_MAGENTA, LIGHT_ORANGE, LIGHT_PURPLE, LIGHT_BROWN, LIGHT_PINK };
	vector<Color> colors = { BLUE, YELLOW, MAGENTA, ORANGE, CYAN, DARK_YELLOW, DARK_MAGENTA, LIGHT_PINK, LIGHT_BLUE, LIGHT_YELLOW, LIGHT_MAGENTA, LIGHT_PINK };
	//--------------------------------------------------------------------------------
	// Numeric
	const float DEG2RAD = 3.14159f / 180.0f;
	const int WINDOW_WIDTH = 720; //480; //1280;
	const int WINDOW_HEIGHT = 720; //480; //720;
	int bricksPerRow = 16;  // ideally can divide WINDOW_WIDTH evenly (1280 or 480: 1, 2, 4, 5, 8, 10, 16, 20, 32, 40, 80, 160)
	int bricksPerCol = 12;	// ideally less than bricksPerRow
	int numBricks = static_cast<int>(bricksPerRow * bricksPerCol);  // bricksPerRow * bricksPerCol = numBricks
	float brickWidth = (WINDOW_WIDTH / bricksPerRow) / (WINDOW_WIDTH * 0.5f);  // normalizes px coords to 0..1 for screen coords 
	float brickHeight = brickWidth / 2.0f;  // FIXME: set to 0.1f
	int bricksDestroyed = 0;
	bool firstLoop = true;
	//--------------------------------------------------------------------------------
	enum BrickType { REFLECTIVE, COLORED };
	enum OnOff { ON, OFF };
	//--------------------------------------------------------------------------------
	int numBalls = 3;
	bool ballStuck = true;  // ball stuck to paddle until space bar pressed
	const float BALL_SPEED = 0.01f; //0.01591f;  // 0.0225f / sqrt(2) = 0.01591f
	bool randomize = false;  // randomizes ball speed variance every frame to vary angle and prevent 45 degree trajectories from hitting corners through gaps
	//--------------------------------------------------------------------------------
	vector<int> offIndices = { 64, 65, 80, 81, 96, 97, 112, 113, 78, 79, 94, 95, 110, 111, 126, 127, 70, 71, 72, 73, 86, 87, 88, 89, 102, 103, 104, 105, 118, 119, 120, 121 };
	vector<int> reflectiveIndices = { 38, 39, 40, 41, 54, 55, 56, 57, 69, 74, 85, 90, 101, 106, 117, 122, 134, 135, 136, 137, 150, 151, 152, 153 };
	//--------------------------------------------------------------------------------
	// Directions
	const unsigned int UP = 1;
	const unsigned int RIGHT = 2;
	const unsigned int DOWN = 3;
	const unsigned int LEFT = 4;
	const unsigned int UP_RIGHT = 5;
	const unsigned int UP_LEFT = 6;
	const unsigned int DOWN_RIGHT = 7;
	const unsigned int DOWN_LEFT = 8;
}  // end namespace
//--------------------------------------------------------------------------------
// Brick class
//--------------------------------------------------------------------------------
class Brick
{
public:
	BrickType type;
	float x, y; //z;
	float width, height;
	float r, g, b; //alpha;
	OnOff onOff;
	float halfW;
	float halfH;
	int hitPoints;

	// default constructor
	Brick() : type(COLORED), x(0.0f), y(0.0f), width(0.0f), height(0.0f), r(0.0f), g(0.0f), b(0.0f), onOff(ON), halfW(0.0f), halfH(0.0f), hitPoints(0)
	{}

	// parameterized constructor
	Brick(BrickType type, float x, float y, float width, float height, float r, float g, float b)  // BrickType, x, y, width, r, g, b
		: type(type), x(x), y(y), width(width), height(height), r(r), g(g), b(b), onOff(ON), halfW(width / 2.0f), halfH(height / 2.0f), hitPoints(2)
	{}
	//--------------------------------------------------------------------------------
	// Brick::drawBrick
	//--------------------------------------------------------------------------------
	void drawBrick()
	{
		if (onOff == OFF)
			return;

		// else draw brick
		float outline = 0.01f;
		float halfW = width / 2.0f - outline / 2.0f;	// visual half width
		float halfH = height / 2.0f - outline / 2.0f;	// visual half height

		glColor3f(r, g, b);  // sets the current color using float values
		glBegin(GL_POLYGON);	// starts the definition of a primitive ('mode' can be GL_POINTS, GL_LINES, GL_TRIANGLES, GL_QUADS, GL_POLYGON)
		// ALTERNATIVE: create/bind VAO, VBO, EBO, and use glDrawElements() and pass to shader
		//glBegin(GL_TRIANGLES);

		// glVertex2d: specifies a 2D vertex using float values (used bewteen glBegin() and glEnd())
		// ALTERNATIVE: store vertex data in a VBO and use glVertexAttribPointer() and glEnableVertexAttribArray() to pass to shader

		glVertex2f(x + halfW, y + halfH);  //glTexCoord2f(0.0f, 0.0f); glVertex2f(x - halfW, y - halfH);
		glVertex2f(x + halfW, y - halfH);  //glTexCoord2f(1.0f, 0.0f); glVertex2f(x + halfW, y - halfH);
		glVertex2f(x - halfW, y - halfH);  //glTexCoord2f(1.0f, 1.0f); glVertex2f(x + halfW, y + halfH);
		glVertex2f(x - halfW, y + halfH);  //glTexCoord2f(0.0f, 1.0f); glVertex2f(x - halfW, y + halfH);

		glEnd();  // ends the definition of vertices for a primitive
	}
};
//--------------------------------------------------------------------------------
// Class Instances
//--------------------------------------------------------------------------------
vector<Brick> bricks(numBricks);
//--------------------------------------------------------------------------------
// Paddle class
// -------------------------------------------------------------------------------
class Paddle
{
public:
	// Paddle attributes
	float x, y, width, halfW;
	float r, g, b;
	float speed;
	
	// default constructor
	Paddle() : x(0.0f), y(-0.99f), width(0.2f), halfW(width / 2.0f), r(CYAN.r), g(CYAN.g), b(CYAN.b), speed(0.05f)
	{}

	// parameterized constructor
	Paddle(float x, float y, float width, float halfW, float r, float g, float b, float speed)
		: x(x), y(y), width(width), halfW(width / 2.0f), r(r), g(g), b(b), speed(speed)
	{}

	void drawPaddle(float x, float y, float halfW, float r, float g, float b)
	{
		glColor3f(r, g, b);
		glBegin(GL_LINES);
		glVertex3f(x - halfW, y, 0.0f);
		glVertex3f(x + halfW, y, 0.0f);
		glEnd();
	}
};
//--------------------------------------------------------------------------------
// Class Instances
//--------------------------------------------------------------------------------
Paddle paddle;
//--------------------------------------------------------------------------------
// Ball class
//--------------------------------------------------------------------------------
class Ball
{
public:
	float r, g, b;
	float radius;
	float x;
	float y;
	// TODO: use angle theta in calculation to determine factors of x and y speed
	// PYTHAGOREAN: speed^2 = xSpeed^2 + ySpeed^2
	float speed;	// x and y speeds found with pythagorean theorem: totalSpeed / sqrt(2) = x & y speeds
	int direction;
	bool firstStep = true;

	// default constructor
	Ball() : x(0.0f), y(0.0f), direction(UP), radius(0.0f), r(0.0f), g(0.0f), b(0.0f), speed(0.0f)
	{}

	// parameterized constructor
	Ball(float x, float y, int dir, float radius, float r, float g, float b)
		: x(x), y(y), direction(dir), radius(radius), r(r), g(g), b(b), speed(BALL_SPEED)
	{}
	//--------------------------------------------------------------------------------
	// Ball-Brick Collision
	//--------------------------------------------------------------------------------
	void CheckCollision(Brick* brick, int index)  // passed by reference to change the original values
	{
		if (brick->onOff == OFF)
			return;

		// axis parallel edge boundaries
		const float topBrick = brick->y + brick->halfH;
		const float rightBrick = brick->x + brick->halfW;
		const float bottomBrick = brick->y - brick->halfH;
		const float leftBrick = brick->x - brick->halfW;
		const float topBall = y + radius;
		const float rightBall = x + radius;
		const float bottomBall = y - radius;
		const float leftBall = x - radius;
		float dx, dy;  // distance between ball and parallel brick edges
		// @note: ball expected to be in bricks at varying depths when collision is detected
		//--------------------------------------------------------------------------------
		// FIXME: simplify code to just compare center vertices of ball and brick edges
		// TODO: use angle theta in calculation to determine factors of x and y to move ball

		// @note: (x,y) variables represent center of ball
		if ((x + radius >= leftBrick && x - radius <= rightBrick) && (y + radius >= bottomBrick && y - radius <= topBrick)) // ball-brick collision
		{
			if (direction == UP_RIGHT)
			{
				dx = abs(rightBall - leftBrick);  // distance is absolute value
				dy = abs(topBall - bottomBrick);

				if (dx < dy) // bounces off left side of brick
				{
					y += dx; // resets ball position
					x -= dx; // resets ball position
					direction = UP_LEFT;
				}
				else if (dy < dx) // bounces off bottom side of brick (or even)
				{
					y -= dy; // resets ball position
					x += dy; // resets ball position
					direction = DOWN_RIGHT;
				}
				
				else // corner case
				{
					direction = DOWN_LEFT;
					/*
					if (bricks.at(index - 1).onOff == ON && bricks.at(index + 16).onOff == ON)  // if bricks to the left and below are ON
					{
						y -= dy; // resets ball position
						x -= dx; // resets ball position
						direction = DOWN_LEFT;
					}
					else if (bricks.at(index - 1).onOff == ON && bricks.at(index + 16).onOff == OFF)  // if brick to the left is ON and below is OFF
					{
						y -= dy; // resets ball position
						x += dx; // resets ball position
						direction = DOWN_RIGHT;
					}
					else if ((bricks.at(index - 1).onOff == OFF && bricks.at(index + 16).onOff == ON) ||	// if brick to the left is OFF and below is ON
						(bricks.at(index - 1).onOff == OFF && bricks.at(index + 16).onOff == OFF))			// if bricks to the left and below are OFF
					{
						y += dy; // resets ball position
						x -= dx; // resets ball position
						direction = UP_LEFT;
					}
					*/
				}
			}

			else if (direction == UP_LEFT)
			{
				dx = abs(leftBall - rightBrick);  // distance is absolute value
				dy = abs(topBall - bottomBrick);

				if (dx < dy) // bounces off right side of brick
				{
					y += dx; // resets ball position
					x += dx; // resets ball position
					direction = UP_RIGHT;
				}
				else if (dy < dx) // bounces off bottom side of brick (or even)
				{
					y -= dy; // resets ball position
					x -= dy; // resets ball position
					direction = DOWN_LEFT;
				}
				
				else // corner case
				{
					direction = DOWN_RIGHT;
					/*
					if (bricks.at(index + 1).onOff == ON && bricks.at(index + 16).onOff == ON)  // if bricks to the right and below are ON
					{
						y -= dy; // resets ball position
						x += dx; // resets ball position
						direction = DOWN_RIGHT;
					}
					else if (bricks.at(index + 1).onOff == ON && bricks.at(index + 16).onOff == OFF)  // if brick to the right is ON and below is OFF
					{
						y -= dy; // resets ball position
						x -= dx; // resets ball position
						direction = DOWN_LEFT;
					}
					else if ((bricks.at(index + 1).onOff == OFF && bricks.at(index + 16).onOff == ON) ||	// if brick to the right is OFF and below is ON
						(bricks.at(index + 1).onOff == OFF && bricks.at(index + 16).onOff == OFF))			// if bricks to the right and below are OFF
					{
						y += dy; // resets ball position
						x += dx; // resets ball position
						direction = UP_RIGHT;
					}
					*/
				}
			}

			else if (direction == DOWN_RIGHT)
			{
				dx = abs(rightBall - leftBrick);  // distance is absolute value	
				dy = abs(bottomBall - topBrick);

				if (dx < dy) // bounces off left side of brick
				{
					y -= dx; // resets ball position
					x -= dx; // resets ball position
					direction = DOWN_LEFT;
				}
				else if (dy < dx) // bounces off top side of brick (or even)
				{
					y += dy; // resets ball position
					x += dy; // resets ball position
					direction = UP_RIGHT;
				}
				
				else // handle corner case
				{
					direction = UP_LEFT;
					/*
					if (bricks.at(index - 1).onOff == ON && bricks.at(index - 16).onOff == ON)  // if bricks to the left and above are ON
					{
						y += dy; // resets ball position
						x -= dx; // resets ball position
						direction = UP_LEFT;
					}
					else if (bricks.at(index - 1).onOff == ON && bricks.at(index - 16).onOff == OFF)  // if brick to the left is ON and above is OFF
					{
						y += dy; // resets ball position
						x += dx; // resets ball position
						direction = UP_RIGHT;
					}
					else if ((bricks.at(index - 1).onOff == OFF && bricks.at(index - 16).onOff == ON) ||	// if brick to the left is OFF and above is ON
						(bricks.at(index - 1).onOff == OFF && bricks.at(index - 16).onOff == OFF))			// if bricks to the left and above are OFF
					{
						y -= dy; // resets ball position
						x -= dx; // resets ball position
						direction = DOWN_LEFT;
					}
					*/
				}
			}

			else if (direction == DOWN_LEFT)
			{
				dx = abs(leftBall - rightBrick);  // distance is absolute value
				dy = abs(bottomBall - topBrick);

				if (dx < dy) // bounces off right side of brick
				{
					y -= dx; // resets ball position
					x += dx; // resets ball position
					direction = DOWN_RIGHT;
				}
				else if (dy < dx) // bounces off top side of brick (or even)
				{
					y += dy; // resets ball position
					x -= dy; // resets ball position
					direction = UP_LEFT;
				}
				
				else // handle corner case
				{
					direction = UP_RIGHT;
					/*
					if (bricks.at(index + 1).onOff == ON && bricks.at(index - 16).onOff == ON)  // if bricks to the right and above are ON
					{
						y += dy; // resets ball position
						x += dx; // resets ball position
						direction = UP_RIGHT;
					}
					else if (bricks.at(index + 1).onOff == ON && bricks.at(index - 16).onOff == OFF)  // if brick to the right is ON and above is OFF
					{
						y += dy; // resets ball position
						x -= dx; // resets ball position
						direction = UP_LEFT;
					}
					else if ((bricks.at(index + 1).onOff == OFF && bricks.at(index - 16).onOff == ON) ||	// if brick to the right is OFF and above is ON
						(bricks.at(index + 1).onOff == OFF && bricks.at(index - 16).onOff == OFF))			// if bricks to the right and above are OFF
					{
						y -= dy; // resets ball position
						x += dx; // resets ball position
						direction = DOWN_RIGHT;
					}
					*/
				}
			}
			//--------------------------------------------------------------------------------
			// Update Brick
			//--------------------------------------------------------------------------------
			if (brick->type == REFLECTIVE)
			{
				// TODO: audio "clink" sound
			}
			else if (brick->type == COLORED)
			{
				brick->hitPoints -= 1;  // starts at 2
				if (brick->hitPoints == 1)
				{
					// TODO: audio "crack" sound
					brick->r = 0.99f; // tints brick reddish color
					brick->g = brick->g * 0.8f; // shades original color
					brick->b = brick->b * 0.8f; // shades original color
				}
				else if (brick->hitPoints == 0)
				{
					// TODO: audio "crumble" sound
					brick->onOff = OFF;  // brick disappears
					bricksDestroyed += 1;
				}
			}
		}
	}
	//--------------------------------------------------------------------------------
	// Ball::MoveOneStep (Ball Movement and Boundary Detection/Reaction)
	//--------------------------------------------------------------------------------
	void MoveOneStep()
	{
		if (ballStuck == true)
			return;

		if (randomize)
		{
			// randoFactor: random 1..10 normalized to 0.9f..1.0f (rounded to 2 decimal places)
			float randomNum = round((0.98f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1.0f - 0.98f)))) * 10000.0f) / 10000.0f;
			int randomSwitch = rand() % 2; // 0 or 1
			float randomFactor;

			if (randomSwitch == 0)
				randomFactor = round(1 / randomNum * 10000.0f) / 10000.0f;  // increases speed
			else
				randomFactor = randomNum;	  // decreases speed

			speed = BALL_SPEED; // reset to default
			speed = speed * randomFactor;
		}

		if (direction == UP_LEFT)
		{
			if (x < -1.0f + radius) // ball edge passed left edge
			{
				x = (-1.0f + radius) + speed; // resets to edge and moves right
				y += speed; // keep going up
				direction = UP_RIGHT;
			}
			else
			{
				x -= speed; // keep going left
				y += speed; // keep going up
			}

			if (y > 1.0f - radius) // ball edge passed top edge
			{
				y = (1.0f - radius) - speed; // resets to edge and moves down
				x -= speed; // keep going left
				direction = DOWN_LEFT;
			}
			else
			{
				y += speed; // keep going up
				x -= speed; // keep going left
			}
		}

		else if (direction == UP_RIGHT)
		{
			if (x > 1.0f - radius) // ball edge passed right edge
			{
				x = (1.0f - radius) - speed; // resets to edge and moves left
				y += speed; // keep going up
				direction = UP_LEFT;
			}
			else
			{
				x += speed; // keep going right
				y += speed; // keep going up
			}

			if (y > 1.0f - radius) // ball edge passed top edge
			{
				y = (1.0f - radius) - speed; // resets to edge and moves down
				x += speed; // keep going right
				direction = DOWN_RIGHT;
			}
			else
			{
				y += speed; // keep going up
				x += speed; // keep going right
			}
		}
		else if (direction == DOWN_LEFT)
		{
			if (x < -1.0f + radius) // ball edge passed left edge
			{
				x = (-1.0f + radius) + speed; // resets to edge and moves right
				y -= speed; // keep going down
				direction = DOWN_RIGHT;
			}
			else
			{
				x -= speed; // keep going left
				y -= speed; // keep going down
			}

			if (y < -1.0f + radius) // ball edge passed bottom edge
			{
				y = (-1.0f + radius) + speed; // resets to edge and moves up
				x -= speed; // keep going left
				direction = UP_LEFT;
			}
			else
			{
				y -= speed; // keep going down
				x -= speed; // keep going left
			}
		}

		else if (direction == DOWN_RIGHT)
		{
			if (x > 1.0f - radius) // ball edge passed right edge
			{
				x = (1.0f - radius) - speed; // resets to edge and moves left
				y -= speed; // keep going down
				direction = DOWN_LEFT;
			}
			else
			{
				x += speed; // keep going right
				y -= speed; // keep going down
			}

			if (y < -1.0f + radius) // ball edge passed bottom edge
			{
				y = (-1.0f + radius) + speed; // resets to edge and moves up
				x += speed; // keep going right
				direction = UP_RIGHT;
			}
			else
			{
				y -= speed; // keep going down
				x += speed; // keep going right
			}
		}
	}
	//--------------------------------------------------------------------------------
	// Ball::DrawBall
	//--------------------------------------------------------------------------------
	void DrawBall()
	{
		glColor3f(r, g, b);   // sets the current color using float values
		glBegin(GL_POLYGON);	// starts the definition of a primitive ('mode' can be GL_POINTS, GL_LINES, GL_TRIANGLES, GL_QUADS, GL_POLYGON)
		// ALTERNATIVE: create/bind VAO, VBO, EBO, and use glDrawElements() and pass to shader
		//glBegin(GL_TRIANGLES);

		for (int i = 0; i < 360; i++)  // 360 draws a full circle
		{
			float degInRad = i * DEG2RAD;

			// specifies a 2D vertex using float values (used bewteen glBegin() and glEnd())
			// ALTERNATIVE: store vertex data in a VBO and use glVertexAttribPointer() and glEnableVertexAttribArray() to pass to shader
			glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
		}
		glEnd();  // ends the definition of vertices for a primitive
	}
};
//--------------------------------------------------------------------------------
// Class Instances
//--------------------------------------------------------------------------------
vector<Ball> balls;
//--------------------------------------------------------------------------------
// Function Prototypes
//--------------------------------------------------------------------------------
void processInput(GLFWwindow* window);
int getRandomDirection();
void CheckCollision();
//--------------------------------------------------------------------------------
// Main
//--------------------------------------------------------------------------------
int main(void)
{
	srand(static_cast<unsigned int>(time(nullptr)));  // seeds the random number generator with the current time

	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);  // change to 4.6+ if using shaders
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Breakout II: The Breakout", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
//--------------------------------------------------------------------------------
// Create Bricks
//--------------------------------------------------------------------------------	
	float leftEdge = -1.0f;
	float topEdge = 1.0f;
	float halfH = brickHeight / 2.0f;
	float halfW = brickWidth / 2.0f;
	float x;
	float y;

	Brick brick;

	unsigned int rowCount = 0;
	int index = 0;

	for (int row = 0; row < bricksPerCol; row++)
	{
		y = topEdge - halfH - (brickHeight * rowCount);

		for (int col = 0; col < bricksPerRow; col++)  // for every column entry of every row
		{
			x = leftEdge + halfW + (col * brickWidth);
			brick = Brick(COLORED, x, y, brickWidth, brickHeight, colors[row].r, colors[row].g, colors[row].b);
			bricks[index] = brick;
			index++;
		}

		rowCount++;
	}

	//	disables (turns off) listed bricks
	for (unsigned int i = 0; i < offIndices.size(); i++)
	{
		bricks[offIndices.at(i)].onOff = OFF;
	}
	// changes listed bricks to gray REFLECTIVE bricks
	for (unsigned int i = 0; i < reflectiveIndices.size(); i++)
	{
		bricks[reflectiveIndices.at(i)].type = REFLECTIVE;
		bricks[reflectiveIndices.at(i)].r = 0.5f;
		bricks[reflectiveIndices.at(i)].g = 0.5f;
		bricks[reflectiveIndices.at(i)].b = 0.5f;
	}
//--------------------------------------------------------------------------------
	// 2 Bouncing Balls
	float x1, x2, y1, y2, radius1, radius2, r1, r2, g1, g2, b1, b2;
	int direction1, direction2;

	// red ball
	x1 = -0.1f;
	y1 = 0.7f;
	radius1 = 0.015f;
	r1 = 1.0f;
	g1 = 0.0f;
	b1 = 0.0f;
	direction1 = 5; //getRandomDirection();
	Ball ball1(x1, y1, direction1, radius1, r1, g1, b1);
	balls.push_back(ball1);
	
	// blue ball
	x2 = 0.09f;
	y2 = 0.67f;
	radius2 = 0.015f;
	r2 = 0.0f;
	g2 = 0.0f;
	b2 = 1.0f;
	direction2 = 5; //getRandomDirection();
	Ball ball2(x2, y2, direction2, radius2, r2, g2, b2);
	balls.push_back(ball2);
//--------------------------------------------------------------------------------
// Game/Render Loop
//--------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / static_cast<float>(height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);
//--------------------------------------------------------------------------------
// Update Objects
// --------------------------------------------------------------------------------
		CheckCollision(); // check current ball collisions with other balls

		// TODO: possibly modify
		for (int i = 0; i < balls.size(); i++) // for each ball
		{
			for (int j = 0; j < bricks.size(); j++) // check for each brick
				balls[i].CheckCollision(&bricks[j], j);     // check current ball collisions with bricks

			balls[i].MoveOneStep();  // move current ball and update direction if necessary
			balls[i].DrawBall();	 // draw current ball

			if (bricksDestroyed >= 9)  // REFLECTIVE become COLORED
			{
				for (unsigned int i = 0; i < reflectiveIndices.size(); i++)
				{
					bricks[reflectiveIndices.at(i)].type = COLORED;
					bricks[reflectiveIndices.at(i)].r = RED.r;
					bricks[reflectiveIndices.at(i)].g = RED.g;
					bricks[reflectiveIndices.at(i)].b = RED.b;
				}
			}
		}
		/*
		if (firstLoop)
		{
			cout << " RED BALL INITIAL: " << balls[0].direction << endl;
			cout << "BLUE BALL INITIAL: " << balls[1].direction << endl;
			firstLoop = false;
			cin.get();
		}
	
		if (!ballStuck)
		{
			cout << "red ball: " << balls[0].direction << endl;
			cout << "blue ball: " << balls[1].direction << endl;
			//cout << balls[2].direction << endl;
		}
		*/
//--------------------------------------------------------------------------------
// Draw Objects
//--------------------------------------------------------------------------------
		// Bricks
		for (Brick& brick : bricks)
			brick.drawBrick();

		// Paddle
		paddle.drawPaddle(paddle.x, paddle.y, paddle.halfW, paddle.r, paddle.g, paddle.b);

//--------------------------------------------------------------------------------
// Swap Buffers and Poll IO Events
//--------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}  // end render loop
//--------------------------------------------------------------------------------
// Cleanup
//--------------------------------------------------------------------------------
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
//--------------------------------------------------------------------------------
// Function Definitions
//--------------------------------------------------------------------------------
int getRandomDirection()
{
	const unsigned int MAX = 2;
	const unsigned int MIN = 1;
	const unsigned int RANGE = MAX - MIN + 1;
	const unsigned int RANDOM = (rand() % RANGE) + MIN;  // random integer between MIN and MAX

	if (RANDOM == 1)
		return UP_RIGHT;	// 5
	else if (RANDOM == 2)
		return UP_LEFT;		// 6
	//else if (RANDOM == 1)
//	return UP;			// 1
	
	return -1;
}
//--------------------------------------------------------------------------------
// Ball-Ball Collision
//--------------------------------------------------------------------------------
void CheckCollision()
{
	if (balls.size() < 2) // only 1 ball
		return;

	for (unsigned int i = 0; i < balls.size(); i++)  // for each ball
	{
		for (unsigned int j = i + 1; j < balls.size(); j++)  // (i+1) to avoid checking collision with itself  / redundancy
		{
			float dx = abs(balls[i].x - balls[j].x); // x distance between balls' center points
			float dy = abs(balls[i].y - balls[j].y); // y distance between balls' center points
			float distance = sqrt(dx * dx + dy * dy); // Pythagorean/Euclidean distance between balls' center points

			// collision detected
			if (distance <= balls[i].radius + balls[j].radius) // if distance between balls' center points is less than the sum of their radii
			{
				//srand(static_cast<unsigned int>(time(NULL)));  // seeds the random number generator with the current time
				balls[i].r = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
				balls[i].g = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
				balls[i].b = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
				balls[j].r = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
				balls[j].g = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
				balls[j].b = static_cast<float>(rand() % 256) / 255.0f;  // 0..255 number normalized to 0..1
			}
		}
	}
}
//--------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// TODO: else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) // pause

	// pressing space bar creates a new ball
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (ballStuck == false)
			return;

		/*
		float x, y; //z;
		float r, g, b; //a;
		int direction = getRandomDirection();
		x = 0.0f;
		y = 0.0f;
		//z = 0.0f;
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		//a = 1.0f;
		float radius = 0.015f;
		*/

		//Ball ball(x, y, direction, radius, r, g, b);
		Ball ball(0.0f, 0.0f, getRandomDirection(), 0.015f, 1.0f, 1.0f, 1.0f); //Ball ball(x, y, direction, radius, r, g, b
		balls.push_back(ball);  // new ball added to world
		ballStuck = false;
	}
	// Paddle movement
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (paddle.x > -1 + paddle.halfW)
			paddle.x -= paddle.speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		if (paddle.x < 1 - paddle.halfW)
			paddle.x += paddle.speed;
	}
}
