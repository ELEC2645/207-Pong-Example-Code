#include "PongEngine.h"

PongEngine::PongEngine()
{

}

PongEngine::~PongEngine()
{

}

void PongEngine::init(int paddle_width,int paddle_height,int ball_size,int speed)
{
    // initialise the game parameters
    _paddle_width = paddle_width;
    _paddle_height = paddle_height;
    _ball_size = ball_size;
    _speed = speed;

    // x position on screen - WIDTH is defined in N5110.h
    _p1x = GAP;
    _p2x = WIDTH - GAP - _paddle_width;

    // puts paddles and ball in middle
    _p1.init(_p1x,_paddle_height,_paddle_width);
    _p2.init(_p2x,_paddle_height,_paddle_width);
    _ball.init(_ball_size,_speed);
}

void PongEngine::read_input(Gamepad &pad)
{
    _d = pad.get_direction();
    _mag = pad.get_mag();
}

void PongEngine::draw(N5110 &lcd)
{
    // draw the elements in the LCD buffer
    // pitch
    lcd.drawRect(0,0,WIDTH,HEIGHT,FILL_TRANSPARENT);
    lcd.drawLine(WIDTH/2,0,WIDTH/2,HEIGHT-1,2);
    //score
    print_scores(lcd);
    // paddles
    _p1.draw(lcd);
    _p2.draw(lcd);
    // ball
    _ball.draw(lcd);
}

void PongEngine::update(Gamepad &pad)
{
    check_goal(pad);
    // important to update paddles and ball before checking collisions so can
    // correct for it before updating the display
    _p1.update(_d,_mag);
    _p2.update(_d,_mag);
    _ball.update();

    check_wall_collision(pad);
    check_paddle_collisions(pad);
}

void PongEngine::check_wall_collision(Gamepad &pad)
{
    // read current ball attributes
    Vector2D ball_pos = _ball.get_pos();
    Vector2D ball_velocity = _ball.get_velocity();

    // check if hit top wall
    if (ball_pos.y <= 1) {  //  1 due to 1 pixel boundary
        ball_pos.y = 1;  // bounce off ceiling without going off screen
        ball_velocity.y = -ball_velocity.y;
        // audio feedback
        pad.tone(750.0,0.1);
    }
    // check if hit bottom wall
    else if (ball_pos.y + _ball_size >= (HEIGHT-1) ) { // bottom pixel is 47
        // hit bottom
        ball_pos.y = (HEIGHT-1) - _ball_size;  // stops ball going off screen
        ball_velocity.y = -ball_velocity.y;
        // audio feedback
        pad.tone(750.0,0.1);
    }

    // update ball parameters
    _ball.set_velocity(ball_velocity);
    _ball.set_pos(ball_pos);
}

void PongEngine::check_paddle_collisions(Gamepad &pad)
{
    // read current ball attributes
    Vector2D ball_pos = _ball.get_pos();
    Vector2D ball_velocity = _ball.get_velocity();

    // check p1 first
    Vector2D p1_pos = _p1.get_pos();

    // see if ball has hit the paddle by checking for overlaps
    if (
        (ball_pos.y >= p1_pos.y) && //top
        (ball_pos.y <= p1_pos.y + _paddle_height) && //bottom
        (ball_pos.x >= _p1x) && //left
        (ball_pos.x <= _p1x + _paddle_width)  //right
    ) {
        // if it has, fix position and reflect x velocity
        ball_pos.x = _p1x + _paddle_width;
        ball_velocity.x = -ball_velocity.x;
        // audio feedback
        pad.tone(1000.0,0.1);
    }

    // check p2 next
    Vector2D p2_pos = _p2.get_pos();

    // see if ball has hit the paddle by checking for overlaps
    if (
        (ball_pos.y >= p2_pos.y) && //top
        (ball_pos.y <= p2_pos.y + _paddle_height) && //bottom
        (ball_pos.x + _ball_size >= _p2x) && //left
        (ball_pos.x + _ball_size <= _p2x + _paddle_width)  //right
    ) {
        // if it has, fix position and reflect x velocity
        ball_pos.x = _p2x - _ball_size;
        ball_velocity.x = -ball_velocity.x;
        // audio feedback
        pad.tone(1000.0,0.1);
    }

    // write new attributes
    _ball.set_velocity(ball_velocity);
    _ball.set_pos(ball_pos);
}

void PongEngine::check_goal(Gamepad &pad)
{
    Vector2D ball_pos = _ball.get_pos();
    // P2 has scored
    if (ball_pos.x + _ball_size < 0) {
        _p2.add_score();
        _ball.init(_ball_size,_speed);
        pad.tone(1500.0,0.5);
        pad.leds_on();
        wait(0.5);
        pad.leds_off();
    }

    // P1 has scored
    if (ball_pos.x > WIDTH) {
        _p1.add_score();
        _ball.init(_ball_size,_speed);
        pad.tone(1500.0,0.5);
        pad.leds_on();
        wait(0.5);
        pad.leds_off();
    }
}

void PongEngine::print_scores(N5110 &lcd)
{
    // get scores from paddles
    int p1_score = _p1.get_score();
    int p2_score = _p2.get_score();

    // print to LCD i
    char buffer1[14];
    sprintf(buffer1,"%2d",p1_score);
    lcd.printString(buffer1,WIDTH/2 - 20,1);  // font is 8 wide, so leave 4 pixel gape from middle assuming two digits
    char buffer2[14];
    sprintf(buffer2,"%2d",p2_score);
    lcd.printString(buffer2,WIDTH/2 + 4,1);
}