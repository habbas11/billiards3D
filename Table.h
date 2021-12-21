//
// Created by User on 20/12/2021.
//

#ifndef BILLIARDS3D_TABLE_H
#define BILLIARDS3D_TABLE_H


#include <GL/glut.h>

class Table {

public:
    static void drawLeg() {
        glColor3ub(0, 0, 0);
        glBegin(GL_POLYGON);
        // Front
        glVertex3f(-0.5, -5, 0.5);
        glVertex3f(-0.5, -10, 0.5);
        glVertex3f(0.5, -10, 0.5);
        glVertex3f(0.5, -5, 0.5);

        // Back
        glVertex3f(-0.5, -5, -0.5);
        glVertex3f(0.5, -5, -0.5);
        glVertex3f(0.5, -10, -0.5);
        glVertex3f(-0.5, -10, -0.5);

        // Left side
        glVertex3f(-0.5, -5, 0.5);
        glVertex3f(-0.5, -10, 0.5);
        glVertex3f(-0.5, -10, -0.5);
        glVertex3f(-0.5, -5, -0.5);

        // Right side
        glVertex3f(0.5, -5, 0.5);
        glVertex3f(0.5, -5, -0.5);
        glVertex3f(0.5, -10, -0.5);
        glVertex3f(0.5, -10, 0.5);
        glEnd();
    }

    static void drawTablePlayground() {
        glColor3ub(32, 91, 47);
        glBegin(GL_POLYGON);
        glVertex3f(-12, -4.9, -28);
        glVertex3f(12, -4.9, -28);
        glVertex3f(12, -4.9, -42);
        glVertex3f(-12, -4.9, -42);
        glEnd();
    }

    static void drawSurfaceXBorder() {
        glColor3ub(173, 90, 23);
        glBegin(GL_POLYGON);
        glVertex3f(-0.5, -4.9, -28);
        glVertex3f(0.5, -4.9, -28);
        glVertex3f(0.5, -4.9, -42);
        glVertex3f(-0.5, -4.9, -42);
        glEnd();
    }

    static void drawSurfaceYBorder() {
        glColor3ub(173, 90, 23);
        glBegin(GL_POLYGON);
        glVertex3f(-12, -4.9, -28);
        glVertex3f(12, -4.9, -28);
        glVertex3f(12, -4.9, -29);
        glVertex3f(-12, -4.9, -29);
        glEnd();
    }


};


#endif //BILLIARDS3D_TABLE_H