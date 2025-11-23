#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model_3DS.h"
#include "Camera.h"

enum ObjectType {
	OBSTACLE,
	COLLECTIBLE,
	ENVIRONMENT
};

class GameObject {
protected:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;
	Model_3DS* model;
	ObjectType type;
	bool isActive;
	float boundingRadius;

public:
	GameObject(Model_3DS* model, ObjectType type, Vector3f pos = Vector3f(0, 0, 0));
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void render();
	virtual void onCollision();

	bool checkCollision(GameObject* other);

	Vector3f getPosition() { return position; }
	float getBoundingRadius() { return boundingRadius; }
	bool getActive() { return isActive; }
	void setActive(bool active) { isActive = active; }
	void setPosition(Vector3f pos) { position = pos; }
	void setRotation(Vector3f rot) { rotation = rot; }
	void setScale(Vector3f s) { scale = s; }
};

class Obstacle : public GameObject {
private:
	int scorePenalty;

public:
	Obstacle(Model_3DS* model, Vector3f position, int penalty = 10);
	void update(float deltaTime) override;
	void onCollision() override;
};

class Collectible : public GameObject {
private:
	int scoreValue;
	float rotationSpeed;
	float currentRotation;
	bool isBeingCollected;
	float collectionTime;

public:
	Collectible(Model_3DS* model, Vector3f position, int score = 10);
	void update(float deltaTime) override;
	void onCollision() override;
	void playCollectionAnimation();
};

#endif
