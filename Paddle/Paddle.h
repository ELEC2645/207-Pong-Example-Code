#ifndef PADDLE_H
#define PADDLE_H

#include "mbed.h"
#include "N5110.h"
#include "Gamepad.h"

class Paddle
{
public:

    Paddle();
    ~Paddle();
    void init(int x,int height,int width);
    void draw(N5110 &lcd);
    void update(Direction d,float mag);
    void add_score();
    int get_score();
    Vector2D get_pos();

private:

    int _height;
    int _width;
    int _x;
    int _y;
    int _speed;
    int _score;

};
#endif