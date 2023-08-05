#include "Window.h"
#include <iostream>

Window::Window()
{
	create(sf::VideoMode(1200, 800), "Yokoso!", sf::Style::Close);

	setFramerateLimit(60);

	setVerticalSyncEnabled(true);

	

	player = new Player();

	player->setPosition(550, 550);

	brickTexture.loadFromFile("Resources/mario-brick.png");

	layout = vector<vector<int>>(12, vector<int>(8, 0));

	for (int i = 0; i < 8; i++)
	{
		layout[0][i] = 1;
		layout[11][i] = 1;
	}

	layout[7][6] = 1;
	layout[8][6] = 1;
	layout[9][6] = 1;

	layout[2][4] = 1;
	layout[3][4] = 1;
	layout[4][4] = 1;

	layout[7][2] = 1;
	layout[8][2] = 1;
	layout[9][2] = 1;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (layout[i][j] == 1)
			{
				Platform* platform = new Platform(&brickTexture);

				platform->setPosition(i * 100, j * 100);

				platforms.push_back(platform);
			}
		}
	}

	maxNrOfBullets = 3;
	nrOfBullets = 0;
}

void Window::update()
{
	player->update();

	// Create bullets;

	if (nrOfBullets < maxNrOfBullets)
	{
		int chance = rand() % 60;
		if (chance < 4)
		{
			std::cout << "Bullet created\n";

			sf::CircleShape* bullet = new sf::CircleShape(30.f);
			bullet->setFillColor(sf::Color(83, 83, 83));
			bullet->setOutlineColor(sf::Color::Black);
			bullet->setOutlineThickness(2);

			bullet->setPosition(0, rand() % 720);

			bullets.push_back(bullet);

			nrOfBullets++;
		}
	}

	// Move and/or Destroy bullets

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->move(6.5f, 0.f);

		if (bullets[i]->getPosition().x + 30 > this->getSize().x)
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;

			nrOfBullets--;
		}
	}
}

void Window::render()
{
	clear(sf::Color(173, 216, 210));

	for (int i = 0; i < platforms.size(); i++)
	{
		draw(*platforms[i]);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		draw(*bullets[i]);
	}

	draw(*player);

	display();
}

void Window::handleEvents()
{
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			close();	
	}
}

void Window::handleInputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->jump();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->moveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->moveRight();
	}
}

void Window::handleCollisionsWithWindow()
{
	if (player->getPosition().x < player->getGlobalBounds().width)
	{
		player->setPosition(player->getGlobalBounds().width, player->getPosition().y);
	}
	else if (player->getPosition().x + player->getGlobalBounds().width > this->getSize().x)
	{
		player->setPosition(this->getSize().x - player->getGlobalBounds().width, player->getPosition().y);
	}

	if (player->getPosition().y < 0)
	{
		player->setPosition(player->getPosition().x, 0);
		player->setVerticalVelocityZero();
	}
	else if (player->getPosition().y > this->getSize().y - player->getGlobalBounds().height - 15)
	{
		player->setPosition(player->getPosition().x, this->getSize().y - player->getGlobalBounds().height - 15);
		player->setTouchingGround(true);
	}
}

void Window::handleCollisionsWithPlatforms()
{
	for (auto& platform : platforms)
	{
		if (player->getGlobalBounds().intersects(platform->getGlobalBounds()))
		{
			auto playerPos = player->getPosition();
			auto platformPos = platform->getPosition();

			auto playerBounds = player->getGlobalBounds();
			auto platformBounds = platform->getGlobalBounds();

			bool touchingFromUpOrDown = false;

			// Up side
			if (playerPos.y + playerBounds.height > platformPos.y && playerPos.y + playerBounds.height < platformPos.y + 26)
			{
				touchingFromUpOrDown = true;
				player->setPosition(playerPos.x, platformPos.y - playerBounds.height);
				player->setTouchingGround(true);
				player->setVerticalVelocityZero();
			}

			// Down side
			else if (playerPos.y < platformPos.y + platformBounds.height && playerPos.y > platformPos.y + platformBounds.height - 26)
			{
				touchingFromUpOrDown = true;
				player->setPosition(playerPos.x, platformPos.y + platformBounds.height);
				player->setVerticalVelocityZero();
			}

			// Left side of platform
			if (!touchingFromUpOrDown && playerPos.x + playerBounds.width > platformPos.x && playerPos.x + playerBounds.width < platformPos.x + 16)
			{
				player->setPosition(platformPos.x - playerBounds.width, playerPos.y);
			}

			// Right side
			else if (!touchingFromUpOrDown && playerPos.x - playerBounds.width < platformPos.x + platformBounds.width && playerPos.x - playerBounds.width > platformPos.x + platformBounds.width - 16)
			{
				player->setPosition(platformPos.x + platformBounds.width + playerBounds.width, playerPos.y);
			}
		}
	}
}

void Window::handleCollisionsWithBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (player->getGlobalBounds().intersects(bullets[i]->getGlobalBounds()))
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;

			nrOfBullets--;
		}
	}
}
