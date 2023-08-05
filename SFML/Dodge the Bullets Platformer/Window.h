#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include <vector>

using std::vector;

class Window :
    public sf::RenderWindow
{
    sf::Event event;

    Player* player;

    vector<vector<int>> layout;

    vector<Platform*> platforms;

    vector<sf::CircleShape*> bullets;

    int maxNrOfBullets;
    int nrOfBullets;

    sf::Texture brickTexture;
public:
    Window();

    void update();
    void render();
    void handleEvents();
    void handleInputs();
    void handleCollisionsWithWindow();
    void handleCollisionsWithPlatforms();
    void handleCollisionsWithBullets();
};

