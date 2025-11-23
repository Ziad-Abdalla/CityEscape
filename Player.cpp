#include "Player.h"
#include <glut.h>
#include <math.h>

Player::Player(Model_3DS* model) {
	carModel = model;
	position = Vector3f(0, 0, 0);
	rotation = Vector3f(0, 0, 0);
	speed = 10.0f; // units per second
	turnSpeed = 90.0f; // degrees per second
	boundingRadius = 2.0f; // Adjust based on car size

	isFlashing = false;
	flashTime = 0.0f;
	flashDuration = 0.5f; // Flash for 0.5 seconds on collision
}

Player::~Player() {
	// Model is managed elsewhere, don't delete here
}

void Player::update(float deltaTime) {
	// Update collision flash
	if (isFlashing) {
		flashTime += deltaTime;
		if (flashTime >= flashDuration) {
			isFlashing = false;
			flashTime = 0.0f;
		}
	}
}

void Player::render() {
	if (!carModel) return;

	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.z, 0, 0, 1);

		// Apply red flash effect if colliding
		if (isFlashing) {
			GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
		}

		carModel->Draw();

		// Reset material after drawing
		if (isFlashing) {
			GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
		}
	glPopMatrix();
}

void Player::moveForward(float amount) {
	float angleRad = rotation.y * 3.14159f / 180.0f;
	position.x += sin(angleRad) * amount;
	position.z += cos(angleRad) * amount;
}

void Player::moveBackward(float amount) {
	moveForward(-amount);
}

void Player::turnLeft(float amount) {
	rotation.y += amount;
	if (rotation.y >= 360.0f) rotation.y -= 360.0f;
}

void Player::turnRight(float amount) {
	rotation.y -= amount;
	if (rotation.y < 0.0f) rotation.y += 360.0f;
}

Vector3f Player::getFirstPersonCameraPos() {
	// Camera inside car, slightly above and forward
	float angleRad = rotation.y * 3.14159f / 180.0f;
	float offsetX = sin(angleRad) * 1.0f;
	float offsetZ = cos(angleRad) * 1.0f;
	return Vector3f(position.x + offsetX, position.y + 1.5f, position.z + offsetZ);
}

Vector3f Player::getFirstPersonCameraLookAt() {
	// Look forward from car
	float angleRad = rotation.y * 3.14159f / 180.0f;
	float lookX = sin(angleRad) * 10.0f;
	float lookZ = cos(angleRad) * 10.0f;
	return Vector3f(position.x + lookX, position.y + 1.5f, position.z + lookZ);
}

Vector3f Player::getThirdPersonCameraPos() {
	// Camera behind and above car
	float angleRad = rotation.y * 3.14159f / 180.0f;
	float offsetX = sin(angleRad) * -8.0f; // Behind the car
	float offsetZ = cos(angleRad) * -8.0f;
	return Vector3f(position.x + offsetX, position.y + 4.0f, position.z + offsetZ);
}

Vector3f Player::getThirdPersonCameraLookAt() {
	// Look at the car
	return Vector3f(position.x, position.y + 1.0f, position.z);
}

void Player::triggerCollisionFlash() {
	isFlashing = true;
	flashTime = 0.0f;
}
