//
// Created by User on 20/12/2021.
//

#ifndef BILLIARDS3D_ROOM_H
#define BILLIARDS3D_ROOM_H


#include <GL/glut.h>
#include "Camera.h"


class Room {

public:
    static void drawRoom() {
        // Floor
        glColor3ub(208, 190, 182);
        glBegin(GL_POLYGON);
        glVertex3f(-20, -10, 50);
        glVertex3f(20, -10, 50);
        glVertex3f(20, -10, -100);
        glVertex3f(-20, -10, -100);
        glEnd();

        // Ceiling
        glColor3ub(190, 135, 127);
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(-20, 10, 50);
        glVertex3f(20, 10, 50);
        glVertex3f(20, 10, -100);
        glVertex3f(-20, 10, -100);
        glEnd();

        // Left wall
        glColor3ub(208, 125, 117);
        glBegin(GL_POLYGON);
        glVertex3f(-20, -10, 50);
        glVertex3f(-20, 10, 50);
        glVertex3f(-20, 10, -100);
        glVertex3f(-20, -10, -100);
        glEnd();

        // Right wall
        glColor3ub(208, 125, 117);
        glBegin(GL_POLYGON);
        glVertex3f(20, -10, 50);
        glVertex3f(20, 10, 50);
        glVertex3f(20, 10, -100);
        glVertex3f(20, -10, -100);
        glEnd();

        // Front wall
        glColor3ub(208, 125, 100);
        glBegin(GL_POLYGON);
        glVertex3f(-20, -10, -100);
        glVertex3f(20, -10, -100);
        glVertex3f(20, 10, -100);
        glVertex3f(-20, 10, -100);
        glEnd();

        // Back wall
        glColor3ub(208, 125, 100);
        glBegin(GL_POLYGON);
        glVertex3f(-20, -10, 30);
        glVertex3f(20, -10, 30);
        glVertex3f(20, 10, 30);
        glVertex3f(-20, 10, 30);
        glEnd();
    }
};


#endif //BILLIARDS3D_ROOM_H
