# Mini game for the arduino

## Introduction

Spaceship game for the arduino.

This is my first arduino project, and it has served mostly as a learning experience but also as a very fun experiment. The idea is to implement a fully functional game using a lcd screen, a joypad, a button and a buzzer. For this we will make use of serveral libraries to control some of the components.

## Video

[![Video demonstration](https://img.youtube.com/vi/o5h392pwCHI/0.jpg)](https://www.youtube.com/watch?v=o5h392pwCHI "Arduino mini game")

## Components

* 1 Arduino board (I used Mega 2560 but UNO works as well),
* 2-axis joystick
* 1 Button
* 1 Passive buzzer
* 10kΩ resistor
* 16x2 LCD display
* 10k potentiometer
* 1 Breadboard
* Several F-M and M-M wires


## Circuit board

![Circuit_board](https://github.com/felperez/Mini-game-arduino/blob/master/Circuit.png)



## How can we improve the project?

* The way the sound effects are built implies that the movement of the objects stops while playing the sounds. It would be interesting to fix this so the sounds do not slow down the natural flow of the game.
