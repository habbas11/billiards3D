//
// Created by User on 21/12/2021.
//

#ifndef BILLIARDS3D_HOLE_H
#define BILLIARDS3D_HOLE_H

#include <GL/glut.h>
#include "Ball.h"

const double holeRadius = 0.5;

class Hole {

public:
    double x, z;
    double radius;

    // The constructor
    Hole(double x, double z) {
        this->x = x, this->z = z;
        this->radius = holeRadius;
    }

    void drawHoleCircle() const {

        glColor3ub(0, 0, 0);
        glTranslatef(x, -4.85, z);
        glBegin(GL_POLYGON);
        for (double i = 0; i <= 360 * 2;) {
            double temp = acos(-1) * i * 2;
            double circleX = cos(temp / 360) * 0.5;
            double circleZ = sin(temp / 360) * 0.5;
            glVertex3d(circleX, 0, circleZ);
            i++;
        }
        glEnd();
        glTranslatef(-x, 4.85, -z);
    }
};

// The array of holes we'll use
Hole *holes[6];


#endif //BILLIARDS3D_HOLE_H
