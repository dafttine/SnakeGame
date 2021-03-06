// SFML Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

//globals
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels
int w = size * num_horzBox; //background numvber of pixels in width
int h = size * num_vertBox; //background numvber of pixels in height


int direction, direction2, snake_length = 4, snake_length2 = 4;

//Maximum size of Snake
struct Snake {
	int x, y;
}s[100];

struct Snake2 {
	int x, y;
}s2[100];

struct Fruit {
	int x, y;
}food;

float Tick(float delay) {
	//Move the remaining pieces of snake s[1] - s[99]
	for (int i = snake_length; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	//head of snake depenads on direction of user s[0]
	//User up
	if (direction == 3) {
		s[0].y -= 1;
	}
	//user down
	if (direction == 0) {
		s[0].y += 1;
	}
	//user left
	if (direction == 1) {
		s[0].x -= 1;
	}
	//user right
	if (direction == 2) {
		s[0].x += 1;
	}

	//If Snake eats food it should grow
	if (((s[0].x) == food.x) && ((s[0].y) == food.y)) {
		snake_length++;
		//Randomly plac food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
		return delay -= .001;
	}
	//Boundary Checking screen loop back on other side
	if (s[0].x > num_horzBox) {
		s[0].x = 0;
	}
	if (s[0].x < 0) {
		s[0].x = num_horzBox;
	}
	if (s[0].y > num_vertBox) {
		s[0].y = 0;
	}
	if (s[0].y < 0) {
		s[0].y= num_vertBox;
	}

	//Check if go over snake
	for (int i = 1; i < snake_length; i++) {
		//Cut snake in half from piece eaten
		if (s[0].x == s[i].x && s[0].y == s[i].y) {
			snake_length = i;
		}
	}

	//Move the remaining pieces of snake s[1] - s[99]
	for (int i = snake_length2; i > 0; --i)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}

	//head of snake depenads on direction of user s[0]
	//user2 up
	if (direction2 == 4) {
		s2[0].y -= 1;
	}
	//user2 down
	if (direction2 == 5) {
		s2[0].y += 1;
	}
	//user2 left
	if (direction2 == 6) {
		s2[0].x -= 1;
	}
	//user2 right
	if (direction2 == 7 || direction2 == 0) {
		s2[0].x += 1;
	}

	if (((s2[0].x) == food.x) && ((s2[0].y) == food.y)) {
		//Randomly place food somewhere else
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;
		snake_length2++;
		return delay -= .001;
	}
	//Boundary Checking screen loop back on other side
	if (s2[0].x > num_horzBox) {
		s2[0].x = 0;
	}
	if (s2[0].x < 0) {
		s2[0].x = num_horzBox;
	}
	if (s2[0].y > num_vertBox) {
		s2[0].y = 0;
	}
	if (s2[0].y < 0) {
		s2[0].y = num_vertBox;
	}

	//Check if go over snake
	for (int i = 1; i < snake_length2; i++) {
		//Cut snake in half from piece eaten
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y) {
			snake_length2 = i;
		}
	}
}
int main(){

	srand(time(0));
	RenderWindow window(VideoMode(w, h), "Snake Game!");

	//Textures
	//difference between textures and sprites?
	Texture t1, t2, t3, t4;
	t1.loadFromFile("white.png");
	t2.loadFromFile("red.png");
	t3.loadFromFile("test.png");
	t4.loadFromFile("purple.png");

	//Sprite
	//has physical dimensions
	Sprite Sprite1(t1);
	Sprite Sprite2(t2);
	Sprite Sprite3(t3);
	Sprite Sprite4(t4);
	food.x = 10;
	food.y = 10;

	Clock clock;
	float timer = 0, delay = .1;
	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something
		Event e;
		
		//check when window is closed
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}

		//Controls for Snake Movement by User
		if (Keyboard::isKeyPressed(Keyboard::Up)) direction = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)) direction = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) direction = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = 2;

		//Controls for Snake Movement by User2
		if (Keyboard::isKeyPressed(Keyboard::W)) direction2 = 4;
		if (Keyboard::isKeyPressed(Keyboard::S)) direction2= 5;
		if (Keyboard::isKeyPressed(Keyboard::A)) direction2 = 6;
		if (Keyboard::isKeyPressed(Keyboard::D)) direction2 = 7;


		if (timer > delay) {
			timer = 0; //reset timer
			delay = Tick(delay); //Move Snake one Sprite Foward	
		}
	
		//Draw
		window.clear();

		//draw background
		for (int i = 0; i < num_horzBox; i++) {
			for (int j = 0; j < num_vertBox; j++) {
				Sprite1.setPosition(i*size, j *size);
				window.draw(Sprite1);
			}
		}
		//Draw Snake
		for (int i = 0; i < snake_length; i++){
			Sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(Sprite2);
		}

		for (int i = 0; i < snake_length2; i++) {
			Sprite4.setPosition(s2[i].x*size, s2[i].y*size);
			window.draw(Sprite4);
		}

		//Draw Fruit
		Sprite3.setPosition(food.x*size, food.y * size);
		window.draw(Sprite3);
		window.display();
	}
    return 0;
	}
