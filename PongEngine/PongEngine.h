#ifndef PONGENGINE_H
#define PONGENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"
#include "Ball.h"
#include "Paddle.h"

// gap from edge of screen
#define GAP 2

class PongEngine
{

public:
    PongEngine();
    ~PongEngine();

    void init(int paddle_width,int paddle_height,int ball_size,int speed);
    void read_input(Gamepad &pad);
    void update(Gamepad &pad);
    void draw(N5110 &lcd);
    
private:

    void check_wall_collision(Gamepad &pad);
    void check_paddle_collisions(Gamepad &pad);
    void check_goal(Gamepad &pad);
    void print_scores(N5110 &lcd);
    
    Paddle _p1;
    Paddle _p2;
     
    int _paddle_width;
    int _paddle_height;
    int _ball_size;
    int _speed;
    
    // x positions of the paddles
    int _p1x;
    int _p2x;
    
    Ball _ball;
    
    Direction _d;
    float _mag;

};

#endif