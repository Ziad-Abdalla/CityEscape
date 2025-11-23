#include <glut.h>
#include <stdio.h>

int WIDTH = 1280;
int HEIGHT = 720;

// Simple camera position
float camX = 0, camY = 5, camZ = 20;
float lookX = 0, lookY = 0, lookZ = 0;

void init() {
    glClearColor(0.5, 0.7, 1.0, 1.0); // Light blue sky
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Simple white light
    GLfloat light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { 0.0, 10.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
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
    glColor3f(0.3, 0.8, 0.3);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(-50, 0, -50);
        glVertex3f(50, 0, -50);
        glVertex3f(50, 0, 50);
        glVertex3f(-50, 0, 50);
    glEnd();

    // Draw a red cube at origin
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(2.0);
    glPopMatrix();

    // Draw a blue cube to the right
    glPushMatrix();
    glTranslatef(5, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();

    // Draw a yellow cube to the left
    glPushMatrix();
    glTranslatef(-5, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidCube(2.0);
    glPopMatrix();

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
    glutCreateWindow("Basic OpenGL Test");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    printf("Controls: WASD to move camera, Q/E for up/down, ESC to exit\n");
    printf("You should see: Green ground, Red cube (center), Blue cube (right), Yellow cube (left)\n");

    glutMainLoop();
    return 0;
}
