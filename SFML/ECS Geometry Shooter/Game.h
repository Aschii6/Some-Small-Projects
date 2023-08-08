#pragma once
#include "Entity Manager.h"

#define speed 10


class Game
{
	sf::RenderWindow window;

	sf::Font font;
	sf::Text scoreText;

	EntityManager entityManager;
	
	shared_ptr<Entity> player;

	//vector<sf::Color> colors;

	string scoreString;

	int score = 0;
	int currentFrame = 0;
	int enemyCooldown = 0;
	int shootCooldown = 0;

	int nrOfEnemies = 0, maxNrOfEnemies = 20;

	void init();

	void update();

	// Systems
	void movementSystem();
	void collisionSystem();
	void userInputSystem();
	void renderSystem();
	void enemySpawnSystem();
	void lifespanSystem();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(shared_ptr<Entity> entity);
	void spawnBullet(shared_ptr<Entity> entity, sf::Vector2f& mousePos);

	bool isColliding(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2);
public:
	Game();

	void run();
};

