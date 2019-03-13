// include the library code:
#include <LiquidCrystal.h>
#include <pitches.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// we set the pin which we will connect the button and the joypad to
const int SW_pin = 2; // digital pin connected to switch output. We won't use this
const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output

/////////////////////////////
// Variables and constants //
/////////////////////////////

  // Positions

// The y position of the ship is a length 2 array because we 
// need to store the previous position as well. This will be 
// important when dealing with collisions
int x_pos = 0;
int y_pos[2] = {0,0};



void setup() {
  // Set the communication speed
  Serial.begin(9600);

  // Prints the start message of the game
  lcd.begin(16, 2);
  lcd.print("Welcome to my");
  lcd.setCursor(0,1);
  lcd.print("first game");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  // Draws the ship
  lcd.setCursor(x_pos, y_pos[0]);
  lcd.print(">");

  // Moves ship
  // This function involves reading the joypad input
  // so it is made it into an external function 
  y_pos[1] = y_pos[0];
  movement();


  // Clear the screen and delay
  delay(100);
  lcd.clear();    
}


////////////////////////
// External functions //
////////////////////////

void movement() {
  if (analogRead(Y_pin) < 100  and y_pos[0] == 1)
  {
    y_pos[0] = y_pos[0] - 1;
  }
  
  else if (analogRead(Y_pin) > 900 and y_pos[0] == 0)
  {
    y_pos[0] = y_pos[0] + 1;
  }
  
  else if (analogRead(X_pin) < 100 and x_pos < 15 )
  {
    x_pos = x_pos + 1;
  }
  
  else if (analogRead(X_pin) > 900 and x_pos > 0  )
  {
    x_pos = x_pos - 1;
  }  
}
