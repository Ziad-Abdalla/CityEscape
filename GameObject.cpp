#include "GameObject.h"
#include <glut.h>
#include <math.h>

// GameObject Base Class Implementation
GameObject::GameObject(Model_3DS* m, ObjectType t, Vector3f pos) {
	model = m;
	type = t;
	position = pos;
	rotation = Vector3f(0, 0, 0);
	scale = Vector3f(1, 1, 1);
	isActive = true;
	boundingRadius = 2.0f; // Default radius, adjust per object
}

GameObject::~GameObject() {
	// Model is managed elsewhere, don't delete here
}

void GameObject::render() {
	if (!isActive || !model) return;

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glScalef(scale.x, scale.y, scale.z);
		model->Draw();
	glPopMatrix();
}

void GameObject::onCollision() {
	// Base implementation - override in derived classes
}

bool GameObject::checkCollision(GameObject* other) {
	if (!isActive || !other->getActive()) return false;

	Vector3f otherPos = other->getPosition();
	float dx = position.x - otherPos.x;
	float dy = position.y - otherPos.y;
	float dz = position.z - otherPos.z;
	float distance = sqrt(dx * dx + dy * dy + dz * dz);

	return distance < (boundingRadius + other->getBoundingRadius());
}

// Obstacle Implementation
Obstacle::Obstacle(Model_3DS* model, Vector3f position, int penalty)
	: GameObject(model, OBSTACLE, position) {
	scorePenalty = penalty;
	boundingRadius = 1.5f; // Adjust based on obstacle size
}

void Obstacle::update(float deltaTime) {
	// Obstacles are static, no update needed
	// Can add animations here later (e.g., rotating barrels)
}

void Obstacle::onCollision() {
	// Collision feedback - can add sound, effects here
	// Score reduction handled in main game logic
}

// Collectible Implementation
Collectible::Collectible(Model_3DS* model, Vector3f position, int score)
	: GameObject(model, COLLECTIBLE, position) {
	scoreValue = score;
	rotationSpeed = 90.0f; // degrees per second
	currentRotation = 0.0f;
	isBeingCollected = false;
	collectionTime = 0.0f;
	boundingRadius = 1.0f; // Smaller radius for collectibles
}

void Collectible::update(float deltaTime) {
	if (!isActive) return;

	// Rotate collectible continuously
	currentRotation += rotationSpeed * deltaTime;
	if (currentRotation >= 360.0f) {
		currentRotation -= 360.0f;
	}
	rotation.y = currentRotation;

	// If being collected, play animation
	if (isBeingCollected) {
		collectionTime += deltaTime;

		// Scale up animation (0.5 seconds)
		if (collectionTime < 0.5f) {
			float scaleFactor = 1.0f + (collectionTime * 2.0f); // Scale from 1.0 to 2.0
			scale = Vector3f(scaleFactor, scaleFactor, scaleFactor);
		} else {
			// Animation complete, deactivate
			isActive = false;
		}
	}
}

void Collectible::onCollision() {
	// Start collection animation
	playCollectionAnimation();
}

void Collectible::playCollectionAnimation() {
	isBeingCollected = true;
	collectionTime = 0.0f;
	// Sound would be played here
}
