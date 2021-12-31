//
// Created by User on 30/12/2021.
//

#ifndef BILLIARDS3D_STICK_H
#define BILLIARDS3D_STICK_H


#include <GL/glut.h>

class Stick {

public:
    float x1;
    float z1;
    float x2;
    float z2;

    // The constructor
    Stick(float stickX1, float stickZ1, float stickX2, float stickZ2) {
        this->x1 = stickX1;
        this->z1 = stickZ1;
        this->x2 = stickX2;
        this->z2 = stickZ2;
    }

    // Drawing the stick
    void drawStick() const {
        // Specifying the stick color
        glColor3ub(150, 128, 87);
        // Increasing the stroke (width) of lines
        glLineWidth(5.0);
        // Drawing
        glBegin(GL_LINES);
        glVertex3d(this->x2, -4.5, this->z2);
        glVertex3d(this->x1, -4.5, this->z1);
        glEnd();

        // In order not to let all the lines affected by the stick given width
        glLineWidth(1.0);
    }

};

// The stick that we'll use
Stick stick = Stick(-4, -35.0, -4 - 5, -35);

#endif //BILLIARDS3D_STICK_H
