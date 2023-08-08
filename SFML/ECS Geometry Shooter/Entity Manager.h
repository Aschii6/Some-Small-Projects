#pragma once
#include "Entity.h"
#include <vector>
#include <map>

typedef vector<shared_ptr<Entity>> EntityVec;
typedef map<string, EntityVec> EntityMap;


class EntityManager {
	EntityVec entities;

	EntityVec toAdd;

	EntityMap entityMap;
	unsigned int totalEntities = 0;

public:
	EntityManager();

	void update();

	shared_ptr<Entity> addEntity(string tag);

	EntityVec& getEntities();

	EntityVec& getEntities(string tag);
};