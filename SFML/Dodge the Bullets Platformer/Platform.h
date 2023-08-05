#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Platform: public sf::Sprite
{
private:
	sf::Texture texture;
public:
	Platform(sf::Texture* texture);
};

