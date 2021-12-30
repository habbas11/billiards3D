/*
 * SVU - ITE - BCG601 - S21
 * Dr.Samer Jamal
 *
 * Participants:
 *  omar_116205
 *  omar_108591
 *  mhd_hussam_109817
 *
 * */

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Room.h"
#include "Table.h"
#include "Ball.h"
#include "Hole.h"
#include "Camera.h"
#include "Stick.h"

using namespace std;

const float step = .5;
const float pushStep = 0.2;
bool gameOver = false;
GLfloat tempX;
GLfloat tempZ;

// Handling key presses
void keyboardEventHandler(unsigned char key, int, int) {
    cout << (int) key << '\n';
    cout << "Camera x = " << camera.x << ", Camera y = " << camera.y << ", Camera z = " << camera.z << '\n';
    switch (key) {
        // w or W
        case 119:
        case 87:
            if (camera.y >= -9)
                camera.y -= step;
            break;
            // s or S
        case 115:
        case 83:
            if (camera.y <= 1)
                camera.y += step;
            break;
            // a or A
        case 97:
        case 65:
            if ((camera.x + step) < 20)
                camera.x += step;
            break;
            // d or D
        case 100:
        case 68:
            if ((camera.x - step) > -20)
                camera.x -= step;
            break;
            // q or Q
        case 113:
        case 81:
            if ((camera.z - step) >= 2)
                camera.z -= step;
            break;
            // e or E
        case 101:
        case 69:
            if ((camera.z + step) <= 98)
                camera.z += step;
            break;
            // 4 num key
        case 52:
            glRotatef(-0.8, 0, 1, 0);
            break;
            // 6 num key
        case 54:
            glRotatef(0.8, 0, 1, 0);
            break;
            // 8 num key
        case 56:
            glRotatef(-0.8, 1, 0, 0);
            break;
            // 2 num key
        case 50:
            glRotatef(0.8, 1, 0, 0);
            break;
            // Although it is meaningless to rotate around the Z axis
            // 7 num key
        case 55:
            glRotatef(0.8, 0, 0, 1);
            break;
            // 9 num key
        case 57:
            glRotatef(-0.8, 0, 0, 1);
            break;
            // z or Z
        case 122:
        case 90:
            balls[0]->x -= pushStep;
            break;
            // x or X
        case 120:
        case 88:
            balls[0]->x += pushStep;
            break;
            // c or C
        case 99:
        case 67:
            balls[0]->z += pushStep;
            break;
            // c or C
        case 118:
        case 86:
            balls[0]->z -= pushStep;
            break;
            // k or K (rotating the stick counterclockwise)
        case 107:
        case 75:
            tempX = cos(-0.1) * (stick.x2 - stick.x1) - sin(-0.1) * (stick.z2 - stick.z1) + stick.x1;
            tempZ = sin(-0.1) * (stick.x2 - stick.x1) + cos(-0.1) * (stick.z2 - stick.z1) + stick.z1;
            stick.x2 = tempX;
            stick.z2 = tempZ;
            break;
            // l or L (rotating the stick clockwise)
        case 108:
        case 76:
            tempX = cos(0.1) * (stick.x2 - stick.x1) - sin(0.1) * (stick.z2 - stick.z1) + stick.x1;
            tempZ = sin(0.1) * (stick.x2 - stick.x1) + cos(0.1) * (stick.z2 - stick.z1) + stick.z1;
            stick.x2 = tempX;
            stick.z2 = tempZ;
            break;
            // b or B (hitting the white ball at x0.01 speed)
        case 98:
        case 66:
            if (balls[0]->speed == 0)
                balls[0]->hitBall(0.01);
            break;
            // n or N (hitting the white ball at x0.1 speed)
        case 110:
        case 78:
            if (balls[0]->speed == 0)
                balls[0]->hitBall(0.1);
            break;
            // m or M (hitting the white ball at x0.5 speed)
        case 109:
        case 77:
            if (balls[0]->speed == 0)
                balls[0]->hitBall(0.5);
            break;
            // Escape key
        case 27:
            cout << "Exiting..." << '\n';
            exit(1);
        default:
            cout << (int) key << '\n';
            cout << "Unknown key pressed." << '\n';
    }

    glutPostRedisplay();
}

void mouseEventHandler(int button, int state, int mouseX, int mouseY) {
    cerr << state << ' ' << mouseX << ' ' << mouseY << '\n';
    if (button == 3) {
        if ((camera.z + step) <= 98)
            camera.z += step;
    } else if (button == 4) {
        if ((camera.z - step) >= 2)
            camera.z -= step;
    } else
        cout << button << '\n';

    glutPostRedisplay();
}

void special(int key, int, int) {
    if (GLUT_KEY_LEFT == key) {
        camera.x -= step;
        cout << "LEFT" << '\n';
    }
    if (GLUT_KEY_RIGHT == key) {
        camera.x += step;
        cout << "RIGHT" << '\n';
    }
    if (GLUT_KEY_UP == key) {
        camera.z += step;
        cout << "UP" << '\n';
    }
    if (GLUT_KEY_DOWN == key) {
        camera.z -= step;
        cout << "DOWN" << '\n';
    }
    glutPostRedisplay();
}

void init() {
    // Initializing the Display Mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Specifying the window dimensions
    glutInitWindowSize(WIDTH, HEIGHT);
    // Creating the window, with its label
    glutCreateWindow("BCG601 - Billiards 3D");
    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glLoadIdentity();
    gluPerspective(60, 1.0, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    // Lighting parameters
    GLfloat mat_ambdif[] = {10.0, 20.0, 24.0, 1.0};
    GLfloat mat_specular[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {00.0};
    GLfloat light_position[] = {0, 9.0, -20.0, 2.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambdif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    // Initializing the holes
    // down leftmost hole
    holes[0] = new Hole(-10.3, -29.4);
    // down rightmost hole
    holes[1] = new Hole(-10.3, -40.3);
    // down mid-hole
    holes[2] = new Hole(0, -29.4);
    // up leftmost hole
    holes[3] = new Hole(10.3, -29.4);
    // up rightmost hole
    holes[4] = new Hole(+10.3, -40.3);
    // up mid-hole
    holes[5] = new Hole(0, -40.3);

    // Initializing the balls
    // 15
    balls[15] = new Ball(8, -37.5, 18, 135, 57, 0, 15);
    // 14
    balls[14] = new Ball(8, -36.5, 155, 97, 77, 0, 14);
    // 13
    balls[13] = new Ball(8, -35.0, 244, 122, 66, 0, 13);
    // 12
    balls[12] = new Ball(8, -33.5, 128, 68, 133, 0, 12);
    // 11
    balls[11] = new Ball(8, -32.0, 223, 39, 40, 0, 11);


    // 10
    balls[10] = new Ball(7, -37.25, 42, 57, 132, 0, 10);
    // 09
    balls[9] = new Ball(7, -35.75, 255, 196, 55, 0, 9);
    // 08
    balls[8] = new Ball(7, -34.25, 4, 159, 72, 0, 8);
    // 07
    balls[7] = new Ball(7, -32.75, 144, 96, 66, 0, 7);

    // 06
    balls[6] = new Ball(6, -36.5, 241, 121, 38, 0, 6);
    // 05
    balls[5] = new Ball(6, -35.0, 52, 60, 54, 0, 5);
    // 04
    balls[4] = new Ball(6, -33.5, 139, 73, 133, 0, 4);

    // 03
    balls[3] = new Ball(5, -35.75, 241, 32, 53, 0, 3);
    // 02
    balls[2] = new Ball(5, -34.25, 37, 57, 114, 0, 2);

    // 01
    balls[1] = new Ball(4, -35.0, 251, 199, 54, 0, 1);
    // White ball
    balls[0] = new Ball(-4, -35.0, 255, 255, 255, 0, 0);

}

void draw() {
    // Specifying the window color
    //208, 125, 100
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // For camera
    glTranslatef(camera.x, camera.y, camera.z);

    if (balls[0]->speed == 0) {
        stick.x1 = balls[0]->x;
        stick.z1 = balls[0]->z;
        stick.drawStick();
    } else {
        stick.x2 = balls[0]->x - 5;
        stick.z2 = balls[0]->z;
    }

    // === TABLE LEGS
    // Front left leg
    glTranslatef(-10, 0, -30);
    Table::drawLeg();
    glTranslatef(10, 0, 30);

    // Front right leg
    glTranslatef(10, 0, -30);
    Table::drawLeg();
    glTranslatef(-10, 0, 30);

    // Back left leg
    glTranslatef(-10, 0, -40);
    Table::drawLeg();
    glTranslatef(10, 0, 40);

    // Back right leg
    glTranslatef(10, 0, -40);
    Table::drawLeg();
    glTranslatef(-10, 0, 40);

    // === TABLE BORDERS
    // Left bottom border
    glTranslatef(-11.5, 0, 0);
    Table::drawSurfaceXBorder();
    glTranslatef(+11.5, 0, 0);

    // Left Up border
    glTranslatef(-11.5, .9, 0);
    Table::drawSurfaceXBorder();
    glTranslatef(+11.5, -.9, 0);

    // Right bottom border
    glTranslatef(+11.5, 0, 0);
    Table::drawSurfaceXBorder();
    glTranslatef(-11.5, 0, 0);

    // Right Up border
    glTranslatef(+11.5, .9, 0);
    Table::drawSurfaceXBorder();
    glTranslatef(-11.5, -.9, 0);

    // Down bottom border
    Table::drawSurfaceYBorder();

    // Down up border
    glTranslatef(0, .9, 0);
    Table::drawSurfaceYBorder();
    glTranslatef(0, -.9, 0);

    // Up bottom border
    glTranslatef(0, 0, -13);
    Table::drawSurfaceYBorder();
    glTranslatef(0, 0, +13);

    // Up up border
    glTranslatef(0, .9, -13);
    Table::drawSurfaceYBorder();
    glTranslatef(0, -.9, +13);

    Table::drawSideYBorder();

    glTranslatef(0, 0, -1);
    Table::drawSideYBorder();
    glTranslatef(0, 0, 1);

    glTranslatef(0, 0, -14);
    Table::drawSideYBorder();
    glTranslatef(0, 0, 14);

    glTranslatef(0, 0, -13);
    Table::drawSideYBorder();
    glTranslatef(0, 0, 13);

    Table::drawSideXBorder();


    glTranslatef(1, 0, 0);
    Table::drawSideXBorder();
    glTranslatef(-1, 0, 0);

    glTranslatef(+24, 0, 0);
    Table::drawSideXBorder();
    glTranslatef(-24, 0, 0);


    glTranslatef(+23, 0, 0);
    Table::drawSideXBorder();
    glTranslatef(-23, 0, 0);


    // Table green playground
    Table::drawTablePlayground();
    Table::drawMidCircle();
    Table::drawMidLine();

    // Rendering walls, ceiling, and roof
    Room::drawRoom();

    // Drawing holes
    // down leftmost hole
    holes[0]->drawHoleCircle();
    // down rightmost hole
    holes[1]->drawHoleCircle();
    // down mid-hole
    holes[2]->drawHoleCircle();
    // up leftmost hole
    holes[3]->drawHoleCircle();
    // up rightmost hole
    holes[4]->drawHoleCircle();
    // up mid-hole
    holes[5]->drawHoleCircle();

    // Drawing balls
    // 15
    balls[15]->drawBall();
    // 14
    balls[14]->drawBall();
    // 13
    balls[13]->drawBall();
    // 12
    balls[12]->drawBall();
    // 11
    balls[11]->drawBall();
    // 10
    balls[10]->drawBall();
    // 09
    balls[9]->drawBall();
    // 08
    balls[8]->drawBall();
    // 07
    balls[7]->drawBall();
    // 06
    balls[6]->drawBall();
    // 05
    balls[5]->drawBall();
    // 04
    balls[4]->drawBall();
    // 03
    balls[3]->drawBall();
    // 02
    balls[2]->drawBall();
    // 01
    balls[1]->drawBall();
    // White ball
    balls[0]->drawBall();

    // For camera
    glTranslatef(-camera.x, -camera.y, -camera.z);

    // Finally, empty all these buffers
    glFlush();
    glutSwapBuffers();
}

// A timer function for refreshing the display every 1 ms
void timerCallBack(int) {

    for (auto &ball: balls) {
        // Move every ball that has speed
        // Check every ball hitting a wall, or entering a hole
        ball->moveBall(), ball->checkTableBorder(), ball->checkHole();

        // Check for colliding between any two balls
        for (auto &targetBall: balls) {
            // No need to check ballsCollision for a ball and itself
            if (ball->id == targetBall->id)
                continue;
            ball->ballsCollision(*targetBall);
        }

    }

    // The game ends when only the white ball remains
    if (remainingBalls == 1 && !gameOver) {
        cout << " ++++ GAME OVER ++++ " << '\n';
        gameOver = true;
    }

    // Refresh display
    glutPostRedisplay();
    // Calling the timer function recursively
    glutTimerFunc(1, timerCallBack, 1);
}


int main(int argc, char **argv) {
    // Initializing the OpenGL Utility Toolkit first
    glutInit(&argc, argv);
    // Initializing and drawing our basic objects
    glOrtho(-10.0, 10, -20.0, 20, 100.0, 100.0);
    init();
    // For handling camera position on the Z axis
    glutMouseFunc(mouseEventHandler);
    // For handling camera position on the three axis
    glutKeyboardFunc(keyboardEventHandler);
    glutSpecialFunc(special);
    // For displaying our view
    glutDisplayFunc(draw);
    // Registering a timer callback to be triggered every 1ms
    glutTimerFunc(1, timerCallBack, 1);

    // For viewing and not closing the window
    glutMainLoop();

    return 0;
}
