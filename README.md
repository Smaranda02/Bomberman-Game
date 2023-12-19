# Unabomber-Game

## Some backstory:

   My game, Unabomber, is a simulation of the classical and well-known Bomberman game that originated in the 1980s and was created by Japanese 
game developer Hudson Soft. "Bomberman" has become an iconic and enduring franchise, with its influence extending beyond video games into 
various forms of media, including cartoons, merchandise, and even a board game.

  I chose to implement this masterpiece because it is a challenge to take care of all the stages in the game evolution as a developer, 
but I also find it really engaging and entertaining for the player itself.

## How to play the game:
My game, similarly to the original one, focuses on navigating mazes and strategically placing bombs to defeat enemies and open up pathways. 
The game has 3 levels and 4 rooms to explore, with the last level having 2 rooms of its own. It is mandatory to destroy all the walls and enemies 
before making it to the next level, of course, within the given time limit.

## Used Components:
- 1 buzzer -> signaling different events (explosions, losses, etc.)
- 1 joystick -> used by the player for interaction with the game
- 1 electrolytic capacitor of 10 µF -> to minimize power-supply ripple due to the peak digit driver currents
- 1 ceramic capacitor of 104 pF
- 1 LED -> signaling when there is little time left
- 1 button
- 1 potentiometer -> contrast control on the LCD
- 1 LCD -> display the menu and game details
- 1 8x8 matrix -> here will take place the game
- 2 330kΩ resistors -> for LED and buzzer
- 1 1kΩ resistor -> for the LCD
- 1 100kΩ resistor -> for the matrix
- 1 MAX7219 display driver -> for controlling the matrix

...and plenty of wires for connections :)

## Hardware schematic followed 
![image](https://github.com/Smaranda02/Bomberman-Game/assets/62556419/301cab45-6b36-4c0e-82ef-d3c50c25b174)

![image](https://github.com/Smaranda02/Bomberman-Game/assets/62556419/d8d919b7-417f-4472-aa60-e9de000af90f)

## Setup 

![setup](https://github.com/Smaranda02/Bomberman-Game/assets/62556419/bd7d747b-4a6f-43ae-ac07-0dfecaa3104c)

## Detailed demo 

Youtube link for an in-depth look over the game's functionalities : https://youtu.be/cCurrnF55tU

## External libraries used:
- LedControl.h -> for controlling the matrix
- avr/pgmspace.h -> for reading/writing into the Flash memory
- LiquidCrystal.h -> for LCD control
- EEPROM.h -> for interacting with EEPROM memory

