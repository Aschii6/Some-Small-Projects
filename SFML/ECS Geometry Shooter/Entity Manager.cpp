#pragma once
#include "Entity Manager.h"
#include <iostream>


EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	for (auto e : toAdd)
	{
		entities.push_back(e);
		entityMap[e->getTag()].push_back(e);
	}
	toAdd.clear();


	entities.erase(remove_if(entities.begin(), entities.end(), [](shared_ptr<Entity> e) { return !e->isAlive(); }), entities.end());

	for (auto& pair : entityMap)
	{
		pair.second.erase(remove_if(pair.second.begin(), pair.second.end(), [](shared_ptr<Entity> e) { return !e->isAlive(); }), pair.second.end());
	}
}

shared_ptr<Entity> EntityManager::addEntity(string tag)
{
	auto e = shared_ptr<Entity>(new Entity(totalEntities++, tag));
	toAdd.push_back(e);
	return e;
}

EntityVec& EntityManager::getEntities()
{
	return entities;
}

EntityVec& EntityManager::getEntities(string tag)
{
	return entityMap[tag];
}
