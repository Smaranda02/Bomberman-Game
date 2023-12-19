#include "LedControl.h"
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#include "Matrix.h"
#include "Bombs.h"
#include "Joystick.h"
#include "LCD.h"
#include "Menu.h"
#include "Player.h"
#include "Buzzer.h"
#include "Enemy.h"
#include "Level.h"

bool gameStarted = false;

unsigned long lastLedBlink = 0;
int ledTimeDelay = 300;
volatile bool ledState = 0;
byte ledPin = A5;

byte inferiorTimeWarning = 0;
byte superiorTimeWarning = 10;


void checkButtonPress() {
  if (isButtonPressed) {

    //we consider the button press as placing a bomb only if the player is alive and there isn't already a bomb (matrix[i][j] != 2)
    if (isAlive) {
      if (currentMatrix[playerLine][playerColumn] == 0) {
        for (int i = 0; i < maximumBombs; i++) {
          if (bombs[i].isDetonated) {
            bombs[i] = Bomb(playerLine, playerColumn, millis(), false, 0);
            bombs[i].isDetonated = false;
            bombsNumber++;
            break;
          }
        }

        //we mark with 2 the existence of a bomb in the matrix
        currentMatrix[playerLine][playerColumn] = bombMarker;
      }
    }
    isButtonPressed = false;
  }
}

//?
void generateWalls(byte (*matrix)[matrixSize], byte size);
void resetMatrix(byte (*matrix)[matrixSize]);


void restartGame() {

  if (resetGame) {
    opened = false;
    level = 1;
    precedentLevelScore = 0;
    resetGame = false;
    currentRoom = 0;
    currentMatrix = *matrixPointers[level - 1];
    closePortals();
    podiumDisplayed = false;
    highscoreDisplayed = false;
  }

  for (int index = 0; index <= maximumBombs; index++) {
    bombs[index].isDetonated=true;
  }

  place = 0;
  stopTimeCount = false;
  resetDone = false;
  score = precedentLevelScore;
  isAlive = true;
  isTheEnd = false;
  lives = noOfLives;
  wallsCoverage = levels[level - 1].walls;
  playerLine = startLine;
  playerColumn = startColumn;
  bombsNumber = -1;
  songEnded = false;
  time = levels[level - 1].timeLimit;
  realNoOfEnemies = levels[level - 1].initialNoOfEnemies;
  currentMatrix = *matrixPointers[level - 1];
  if (level == noOfLevels) {
    currentRoom = level;
  } else {
    currentRoom = level - 1;
  }

  //we regenerate walls for the room corresponding to the current level
  if (level == noOfLevels) {
    //to be continued
    resetMatrix(*matrixPointers[level - 1]);
    resetMatrix(*matrixPointers[level]);
    generateWalls(*matrixPointers[level - 1], levels[level - 1].walls);  //for room 3
    generateWalls(*matrixPointers[level], levels[level - 1].walls);      //for room 4

  } else {
    resetMatrix(*matrixPointers[level - 1]);
    generateWalls(*matrixPointers[level - 1], levels[level - 1].walls);  //level 1 means index 0 in our array of pointers
  }
}



void handleInterrupt() {

  static unsigned long interruptTime = 0;  // Retains its value between calls
  interruptTime = micros();                // Get the current time in microseconds

  // If interrupts come faster than the debounce delay, ignore them
  if (interruptTime - lastInterruptTime > debounceDelay * 1000) {  // Convert debounceDelay to microseconds for comparison
    isButtonPressed = true;
  }

  lastInterruptTime = interruptTime;
}
