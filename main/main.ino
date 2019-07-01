// include the library code:
#include <LiquidCrystal.h>
#include <pitches.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// we set the pin which we will connect the button and the joypad to
const int SW_pin = 2; // digital pin connected to switch output
const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output

int buzzer = 13;//the pin of the active buzzer

const int buttonPin = 4; //digital pin connected to button
int buttonState = 0;

// Positions
// The y position of the ship is a length 2 array because we need to store the previous position as well
int x_pos = 0;
int y_pos[2] = {0,0};

int enemy [4] = {0,0,0,0};
int x_enemy [4] = {16,16,16,16};
int y_enemy [4] = {0,1,1,0};

int bullet [4] = {0,0,0,0};
int x_bull [4];
int y_bull [4];

int x_bon;
int y_bon;

// counters
int t = 0;
int score = 0;
int bonus = 0;
int t_bonus = 0;

void setup() {
  // put your setup code here, to run once:

  //joypad 
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // set the button pic to input
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);

  //initialize the buzzer pin as an output
  pinMode(buzzer,OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome to my");
  lcd.setCursor(0,1);
  lcd.print("first game");
  delay(500);
  lcd.clear();

}

void loop() {

  // check for collisions 
  for (int n = 0 ; n<4 ; ++n){
    if ((enemy[n] == 1 and x_enemy[n] == x_pos and y_enemy[n] == y_pos[0]) or
    (enemy[n] == 1 and x_enemy[n] + 1 == x_pos and y_enemy[n] == y_pos[0] and y_enemy[n] == y_pos[1])){
      lcd.setCursor(x_enemy[n], y_enemy[n]);
      lcd.print("X");
      
      crash_sound();
      
      delay(400);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Game over!");
      lcd.setCursor(0,1);
      lcd.print("Score: ");
      lcd.setCursor(7,1);
      lcd.print(score);
      
      score = 0 ;
      x_pos = 0;
      y_pos[0] = 0;
      y_pos[1] = 0;
      for (int n = 0 ; n<4 ; ++n){
        bullet[n] = 0;
        enemy[n] = 0;
      }
      bonus = 0;
      t_bonus = 0;
      
      delay(1000);
      lcd.clear(); 
    }
  }


  

  
  // Draws the ship
  lcd.setCursor(x_pos, y_pos[0]);
  lcd.print(">");


  // Draws the enemies
  for (int n = 0 ; n<4 ; ++n){
    if (enemy[n] == 1 and x_enemy[n] > -1){
      lcd.setCursor(x_enemy[n], y_enemy[n]);
      lcd.print("}");
    }
  }

 

  // Moves ship
  // This function involves reading the joypad input
  // So I made it into an external function 
  y_pos[1] = y_pos[0];
  movement();
  

  // Moves and erases enemies
  for (int n = 0 ; n<4 ; ++n){
    if (enemy[n] == 1 and x_enemy[n] > 0){
      x_enemy[n] = x_enemy[n] - 1;
    }

    else if (enemy[n] == 1 and x_enemy[n] == 0){
      enemy[n] = 0;
    }
  }




  // Moves and erases bullets
  for (int n = 0 ; n<4 ; ++n){
    if (bullet[n] == 1 and x_bull[n] < 16){
      x_bull[n] = x_bull[n] + 1;
    }

    else if (x_bull[n] == 16){
      bullet[n] = 0;
      x_bull[n] = -1;
    }
  }  



  // Generates new enemies
  t = t + 100;
  if (t % (300*(random(1,4))) == 0){
    for (int n = 0 ; n<4 ; ++n){
      if (enemy[n] == 0){
        enemy[n] = 1;
        x_enemy[n] = 16;
        y_enemy[n] = random(0,2);
        t = 0;
        break;
      }
    }
  }
  

  // Firing:
  // reads the state of the button
  buttonState = digitalRead(buttonPin);
  if (buttonState == 1 and x_pos < 14){
    for (int n = 0 ; n<4 ; ++n){
      if (bullet[n] == 0){
        bullet[n] = 1;
        x_bull[n] = x_pos + 1;
        y_bull[n] = y_pos[0];

//        unsigned char i;
//        for(i=0;i<20;i++)
//        {
//        digitalWrite(buzzer,HIGH);
//        delay(1);//wait for 1ms
//        digitalWrite(buzzer,LOW);
//        delay(1);//wait for 1ms
//        }

        shooting_sound();
        
        break;  
      }
    }
  }


  // Draws the bullets
  for (int n = 0 ; n<4 ; ++n){
    if (bullet[n] == 1 and x_bull[n] < 16){
      lcd.setCursor(x_bull[n], y_bull[n]);
      lcd.print("-");
    }
  }  


  // Bullets destroy enemies
  for (int n = 0 ; n < 4 ; ++n){
    for (int m = 0 ; m < 4 ; ++m){
      if (bullet[n] == 1 and enemy[m] == 1 and ((x_bull[n] == x_enemy[m]) or  x_bull[n] - 1 == x_enemy[m]) and y_bull[n] == y_enemy[m]){
        bullet[n] = 0;
        enemy[m] = 0;
        lcd.setCursor(x_enemy[m], y_enemy[m]);
        lcd.print("X");
        delay(50);
        score = score + 1;
        break;
      }
    }
  }  


  
  // Generates bonus
  if (bonus == 0 and score > 0 and score % 21 == 0 and random(0,2) == 0){
    x_bon = random(7,15);
    y_bon = random(0,2);
    bonus = 1;
  }

  // Draws and erases bonus
  if (t_bonus < 50 and bonus == 1){
    lcd.setCursor(x_bon, y_bon);
    lcd.print("*");  
    t_bonus = t_bonus + 1;

    if ((t_bonus % 6 == 0) or (t_bonus == 0)){
      tone(buzzer, 1000, 100);
    }

    else if(t_bonus % 6 == 3){
      tone(buzzer, 500, 100);
    }
  }

  else {
    bonus = 0;
    t_bonus = 0;
  }

  // Get the bonus
  if (x_pos == x_bon and y_pos[0] == y_bon and bonus == 1 ){
    bonus = 0;
    score = score + 50;
  }
  
  

  // Clear and delay
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


// Design of the bullet
byte bullet_char[8] = {
  B00000,
  B00000,
  B00000,
  B01100,
  B01100,
  B00000,
  B00000,
  B00000
};


// Sound functions

void shooting_sound() {
  for (int n = 2000 ; n > 100 ; --n){
    if (n % 2 == 0){
      tone(buzzer,n,2);
    }  
  }
};


// Crash sound 

void crash_sound() {
  for (int n = 0 ; n < 500 ; ++n){
    tone(buzzer,random(100,2000),20);
  }
};
