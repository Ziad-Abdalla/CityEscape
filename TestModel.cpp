#include <stdio.h>
#include <glew.h>  // MUST be included before any other OpenGL headers
#include <glut.h>
#include "Model_3DS.h"
#include "Camera.h"
#include "GLTexture.h"
#include "TextureBuilder.h"

int WIDTH = 1280;
int HEIGHT = 720;

// Camera using Camera class from Lab 6 Solution
Camera camera(0, 5, 20, 0, 0, 0, 0, 1, 0);

// Test model
Model_3DS testModel;
bool modelLoaded = false;

// Ground texture
GLTexture tex_ground;

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

void loadAssets() {
    printf("Loading assets...\n");
    printf("Working directory should contain 'models' and 'textures' folders\n");

    // Load the Jeep model
    testModel.Load("models/player/Jeep/Jeep.3ds");
    printf("Jeep model loaded\n");
    modelLoaded = true;

    // Load ground texture
    tex_ground.Load("textures/ground.bmp");
    printf("Ground texture loaded\n");
}

// Render textured ground (from CityEscape.cpp)
void renderGround() {
    glDisable(GL_LIGHTING);  // Disable lighting for ground

    glColor3f(0.6, 0.6, 0.6);  // Dim the ground texture a bit

    glEnable(GL_TEXTURE_2D);  // Enable 2D texturing

    glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]);  // Bind the ground texture

    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);  // Set quad normal direction
    glTexCoord2f(0, 0);   // Texture coordinates with wrapping
    glVertex3f(-50, 0, -50);
    glTexCoord2f(5, 0);
    glVertex3f(50, 0, -50);
    glTexCoord2f(5, 5);
    glVertex3f(50, 0, 50);
    glTexCoord2f(0, 5);
    glVertex3f(-50, 0, 50);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);  // Disable texturing
    glEnable(GL_LIGHTING);     // Re-enable lighting for other objects

    glColor3f(1, 1, 1);  // Reset color to white
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)WIDTH / (double)HEIGHT, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera.look();

    // Draw textured ground
    renderGround();

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
    float moveSpeed = 1.0f;

    switch(key) {
        case 'w': camera.moveZ(moveSpeed); break;
        case 's': camera.moveZ(-moveSpeed); break;
        case 'a': camera.moveX(moveSpeed); break;
        case 'd': camera.moveX(-moveSpeed); break;
        case 'q': camera.moveY(moveSpeed); break;
        case 'e': camera.moveY(-moveSpeed); break;
        case 'r':
            printf("Reloading assets...\n");
            loadAssets();
            break;
        case 27:
            printf("ESC pressed - exiting\n");
            exit(0);
    }
    printf("Camera: (%.1f, %.1f, %.1f)\n", camera.eye.x, camera.eye.y, camera.eye.z);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Model Loading Test");

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("GLEW initialization failed: %s\n", glewGetErrorString(err));
        return -1;
    }

    init();
    loadAssets();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("\n=== MODEL LOADING TEST ===\n");
    printf("Controls: WASD to move camera, Q/E for up/down\n");
    printf("          R to reload model, ESC to exit\n");
    printf("Expected: Green ground, Red cube (center), Jeep model (right)\n\n");

    glutMainLoop();
    return 0;
}
