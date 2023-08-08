#pragma once
#include <SFML/Graphics.hpp>
using namespace std;


class CTransform {
public:
	sf::Vector2f pos = { 0, 0 };
	sf::Vector2f velocity = { 0, 0 };

	//sf::Vector2f scale = { 1, 1 };
	float angle = 0;

	CTransform() {}

	CTransform(const sf::Vector2f p, const sf::Vector2f v, float a): pos(p), velocity(v), angle(a) {}

	void increaseAngle() {
		angle += 1;
		angle = fmod(angle, 360);
	}
};


class CShape {
public:
	sf::CircleShape circle;

	CShape(float radius, int points, sf::Color fill, sf::Color outline, float thickness): circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};


class CCollision {
public:
	float radius = 0;

	CCollision(float r): radius(r) {}
};


class CInput {
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shooting = false;

	CInput() {}
};


class CScore {
public:
	int score = 0;

	CScore(int s): score(s) {}
};


class CLifespan {
public:
	int remaining = 0;

	CLifespan(int t): remaining(t) {}
};


/*
class CName {
public:
	string name;

	CName() {}

	CName(string n): name(n) {}
};
*/