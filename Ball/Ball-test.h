#ifndef BALL_TEST_H
#define BALL_TEST_H

/**
 * \brief Check that Ball object goes to correct position when moved
 * 
 * \returns true if all the tests passed
 */
bool Ball_test_movement()
{
    // Initialise Ball object with a size of 2, and speed of 1
    Ball ball;
    ball.init(2, 1);

    // Set the position to 5, 5
    Vector2D initial_pos = {5, 5};
    ball.set_pos(initial_pos);

    // Read the position
    Vector2D read_pos_1 = ball.get_pos();
    printf("%f, %f\n", read_pos_1.x, read_pos_1.y);

    // Set the velocity to -2, 3
    Vector2D velocity = {-2, 3};
    ball.set_velocity(velocity);

    // Update the position
    ball.update();

    // Read the position
    Vector2D read_pos_2 = ball.get_pos();
    printf("%f, %f\n", read_pos_2.x, read_pos_2.y);
    
    // Now check that both the positions are as expected
    bool success_flag = true;
    
    // Fail the test if the initial position is wrong
    if (read_pos_1.x != 5 || read_pos_1.y != 5) {
        success_flag = false;
    }
    
    // Fail the test if the final position is wrong
    if (read_pos_2.x != 3 || read_pos_2.y != 8) {
        success_flag = false;
    }

    return success_flag;
}
#endif