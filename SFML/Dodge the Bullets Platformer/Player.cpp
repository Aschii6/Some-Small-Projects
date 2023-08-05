#include "Player.h"


Player::Player()
{
	texture.loadFromFile("Resources/Player.png");

	setTexture(texture);

	velocityMax = sf::Vector2f(15.f, 22.f);
	velocityMin = sf::Vector2f(0.1f, 0.1f);
	velocity = sf::Vector2f(0.f, 0.f);

	gravity = 1.f;
	drag = 0.92f;

	facingRight = true;

	touchingGround = false;
}


void Player::update()
{
	velocity.x *= drag;
	velocity.y += gravity;

	if (velocity.x > velocityMax.x)
		velocity.x = velocityMax.x;
	else if (velocity.x < -velocityMax.x)
		velocity.x = -velocityMax.x;

	if (velocity.y > velocityMax.y)
		velocity.y = velocityMax.y;
	else if (velocity.y < -velocityMax.y)
		velocity.y = -velocityMax.y;

	if (abs(velocity.x) < velocityMin.x)
		velocity.x = 0.f;

	if (abs(velocity.y) < velocityMin.y)
		velocity.y = 0.f;

	move(velocity);
}

// Very very wierd things din cauza la scale, nu cred ca se modifica bine global bounds
// Maybe niste sprite animations si nu ar mai fi probleme

void Player::jump()
{
	if (!touchingGround)
	{
		return;
	}
	velocity.y = -velocityMax.y;
	touchingGround = false;
}


void Player::moveLeft()
{
	velocity.x -= 1.f;

	if (facingRight && velocity.x < 0)
	{
		scale(-1.f, 1.f);
		move(getGlobalBounds().width, 0.f);
		facingRight = false;
	}
}


void Player::moveRight()
{
	velocity.x += 1.f;

	if (!facingRight && velocity.x > 0)
	{
		scale(-1.f, 1.f);
		move(-getGlobalBounds().width, 0.f);
		facingRight = true;
	}
}

void Player::setTouchingGround(bool val)
{
	touchingGround = val;
}

void Player::setVerticalVelocityZero()
{
	velocity.y = 0.f;
}
