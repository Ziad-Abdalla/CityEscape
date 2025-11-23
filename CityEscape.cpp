#include <stdio.h>
#include "Model_3DS.h"
#include <glut.h>

int WIDTH = 1280;
int HEIGHT = 720;

// Simple camera position
float camX = 0, camY = 5, camZ = 20;
float lookX = 0, lookY = 0, lookZ = 0;

// Test models
Model_3DS jeepModel;
Model_3DS barrelModel;
Model_3DS coneModel;
Model_3DS fuelCanModel;
Model_3DS streetLightModel;
bool modelsLoaded = false;

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
    printf("Attempting to load models...\n");
    printf("Working directory should contain 'models' folder\n");

    // Load all models
    printf("Loading Jeep...\n");
    jeepModel.Load("models/player/Jeep/Jeep.3ds");

    printf("Loading Barrel...\n");
    barrelModel.Load("models/obstacles/barrel2/barrel2.3DS");

    printf("Loading Traffic Cone...\n");
    coneModel.Load("models/obstacles/TrafficCone/TrafficCone.3DS");

    printf("Loading Fuel Can...\n");
    fuelCanModel.Load("models/collectibles/FeulCan/FeulCan.3DS");

    printf("Loading Street Light...\n");
    streetLightModel.Load("models/environment/StreetLight2/StreetLight2.3ds");

    modelsLoaded = true;
    printf("All 5 models loaded successfully!\n");
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

    // Draw reference cube at origin (red) - 2 units high
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(2.0);
    glPopMatrix();

    if (modelsLoaded) {
        // Model scales adjusted for proper sizing
        float jeepScale = 0.05f;
        float barrelScale = 0.05f;
        float coneScale = 0.01f;      // Cones are bigger, scale down more
        float fuelCanScale = 0.01f;   // Fuel cans are bigger
        float lampScale = 0.01f;      // Lamps are bigger

        // Draw the Jeep (center)
        glPushMatrix();
        glTranslatef(0, 0, -10);
        glScalef(jeepScale, jeepScale, jeepScale);
        glColor3f(1.0, 1.0, 1.0);
        jeepModel.Draw();
        glPopMatrix();

        // Draw Barrels (left side)
        glPushMatrix();
        glTranslatef(-10, 0, 0);
        glScalef(barrelScale, barrelScale, barrelScale);
        glColor3f(1.0, 1.0, 1.0);
        barrelModel.Draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-10, 0, -5);
        glScalef(barrelScale, barrelScale, barrelScale);
        barrelModel.Draw();
        glPopMatrix();

        // Draw Traffic Cones (right side)
        glPushMatrix();
        glTranslatef(10, 0, 0);
        glScalef(coneScale, coneScale, coneScale);
        coneModel.Draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(10, 0, -5);
        glScalef(coneScale, coneScale, coneScale);
        coneModel.Draw();
        glPopMatrix();

        // Draw Fuel Cans (scattered)
        glPushMatrix();
        glTranslatef(5, 0, 5);
        glScalef(fuelCanScale, fuelCanScale, fuelCanScale);
        fuelCanModel.Draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-5, 0, 5);
        glScalef(fuelCanScale, fuelCanScale, fuelCanScale);
        fuelCanModel.Draw();
        glPopMatrix();

        // Draw Street Lights (back)
        glPushMatrix();
        glTranslatef(-15, 0, -15);
        glScalef(lampScale, lampScale, lampScale);
        streetLightModel.Draw();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(15, 0, -15);
        glScalef(lampScale, lampScale, lampScale);
        streetLightModel.Draw();
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

    printf("\n=== STRESS TEST: MULTIPLE 3DS MODELS ===\n");
    printf("Controls: WASD to move camera, Q/E for up/down\n");
    printf("          R to reload models, ESC to exit\n");
    printf("Scene: 1 Jeep, 2 Barrels, 2 Cones, 2 Fuel Cans, 2 Street Lights\n");
    printf("       Plus 1 reference red cube at origin\n\n");

    glutMainLoop();
    return 0;
}
