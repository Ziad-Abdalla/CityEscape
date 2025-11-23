#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <glut.h>

#define DEG2RAD(a) (a * 0.0174532925)

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);

	Vector3f operator+(Vector3f &v);
	Vector3f operator-(Vector3f &v);
	Vector3f operator*(float n);
	Vector3f operator/(float n);
	Vector3f unit();
	Vector3f cross(Vector3f v);
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f,
	       float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f,
	       float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f);

	void moveX(float d);
	void moveY(float d);
	void moveZ(float d);
	void rotateX(float a);
	void rotateY(float a);
	void look();
};

#endif
