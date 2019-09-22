#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void Ball::init(int size,int speed)
{
    _size = size;

    _x = WIDTH/2 -  _size/2;
    _y = HEIGHT/2 - _size/2;

    srand(time(NULL));
    int direction = rand() % 4; // randomise initial direction. 

    // 4 possibilities. Get random modulo and set velocities accordingly
    if (direction == 0) {
        _velocity.x = speed;
        _velocity.y = speed;
    } else if (direction == 1) {
        _velocity.x = speed;
        _velocity.y = -speed;
    } else if (direction == 2) {
        _velocity.x = speed;
        _velocity.y = speed;
    } else {
        _velocity.x = -speed;
        _velocity.y = -speed;
    }
}

void Ball::draw(N5110 &lcd)
{
    lcd.drawRect(_x,_y,_size,_size,FILL_BLACK);
}

void Ball::update()
{
    _x += _velocity.x;
    _y += _velocity.y;
}

void Ball::set_velocity(Vector2D v)
{
    _velocity.x = v.x;
    _velocity.y = v.y;
}

Vector2D Ball::get_velocity()
{
    Vector2D v = {_velocity.x,_velocity.y};
    return v;
}

Vector2D Ball::get_pos()
{
    Vector2D p = {_x,_y};
    return p;
}

void Ball::set_pos(Vector2D p)
{
    _x = p.x;
    _y = p.y;
}