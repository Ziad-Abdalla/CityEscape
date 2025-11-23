#include <stdio.h>
#include "Model_3DS.h"
#include <glut.h>

int WIDTH = 1280;
int HEIGHT = 720;

// Simple camera position
float camX = 0, camY = 5, camZ = 20;
float lookX = 0, lookY = 0, lookZ = 0;

// Test model
Model_3DS testModel;
bool modelLoaded = false;

void init() {
    glClearColor(0.5, 0.7, 1.0, 1.0); // Light blue sky
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // Simple white light
    GLfloat ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat pos[] = { 0.0, 10.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void loadModel() {
    printf("Attempting to load model...\n");
    printf("Working directory should contain 'models' folder\n");

    // Try to load the Jeep model
    testModel.Load("models/player/Jeep/Jeep.3ds");

    // Model_3DS::Load() doesn't return a value, so we assume success
    printf("Model load command executed\n");
    modelLoaded = true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WIDTH / (double)HEIGHT, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);

    // Draw ground (green plane)
    glDisable(GL_LIGHTING);
    glColor3f(0.3, 0.8, 0.3);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-50, 0, -50);
        glVertex3f(50, 0, -50);
        glVertex3f(50, 0, 50);
        glVertex3f(-50, 0, 50);
    glEnd();
    glEnable(GL_LIGHTING);

    // Draw reference cube at origin (red)
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(2.0);
    glPopMatrix();

    // Try to draw the model
    if (modelLoaded) {
        glPushMatrix();
        glTranslatef(5, 0, 0); // To the right of the cube
        glScalef(1.0, 1.0, 1.0); // Try different scales if needed
        glColor3f(1.0, 1.0, 1.0); // White color
        testModel.Draw();
        glPopMatrix();
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w': camZ -= 1.0; break;
        case 's': camZ += 1.0; break;
        case 'a': camX -= 1.0; break;
        case 'd': camX += 1.0; break;
        case 'q': camY += 1.0; break;
        case 'e': camY -= 1.0; break;
        case 'r':
            printf("Reloading model...\n");
            loadModel();
            break;
        case 27:
            printf("ESC pressed - exiting\n");
            exit(0);
    }
    printf("Camera: (%.1f, %.1f, %.1f)\n", camX, camY, camZ);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Model Loading Test");

    init();
    loadModel();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("\n=== MODEL LOADING TEST ===\n");
    printf("Controls: WASD to move camera, Q/E for up/down\n");
    printf("          R to reload model, ESC to exit\n");
    printf("Expected: Green ground, Red cube (center), Jeep model (right)\n\n");

    glutMainLoop();
    return 0;
}
