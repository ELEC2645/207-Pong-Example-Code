#ifndef BALL_H
#define BALL_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Paddle.h"

/** Ball Class
@author Dr Craig A. Evans, University of Leeds
@brief Controls the ball in the Pong game 
@date Febraury 2017
*/ 
class Ball
{

public:
    Ball();
    ~Ball();
    void init(int size,int speed);
    void draw(N5110 &lcd);
    void update();
    /// accessors and mutators
    void set_velocity(Vector2D v);
    Vector2D get_velocity();
    Vector2D get_pos();
    void set_pos(Vector2D p);
    
private:

    Vector2D _velocity;
    int _size;
    int _x;
    int _y;
};
#endif