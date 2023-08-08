#include "Game.h"

void Game::init()
{
	window.create(sf::VideoMode::getDesktopMode(), "ECS Geometry Shooter", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	/*colors.push_back(sf::Color::Red);
	colors.push_back(sf::Color::Green);
	colors.push_back(sf::Color::Blue);
	colors.push_back(sf::Color::Yellow);
	colors.push_back(sf::Color::Magenta);
	colors.push_back(sf::Color::Cyan);
	colors.push_back(sf::Color::White);*/

	font.loadFromFile("Resources/arial_bold.ttf");
	scoreText.setFont(font);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(10, 10);

	spawnPlayer();
}

Game::Game()
{
	init();
}

void Game::update()
{
	currentFrame++;
	currentFrame %= 60;

	if (shootCooldown > 0)
	{
		shootCooldown--;
	}

	scoreString = "Score: " + to_string(score);
	scoreText.setString(scoreString);

	entityManager.update();
	userInputSystem();
	movementSystem();
	collisionSystem();
	enemySpawnSystem();
	lifespanSystem();
	renderSystem();
}

void Game::movementSystem()
{
	if (player->cInput) {
		if (player->cInput->up)
		{
			player->cTransform->velocity.y = -speed;
		}
		else if (player->cInput->down)
		{
			player->cTransform->velocity.y = speed;
		}
		else
		{
			player->cTransform->velocity.y = 0;
		}

		if (player->cInput->left)
		{
			player->cTransform->velocity.x = -speed;
		}
		else if (player->cInput->right)
		{
			player->cTransform->velocity.x = speed;
		}
		else
		{
			player->cTransform->velocity.x = 0;
		}

		if (player->cTransform->velocity.x != 0 && player->cTransform->velocity.y != 0)
		{
			player->cTransform->velocity.x *= 0.71;
			player->cTransform->velocity.y *= 0.71;
		}
	}

	if (player->cTransform && player->cShape)
	{
		player->cTransform->pos += player->cTransform->velocity;
		player->cShape->circle.setPosition(player->cTransform->pos);

		player->cTransform->increaseAngle();
		player->cShape->circle.setRotation(player->cTransform->angle);

		// Window border collision for player

		if (player->cTransform->pos.x < player->cCollision->radius)
		{
			player->cTransform->pos.x = player->cCollision->radius;
		}
		else if (player->cTransform->pos.x > window.getSize().x - player->cCollision->radius)
		{
			player->cTransform->pos.x = window.getSize().x - player->cCollision->radius;
		}

		if (player->cTransform->pos.y < player->cCollision->radius)
		{
			player->cTransform->pos.y = player->cCollision->radius;
		}
		else if (player->cTransform->pos.y > window.getSize().y - player->cCollision->radius)
		{
			player->cTransform->pos.y = window.getSize().y - player->cCollision->radius;
		}
	}
		
	for (auto e : entityManager.getEntities("enemy"))
	{
		if (e->cTransform && e->cShape)
		{
			e->cTransform->pos += e->cTransform->velocity;
			e->cShape->circle.setPosition(e->cTransform->pos);

			e->cTransform->increaseAngle();
			e->cShape->circle.setRotation(e->cTransform->angle);
		}

		// Window border collision for enemies

		if (!e->cCollision)
			continue;

		if (e->cTransform->pos.x < e->cCollision->radius)
		{
			e->cTransform->velocity.x *= -1;
		}
		else if (e->cTransform->pos.x > window.getSize().x - e->cCollision->radius)
		{
			e->cTransform->velocity.x *= -1;
		}

		if (e->cTransform->pos.y < e->cCollision->radius)
		{
			e->cTransform->velocity.y *= -1;
		}
		else if (e->cTransform->pos.y > window.getSize().y - e->cCollision->radius)
		{
			e->cTransform->velocity.y *= -1;
		}
	}

	for (auto e : entityManager.getEntities("bullet"))
	{
		if (e->cTransform && e->cShape)
		{
			e->cTransform->pos += e->cTransform->velocity;
			e->cShape->circle.setPosition(e->cTransform->pos);
		}
	}
}

void Game::collisionSystem()
{
	for (auto e : entityManager.getEntities("enemy")) {
		for (auto b : entityManager.getEntities("bullet")) {
			if (isColliding(b, e))
			{
				spawnSmallEnemies(e);

				b->destroy();
				e->destroy();
				nrOfEnemies--;

				score += 10 * e->cShape->circle.getPointCount();
			}
		}

		// Player collision with enemies
		if (isColliding(player, e))
		{
			e->destroy();
			nrOfEnemies--;

			player->cTransform->pos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
		}
	}
}

void Game::userInputSystem()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			case sf::Keyboard::W:
				player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				player->cInput->right = true;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				player->cInput->right = false;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (shootCooldown == 0 && event.mouseButton.button == sf::Mouse::Left) {
				shootCooldown = 20;
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				spawnBullet(player, mousePos);
			}
		}
	}
}

void Game::renderSystem()
{
	window.clear();

	for (auto e : entityManager.getEntities())
	{
		if (e->cShape)
		{
			window.draw(e->cShape->circle);
		}
	}

	window.draw(scoreText);

	window.display();
}

void Game::enemySpawnSystem()
{
	if (nrOfEnemies < maxNrOfEnemies && currentFrame == 0)
	{
		spawnEnemy();
		nrOfEnemies++;
	}
}

void Game::lifespanSystem()
{
	for (auto e : entityManager.getEntities())
	{
		if (e->cLifespan)
		{
			e->cLifespan->remaining--;
			if (e->cLifespan->remaining <= 0)
			{
				e->destroy();
			}

			if (e->cShape && e->cLifespan->remaining <= 50)
			{
				e->cShape->circle.setFillColor(sf::Color(e->cShape->circle.getFillColor().r, e->cShape->circle.getFillColor().g, e->cShape->circle.getFillColor().b, 55 + e->cLifespan->remaining * 4));
				e->cShape->circle.setOutlineColor(sf::Color(e->cShape->circle.getOutlineColor().r, e->cShape->circle.getOutlineColor().g, e->cShape->circle.getOutlineColor().b, 55 + e->cLifespan->remaining * 4));
			}
		}
	}
}

void Game::spawnPlayer()
{
	auto entity = entityManager.addEntity("player");

	entity->cTransform = make_shared<CTransform>(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), sf::Vector2f(0, 0), 0);

	entity->cShape = make_shared<CShape>(70, 6, sf::Color::Green, sf::Color::White, 2);

	entity->cInput = make_shared<CInput>();

	entity->cCollision = make_shared<CCollision>(entity->cShape->circle.getRadius());

	player = entity;
}

void Game::spawnEnemy()
{
	auto entity = entityManager.addEntity("enemy");

	int radius = 40 + rand() % 20;
	int sides = 3 + rand() % 8;

	int x = radius + rand() % (window.getSize().x - 2 * radius);
	int y = radius + rand() % (window.getSize().y - 2 * radius);

	int vx = -8 + rand() % 17 + 0.1;
	int vy = -8 + rand() % 17 + 0.1;

	auto color1 = sf::Color(rand() % 256, rand() % 256, rand() % 256);
	auto color2 = sf::Color::White;

	entity->cTransform = make_shared<CTransform>(sf::Vector2f(x, y), sf::Vector2f(vx, vy), 0);

	entity->cShape = make_shared<CShape>(radius, sides, color1, color2, 2);

	entity->cCollision = make_shared<CCollision>(radius);
}

void Game::spawnSmallEnemies(shared_ptr<Entity> entity)
{
	for (int i = 0; i < entity->cShape->circle.getPointCount(); i++)
	{
		auto smallEnemy = entityManager.addEntity("enemy");

		sf::Vector2f pos = entity->cTransform->pos;

		sf::Vector2f velocity = sf::Vector2f(cos(2 * 3.14159265359 * i / entity->cShape->circle.getPointCount()), sin(2 * 3.14159265359 * i / entity->cShape->circle.getPointCount()));

		smallEnemy->cTransform = make_shared<CTransform>(pos, velocity, 0);

		smallEnemy->cShape = make_shared<CShape>(20,
			entity->cShape->circle.getPointCount(),
			sf::Color(entity->cShape->circle.getFillColor().r, entity->cShape->circle.getFillColor().g, entity->cShape->circle.getFillColor().b),
			sf::Color(entity->cShape->circle.getFillColor().r, entity->cShape->circle.getFillColor().g, entity->cShape->circle.getFillColor().b),
			2);

		smallEnemy->cLifespan = make_shared<CLifespan>(90);
	}
}

void Game::spawnBullet(shared_ptr<Entity> entity, sf::Vector2f& mousePos)
{
	auto bullet = entityManager.addEntity("bullet");

	// Determine velocity

	sf::Vector2f direction = mousePos - entity->cTransform->pos;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	direction.x /= length;
	direction.y /= length;

	direction.x *= 12;
	direction.y *= 12;


	bullet->cTransform = make_shared<CTransform>(entity->cTransform->pos, direction, 0);

	bullet->cShape = make_shared<CShape>(25, 18, sf::Color::White, sf::Color::White, 2);

	bullet->cCollision = make_shared<CCollision>(bullet->cShape->circle.getRadius());

	bullet->cLifespan = make_shared<CLifespan>(50);
}

bool Game::isColliding(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2)
{
	if (entity1->cCollision && entity2->cCollision)
	{
		sf::Vector2f distanceVector = entity1->cTransform->pos - entity2->cTransform->pos;

		float distance = distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y;

		if (distance < (entity1->cCollision->radius + entity2->cCollision->radius) * (entity1->cCollision->radius + entity2->cCollision->radius))
		{
			return true;
		}
	}
	return false;
}

void Game::run()
{
	while (window.isOpen())
	{
		update();
	}
}