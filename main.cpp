///////// pre-processor directives ////////
#include "mbed.h"
#include "Gamepad.h"
#include "N5110.h"
#include "PongEngine.h"

#ifdef WITH_TESTING
# include "tests.h"
#endif

#define PADDLE_WIDTH 2
#define PADDLE_HEIGHT 8
#define BALL_SIZE 2
#define BALL_SPEED 3

/////////////// structs /////////////////
struct UserInput {
    Direction d;
    float mag;
};
/////////////// objects ///////////////
N5110 lcd;
Gamepad pad;
PongEngine pong;

///////////// prototypes ///////////////
void init();
void update_game(UserInput input);
void render();
void welcome();

///////////// functions ////////////////
int main()
{
#ifdef WITH_TESTING
    int number_of_failures = run_all_tests();

    if(number_of_failures > 0) return number_of_failures;
#endif

    int fps = 8;  // frames per second

    init();     // initialise and then display welcome screen...
    welcome();  // waiting for the user to start
    
    render();  // first draw the initial frame 
    wait(1.0f/fps);  // and wait for one frame period


    // game loop - read input, update the game state and render the display
    while (1) {
        pong.read_input(pad);
        pong.update(pad);
        render();
        wait(1.0f/fps);
    }
}

// initialies all classes and libraries
void init()
{
    // need to initialise LCD and Gamepad 
    lcd.init();
    pad.init();
     
    // initialise the game with correct ball and paddle sizes
    pong.init(PADDLE_WIDTH,PADDLE_HEIGHT,BALL_SIZE,BALL_SPEED);

}

// this function draws each frame on the LCD
void render()
{
    // clear screen, re-draw and refresh
    lcd.clear();  
    pong.draw(lcd);
    lcd.refresh();
}

// simple splash screen displayed on start-up
void welcome() {
    
    lcd.printString("     Pong!    ",0,1);  
    lcd.printString("  Press Start ",0,4);
    lcd.refresh();
     
    // wait flashing LEDs until start button is pressed 
    while ( pad.start_pressed() == false) {
        pad.leds_on();
        wait(0.1);
        pad.leds_off();
        wait(0.1);
    }
 
}