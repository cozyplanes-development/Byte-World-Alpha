// Created by:
// Main Coder: Haxk20;
// Co Coder: Vu Prox;
// Tester: Programmers;
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool sunmoon = true;
bool running = true;
bool rain = false;
bool randX = true;
int RainDrops = 250;
int sunCycle = 0;
int SCycle = -35;
int RainX;
int RainY;
class Terrain
{
	
  public:

	void render()
	{
		SDL_RenderPresent(renderer);
	}
};

class Color
{
  public:
	int r;
	int g;
	int b;
	int a;

	void create(int R, int G, int B, int A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}
};

class GameObject
{
  public:
	SDL_Rect form;
	Color color;

	void set(int X, int Y, int SIZE, Color C)
	{
		form.x = X;
		form.y = Y;
		form.w = SIZE;
		form.h = SIZE;
		color = C;
	}
void setColor(Color C) {
	color = C;
}
	void move(int pX, int pY)
	{
		form.x = form.x + pX;
		form.y = form.y + pY;
	}

	void render()
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &form);
	}
};
class Rain {
	public:
	GameObject Rain[250];
	   
	   int lastY[250];
	   
		void setH( int RainDrops, Color RainColor) {
			for (int RainList = 0; RainList < RainDrops; RainList++) {
		Rain[RainList].set(0, 0, 10, RainColor);
		Rain[RainList].form.w = 2;
	}
		}
		void randXY( int RainDrops, int screen) {
			//Change X of the rain to random
		for (int RainArray = 0; RainArray < RainDrops; RainArray++) {
					RainY = rand() % RainDrops * 4;
				Rain[RainArray].form.y =- RainY;
					RainX = rand() % screen;
				Rain[RainArray].form.x = RainX;
			
			lastY[RainArray] = Rain[RainArray].form.y;
		}
		}
		//Move the Rain
		void Move( int RainDrops) {
			if (rain) {
			for (int RainArray = 0; RainArray < RainDrops; RainArray++) {
				Rain[RainArray].move(0, 5);
				Rain[RainArray].render();
				
			}
			}
		}
			void IsOutScreen(int RainDrops, int screen) {
				if (rain) {
			for (int RainArray = 0; RainArray < RainDrops; RainArray++) {
				if (Rain[RainArray].form.y > screen) {
					Rain[RainArray].form.y = lastY[RainArray];
				}
			}
				}
			}
		
};
int main()
{
	
	srand(time(NULL));
	SDL_DisplayMode screen;
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GetDesktopDisplayMode(0, &screen);
	window =
		SDL_CreateWindow("Byte World Pre-Alpha 1.4", SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED, screen.w, screen.h,
						 SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

	// Setup renderer

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	// Clear window
	SDL_RenderClear(renderer);

	
	Terrain Terrain;
	
	int length = 200;
	int MaxX = screen.w / 10;
	int MaxY = screen.h / 10;
	int map[MaxX][MaxY];
	// generate map
	int l = 0;
	int last = MaxY / 2;
	for (int x = 0; x < MaxX; x++)
	{
		int move = rand() % 3 - 1;
		last = last + move;
		for (int y = 0; y < MaxY; y++)
		{
			if (y > last)
			{
				map[x][y] = 0;	// nothing
			}
			else if (y == last)
			{
				map[x][y] = 1;	// grass
			}
			else if (y <= last - 1 && y >= last - 5)
			{
				map[x][y] = 2;	// dirt
			}
			else if (y <= 2 && y >= 1) {
				map[x][y] = 4; //Bedrock
			}
			else
			{
				map[x][y] = 3;	// stone
			}
			// to objects
			if (map[x][y] != 0)
			{
				l++;
			}
		}
	}
	// objects
	GameObject objects[l];
	int curr = 0;
	int mapX = 0;
	int mapY = 0;
	int size = 10;
	for (int i = 0; i < MaxX; i++)
	{
		for (int j = 0; j < MaxY; j++)
		{
			if (curr >= l)
			{
				continue;
			}
			if (map[i][j] != 0)
			{
				GameObject object;
				Color Color;
				switch (map[i][j])
				{
				case 1:
					Color.create(0, 255, 0, 0);
					break;
				case 2:
					Color.create(128, 64, 0, 0);
					break;
				case 3:
					Color.create(128, 128, 128, 0);
					break;
					case 4:
					Color.create(20, 20, 20, 0);
					break;
				default:
					Color.create(0, 0, 0, 0);
				}
				object.set(mapX + i * size, screen.h - (mapY + j * size), size, Color);
				objects[curr] = object;
				curr++;
			}
		}

	}
	// end
//Creating all objects;
	GameObject Player;
	GameObject Sun;
	GameObject Background;
	
	 Rain Rain;
	Color pCol;
	Color sun;
	Color moon;
	Color Day;
	Color MN;
	Color Night;
	Color RainColor;
	RainColor.create(0, 0, 255, 0);
	Night.create(0, 0, 0, 0);
	MN.create(255, 128, 0, 0);
	Day.create(0, 0, 255, 0);
	moon.create(128, 128, 128, 0);
	sun.create(255, 255, 0, 0);
	pCol.create(255, 0, 0, 0);
	Background.set(0, 0, 0, Day);
	Sun.set(-35, sin((Sun.form.x/180)* 3.14 / 180) * 100, 35, sun);
	Player.set(100, 100, 10, pCol);
	Player.form.h = 20;
	Background.form.h = screen.h;
	Background.form.w = screen.w;
	Rain.setH(RainDrops, RainColor);
	Rain.randXY(RainDrops, screen.w);
	
    

	// Code...
clock_t time = clock();
clock_t nextt = time;
	last = screen.h / 10;
	int x, y = 0;
	bool coll=false;

	while (running)
	{
		time = clock();
		for (int OArray = 0; OArray < l; OArray++)
		{
			objects[OArray].render();
			
		}
		//Collision checker;
		for (int a = 0; a < l; a++) {
			if (Player.form.y <= objects[a].form.y + objects[a].form.h
			     && Player.form.y + Player.form.h >= objects[a].form.y
			     && Player.form.x + 1 <= objects[a].form.x + objects[a].form.w
			     && Player.form.x + Player.form.w - 2 >= objects[a].form.x) {
			 coll =true;
			 break;
			}
		}
		if (!coll) {
			Player.move(0,2);
		}
		coll = false;
		
		//Sunand Moon cycle
			if (Sun.form.x <= -35) {
			if (rand() % 10 == 6) {
			rain = true;
			}
		}
		if (Sun.form.x != screen.w) {
			if (time - nextt >= 30000) {
			Sun.move(1, 0);
			Sun.form.y = 100 - sin((Sun.form.x * 180 / screen.w)* 3.14 / 180) * 100;
			nextt = time;
			}
		}

		if (sunCycle % 2 == 0) {
			Sun.setColor(sun);
			
		if (Sun.form.x < screen.w / 3) {
		Background.setColor(MN);
		}
		
		if (Sun.form.x > (screen.w / 3) * 2) {
			
		Background.setColor(MN);
		}
		
		if (Sun.form.x > screen.w / 3 && Sun.form.x < (screen.w / 3) * 2) {
		Background.setColor(Day);
		}
		}
		if (sunCycle % 2 == 1) {
			Sun.setColor(moon);
			Background.setColor(Night);
		}
		if (Sun.form.x == screen.w) {
			if (rain) {
				rain = false;
			}
		Sun.form.x = -35;
		sunCycle++;
		}
	//Rendering Stuff;
		Sun.render();
		Player.render();
		Terrain.render();
		Background.render();
        Rain.Move(RainDrops);
        Rain.IsOutScreen(RainDrops, screen.h);
		time = clock();
	}
}



