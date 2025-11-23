#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include "Camera.h"
#include "Player.h"
#include "GameObject.h"
#include <glut.h>
#include <stdio.h>
#include <vector>
#include <cmath>

int WIDTH = 1280;
int HEIGHT = 720;

GLuint tex;
char title[] = "City Escape 3D";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;

// Camera
Camera camera(20, 5, 20, 0, 0, 0, 0, 1, 0);
bool firstPersonView = false;

// Model Variables
Model_3DS model_jeep;
Model_3DS model_barrel;
Model_3DS model_cone;
Model_3DS model_fuelcan;
Model_3DS model_streetlight;

// Player
Player* player = NULL;

// Game Objects
std::vector<Obstacle*> obstacles;
std::vector<Collectible*> collectibles;

// Game State
int score = 0;
float deltaTime = 0.0f;
int lastTime = 0;

// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	camera.look();
	//*******************************************************************************************//
	// Using Camera class from Lab 6 Solution for improved camera control						 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// HUD Rendering Function
//=======================================================================
void RenderHUD()
{
	// Switch to orthographic projection for 2D HUD
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Disable lighting for HUD
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Set HUD text color (white)
	glColor3f(1.0f, 1.0f, 1.0f);

	// Display score
	char scoreText[50];
	sprintf(scoreText, "Score: %d", score);
	glRasterPos2f(20, HEIGHT - 30);
	for (int i = 0; scoreText[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreText[i]);
	}

	// Display controls hint
	glRasterPos2f(20, HEIGHT - 60);
	const char* controls = "WASD: Move | Right-Click: Change Camera";
	for (int i = 0; controls[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, controls[i]);
	}

	// Re-enable lighting and depth test
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Restore projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//=======================================================================
// Update Function (Game Loop)
//=======================================================================
void myUpdate(int value)
{
	// Calculate delta time
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
	lastTime = currentTime;

	// Update player
	if (player) {
		player->update(deltaTime);
	}

	// Update all obstacles
	for (size_t i = 0; i < obstacles.size(); i++) {
		obstacles[i]->update(deltaTime);
	}

	// Update all collectibles
	for (size_t i = 0; i < collectibles.size(); i++) {
		collectibles[i]->update(deltaTime);
	}

	// Collision detection - player vs obstacles
	if (player) {
		for (size_t i = 0; i < obstacles.size(); i++) {
			if (obstacles[i]->getActive()) {
				Vector3f playerPos = player->getPosition();
				Vector3f obstaclePos = obstacles[i]->getPosition();
				float dx = playerPos.x - obstaclePos.x;
				float dz = playerPos.z - obstaclePos.z;
				float distance = sqrt(dx * dx + dz * dz);

				if (distance < (player->getBoundingRadius() + obstacles[i]->getBoundingRadius())) {
					// Collision detected!
					player->triggerCollisionFlash();
					obstacles[i]->onCollision();
					score -= 10; // Penalty
					printf("Collision with obstacle! Score: %d\n", score);
				}
			}
		}

		// Collision detection - player vs collectibles
		for (size_t i = 0; i < collectibles.size(); i++) {
			if (collectibles[i]->getActive()) {
				Vector3f playerPos = player->getPosition();
				Vector3f collectiblePos = collectibles[i]->getPosition();
				float dx = playerPos.x - collectiblePos.x;
				float dz = playerPos.z - collectiblePos.z;
				float distance = sqrt(dx * dx + dz * dz);

				if (distance < (player->getBoundingRadius() + collectibles[i]->getBoundingRadius())) {
					// Collectible picked up!
					collectibles[i]->onCollision();
					score += 10; // Reward
					printf("Collected item! Score: %d\n", score);
				}
			}
		}
	}

	// Request redraw
	glutPostRedisplay();

	// Call update again after 16ms (approximately 60 FPS)
	glutTimerFunc(16, myUpdate, 0);
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Update camera to follow player
	if (player) {
		Vector3f camPos, camLookAt;
		if (firstPersonView) {
			camPos = player->getFirstPersonCameraPos();
			camLookAt = player->getFirstPersonCameraLookAt();
		} else {
			camPos = player->getThirdPersonCameraPos();
			camLookAt = player->getThirdPersonCameraLookAt();
		}
		camera.eye = camPos;
		camera.center = camLookAt;
	}

	camera.look();

	GLfloat lightIntensity[] = { 0.7, 0.7, 0.7, 1.0f };
	GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);

	// Draw Ground
	RenderGround();

	// Draw Player Car
	if (player) {
		player->render();
	}

	// Draw all obstacles
	for (size_t i = 0; i < obstacles.size(); i++) {
		obstacles[i]->render();
	}

	// Draw all collectibles
	for (size_t i = 0; i < collectibles.size(); i++) {
		collectibles[i]->render();
	}


	//sky box
	glPushMatrix();

	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	// Draw HUD
	RenderHUD();

	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	if (!player) return;

	float speed = 0.5f;
	float turnSpeed = 5.0f;

	switch (button)
	{
	case 'w':
	case 'W':
		player->moveForward(speed);
		break;
	case 's':
	case 'S':
		player->moveBackward(speed);
		break;
	case 'a':
	case 'A':
		player->turnLeft(turnSpeed);
		break;
	case 'd':
	case 'D':
		player->turnRight(turnSpeed);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Special Keys Function (Arrow keys)
//=======================================================================
void mySpecial(int key, int x, int y)
{
	float a = 2.0;

	switch (key)
	{
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// Toggle camera view (first-person / third-person)
		firstPersonView = !firstPersonView;
		printf("Camera switched to %s view\n", firstPersonView ? "First-Person" : "Third-Person");
	}

	glutPostRedisplay();
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	printf("Loading models...\n");
	model_jeep.Load("models/player/Jeep/Jeep.3ds");
	model_barrel.Load("models/obstacles/barrel2/barrel2.3DS");
	model_cone.Load("models/obstacles/TrafficCone/TrafficCone.3DS");
	model_fuelcan.Load("models/collectibles/FeulCan/FeulCan.3DS");
	printf("Models loaded successfully!\n");

	// Initialize Player
	player = new Player(&model_jeep);
	printf("Player initialized!\n");

	// Create obstacles - place barrels and cones along the scene
	printf("Creating obstacles...\n");

	// Barrels on the right side
	obstacles.push_back(new Obstacle(&model_barrel, Vector3f(10, 0, 0), 10));
	obstacles.push_back(new Obstacle(&model_barrel, Vector3f(12, 0, -8), 10));
	obstacles.push_back(new Obstacle(&model_barrel, Vector3f(8, 0, -16), 10));

	// Traffic cones on the left side
	obstacles.push_back(new Obstacle(&model_cone, Vector3f(-10, 0, 0), 10));
	obstacles.push_back(new Obstacle(&model_cone, Vector3f(-12, 0, -8), 10));
	obstacles.push_back(new Obstacle(&model_cone, Vector3f(-8, 0, -16), 10));

	// More obstacles ahead
	obstacles.push_back(new Obstacle(&model_barrel, Vector3f(5, 0, 10), 10));
	obstacles.push_back(new Obstacle(&model_cone, Vector3f(-5, 0, 10), 10));

	// Set scale for obstacles
	for (size_t i = 0; i < obstacles.size(); i++) {
		obstacles[i]->setScale(Vector3f(0.5f, 0.5f, 0.5f));
	}
	printf("Created %d obstacles!\n", (int)obstacles.size());

	// Create collectibles - place fuel cans throughout the scene
	printf("Creating collectibles...\n");

	collectibles.push_back(new Collectible(&model_fuelcan, Vector3f(0, 0, 5), 10));
	collectibles.push_back(new Collectible(&model_fuelcan, Vector3f(3, 0, -5), 10));
	collectibles.push_back(new Collectible(&model_fuelcan, Vector3f(-3, 0, -10), 10));
	collectibles.push_back(new Collectible(&model_fuelcan, Vector3f(6, 0, 8), 10));
	collectibles.push_back(new Collectible(&model_fuelcan, Vector3f(-6, 0, -2), 10));

	// Set scale for collectibles
	for (size_t i = 0; i < collectibles.size(); i++) {
		collectibles[i]->setScale(Vector3f(0.5f, 0.5f, 0.5f));
	}
	printf("Created %d collectibles!\n", (int)collectibles.size());

	// Loading texture files
	printf("Loading textures...\n");
	tex_ground.Load("textures/ground.bmp");
	loadBMP(&tex, "textures/blu-sky-3.bmp", true);
	printf("Textures loaded successfully!\n");
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);

	glutSpecialFunc(mySpecial);

	glutMouseFunc(myMouse);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	// Initialize timer for game loop
	lastTime = glutGet(GLUT_ELAPSED_TIME);
	glutTimerFunc(0, myUpdate, 0);

	glutMainLoop();
}