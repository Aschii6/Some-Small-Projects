#pragma once
#include "Components.h"
#include "Entity Manager.h"
#include <memory>


class Entity {
	friend class EntityManager;

	unsigned int id = 0;
	string tag = "Default";
	bool alive = true;

	Entity(unsigned int i, string t) : id(i), tag(t) {}
public:
	shared_ptr<CTransform> cTransform;
	shared_ptr<CShape> cShape;
	shared_ptr<CCollision> cCollision;
	shared_ptr<CInput> cInput;
	shared_ptr<CScore> cScore;
	shared_ptr<CLifespan> cLifespan;

	void destroy() {
		alive = false;
	}

	bool isAlive() {
		return alive;
	}

	unsigned int getId() {
		return id;
	}

	string getTag() {
		return tag;
	}
};