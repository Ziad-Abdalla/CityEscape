#ifndef PLAYER_H
#define PLAYER_H

#include "Model_3DS.h"
#include "Camera.h"

class Player {
private:
	Vector3f position;
	Vector3f rotation;
	float speed;
	float turnSpeed;
	Model_3DS* carModel;
	float boundingRadius;

	// Collision feedback
	bool isFlashing;
	float flashTime;
	float flashDuration;

public:
	Player(Model_3DS* model);
	~Player();

	void update(float deltaTime);
	void render();

	void moveForward(float amount);
	void moveBackward(float amount);
	void turnLeft(float amount);
	void turnRight(float amount);

	Vector3f getPosition() { return position; }
	Vector3f getRotation() { return rotation; }
	float getBoundingRadius() { return boundingRadius; }

	// Camera position helpers
	Vector3f getFirstPersonCameraPos();
	Vector3f getFirstPersonCameraLookAt();
	Vector3f getThirdPersonCameraPos();
	Vector3f getThirdPersonCameraLookAt();

	// Collision feedback
	void triggerCollisionFlash();
	bool isCollisionFlashing() { return isFlashing; }
};

#endif
