#include "Platform.h"

Platform::Platform(sf::Texture* texture)
{
	setTexture(*texture);

	this->scale(0.109f, 0.109f);
}
