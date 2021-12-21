//
// Created by User on 21/12/2021.
//

#ifndef BILLIARDS3D_BALL_H
#define BILLIARDS3D_BALL_H



#include <valarray>
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <Gl/glut.h>
#include "Hole.h"

using namespace std;

const GLfloat PI = acos(-1);
const int HEIGHT = 800;
const int WIDTH = 1000;
const double EPS = 1e-18;
const double ballRadius = 0.4;
const double gravity = 9.81;

// Lights and mat properties for the spheres
const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 1.0f, 5.0f, 0.0f};
const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

// The number of balls at the beginning
int remainingBalls = 16;

class Ball {

public:

    // All the properties that are needed for controlling the balls

    // position vector
    double x, z;
    double radius;
    double red, green, blue;
    double speed;
    // The line which the ball will follow when it has speed
    double ballRect;
    // The friction force caused by moving on the table
    double frictionForce;
    // The number of the ball
    int id;

    // The constructor
    Ball(double x, double z, double red, double green, double blue, double rect, int id) {
        this->x = x, this->z = z;
        this->red = red;
        this->green = green, this->blue = blue, this->ballRect = rect;
        this->speed = 0;
        this->radius = ballRadius;
        // The pool table has a coefficient of friction of 0.005 at any point on the table
        this->frictionForce = 0.005;
        this->id = id;
    }

    void drawBall() const {
        // Specifying the lighting properties
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
//        glEnable(GL_LIGHTING);
//
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        // Giving a specific color for the ball
        glColor3ub((GLubyte) red, (GLubyte) green, (GLubyte) blue);

        // Drawing
        glPushMatrix();
        glTranslated(x, -4.4, z);
        glutSolidSphere(this->radius, 60, 20);
        glPopMatrix();
    }

    // Moving the ball when there is no ballsCollision
    void moveBall() {
        // The ball will be affected by the friction of the table and the gravity
        if (speed > (frictionForce * gravity)) {
            speed -= frictionForce * gravity;
            x += cos((ballRect * PI) / 180.0) * speed;
            z += sin((ballRect * PI) / 180.0) * speed;
        } else
            speed = 0;
    }

    // Checking if the ball got inside a hole
    void checkHole() {
        // Looping throw all the 6 holes
        for (auto &hole: holes) {
            // Applying the formula of distance between two circles
            double distOnX = hole->x - x;
            double distOnY = hole->z - z;

            // If the two circles touch...
            if (((distOnX * distOnX) + (distOnY * distOnY)) <= (ballRadius + holeRadius) * (ballRadius + holeRadius)) {
                cout << "====== Ball " << id << " got inside a hole ======" << '\n';
                // Playing a sound (Might not work if not running in debug mode)
                PlaySound(TEXT("C:\\Users\\User\\CLionProjects\\billiards2D\\falling.wav"), nullptr,
                          SND_FILENAME | SND_ASYNC);

                // If the white ball
                if (id == 0) {
                    cout << "====== White Ball got inside a hole ======" << '\n';
                    x = hole->x;
                    z = hole->z;
                    x = -1.0;
                    z = -35.0;
                    speed = 0;
                }
                    // If not a white ball, get it out of the viewing range, and stop it
                else {
                    x = -20, z = -20;
                    speed = 0;
                    --remainingBalls;
                }
            }
        }
    }

    // Checking if a ball hits any of the table borders, and if so reduce its speed
    void checkTableBorder() {
        // Left border
        if (((x - ballRadius) <= -10.6) && (z >= -42 && z <= -28)) {
            cout << "Ball " << id << " touched left border" << '\n';
            ballRect = 180 - ballRect;
            if (ballRect < 0)
                ballRect += 360;
            x = -10.6 + ballRadius;
            speed *= 0.55;
        }

        // Right border
        if (((x + ballRadius) >= 10.6) && (z >= -42 && z <= -28)) {
            cout << "Ball " << id << " touched right border" << '\n';
            ballRect = 180 - ballRect;
            if (ballRect < 0)
                ballRect += 360;
            x = 10.6 - ballRadius;
            speed *= 0.55;
        }

        // Down border
        if ((x >= -12 && x <= 12) && ((z - ballRadius) >= -29.4)) {
            cout << "Ball " << id << " touched down left border" << '\n';
            ballRect = 360 - ballRect;
            if (ballRect < 0)
                ballRect += 360;
            z = -29.4 + ballRadius;
            speed *= 0.55;
        }

        // Up border
        if ((x >= -12 && x <= 12) && ((z - ballRadius) <= -40.2)) {
            cout << "Ball " << id << " touched down right border" << '\n';
            ballRect = 360 - ballRect;
            if (ballRect < 0)
                ballRect += 360;
            z = -40.2 + ballRadius;
            speed *= 0.55;
        }
    }

    // For checking if two ball collide
    bool collide(Ball &targetBall) const {
        return fabs(((x - targetBall.x) * (x - targetBall.x)) + ((z - targetBall.z) * (z - targetBall.z))) <=
               ((2 * ballRadius) * (2 * ballRadius));
    }

    // The event to be taken when two balls collide
    void ballsCollision(Ball &targetBall) {
        if (collide(targetBall)) {
            cout << "Balls " << id << " and " << targetBall.id << " collided." << '\n';

            double dist = sqrt(((x - targetBall.x) * (x - targetBall.x)) + ((z - targetBall.z) * (z - targetBall.z)));
            double overLap = 0.5 * (dist - (2 * ballRadius));

            x -= overLap * (x - targetBall.x) / dist;
            z -= overLap * (z - targetBall.z) / dist;

            targetBall.x += overLap * (x - targetBall.x) / dist;
            targetBall.z += overLap * (z - targetBall.z) / dist;

            double rect = atan2(z - targetBall.z, x - targetBall.x);
            rect *= 180;
            rect /= PI;


            double firstBallX, firstBallY, targetBallX, targetBallY;

            firstBallX = cos(((ballRect - rect) * PI) / 180.0) * speed;
            firstBallY = sin(((ballRect - rect) * PI) / 180.0) * speed;

            targetBallX = cos(((targetBall.ballRect - rect) * PI) / 180.0) * targetBall.speed;
            targetBallY = sin(((targetBall.ballRect - rect) * PI) / 180.0) * targetBall.speed;

            // Adjusting the speed of the two balls
            speed = sqrt(pow(targetBallX, 2) + pow(firstBallY, 2));
            targetBall.speed = sqrt(pow(firstBallX, 2) + pow(targetBallY, 2));

            // Adjusting the rect of the two balls
            ballRect = rect + (atan2(firstBallY, targetBallX) * 180 / PI);
            targetBall.ballRect = rect + (atan2(targetBallY, firstBallX) * 180 / PI);
        }
    }

};

// The array of balls we'll use
Ball *balls[16];




#endif //BILLIARDS3D_BALL_H
