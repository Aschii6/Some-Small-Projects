#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Player:
	public sf::Sprite
{
	sf::Texture texture;

	sf::Vector2f velocity;
	sf::Vector2f velocityMax;
	sf::Vector2f velocityMin;

	float gravity;
	float drag;

	bool facingRight;

	bool touchingGround;
public:
	Player();

	void update();

	void jump();

	void moveLeft();
	void moveRight();

	void setTouchingGround(bool val);
	
	void setVerticalVelocityZero();
};

