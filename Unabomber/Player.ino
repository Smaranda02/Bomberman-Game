
void blinkPlayer() {

  if (millis() - lastPlayerBlink >= playerBlinkTime && !isTheEnd) {
    playerState = !playerState;  //invert the state of the player LED
    lc.setLed(0, playerLine, playerColumn, playerState);
    lastPlayerBlink = millis();
  }
}


void movePlayer() {
  if (currentMove != -1) {

    byte newPlayerLine = playerLine + directionMatrix[currentMove][0];
    byte newPlayerColumn = playerColumn + directionMatrix[currentMove][1];

    //we let the player move into the new position if there is no wall or if he is in the limits of the matrix
    if ((currentMatrix[newPlayerLine][newPlayerColumn] == 0 || currentMatrix[newPlayerLine][newPlayerColumn] == bombMarker
         || currentMatrix[newPlayerLine][newPlayerColumn] == enemyMarker)
        && (newPlayerLine >= 0 && newPlayerLine <= matrixSize - 1 && newPlayerColumn >= 0 && newPlayerColumn <= matrixSize - 1)) {
      //we first turn off the last player position
      lc.setLed(0, playerLine, playerColumn, 0);

      //update player coordinates
      playerLine = newPlayerLine;
      playerColumn = newPlayerColumn;
    }

    //in the end we ensure that we mark the player as static
    currentMove = -1;
  }
}


void checkTimePass() {

  //if we passed the critical time threshold we warn the player through the LED
  if (time <= superiorTimeWarning && time > inferiorTimeWarning) {
    endOfTimeLedWarning();
  }

  if (millis() - lastTimeCount >= timeDelay && !stopTimeCount) {
    lastTimeCount = millis();
    time--;

    //if we reached the end of time the game ends
    if (time == inferiorTimeWarning) {
      //we force the entering of the condition when the player is dead because the effects are the same
      lives = 0;
      ledState = LOW;
      checkPlayerAlive();
    }
  }

  digitalWrite(ledPin, ledState);
}


void endOfTimeLedWarning() {

  //we blink the red LED with the desrired frequency
  if (millis() - lastLedBlink >= ledTimeDelay) {
    ledState = !ledState;
    lastLedBlink = millis();
  }
}


void levelRules() {

  if (inGame) {

    byte wallDamage;

    //only if we are at level 3 we double wall quantity because we have 2 rooms
    if (level == noOfLevels) {
      wallDamage = levels[level - 1].walls * 2 - wallsCoverage;
    } else {
      wallDamage = levels[level - 1].walls - wallsCoverage;
    }

    score = precedentLevelScore + enemyPoints * (levels[level - 1].initialNoOfEnemies - realNoOfEnemies) + wallDamage;

    //the enemies will follow me into the other rooms
    for (int index = 0; index < realNoOfEnemies; index++) {
      enemies[index].moveEnemy();
    }

    bool inPortal = checkIfInPortal();

    if (inPortal) {

      //we make sure there won't be enemy artifacts in the matrix we leave
      for (int index = 0; index < realNoOfEnemies; index++) {
        currentMatrix[enemies[index].line][enemies[index].column] = 0;
      }

      currentMatrix = teleportMatrix;
      playerLine = startLine;
      playerColumn = startColumn;
    }

    if (wallsCoverage == 0 && realNoOfEnemies == 0) {
      score += time;
      shown = false;
      inGame = false;
      stopTimeCount = true;
      opened = false;
      firstEndMessage = true;
    }
  }

  else {
    prepareNextLevel();
  }
}


void prepareNextLevel() {

  if (level == noOfLevels) {
    checkEepromScore();
    endGame();
  }

  else {
    if (level == noOfLevels - 1) {
      blinkArrow(DownArrow);
    } else {
      blinkArrow(Arrow);
    }

    nextLevelMessage();

    if (!opened) {
      openPortals();
      opened = true;
    }

    bool inPortal = checkIfInPortal();

    /*
    the correct matrix is the matrix corresponding to the next level or matrix 4 in case we just finished the level 2 because matrix 
    4 also corresponds to the third level
    */
    bool correctMatrix = (teleportMatrix == *matrixPointers[level]) || (teleportMatrix == *matrixPointers[level + 1] && level == noOfLevels-1);

    if (inPortal) {
      //if we go to the matrix of the next level we update the necessary parameters
      if (correctMatrix) {
        teleportToNextLevel();
      } else {
        //otherwise we just reset the current matrix and player position
        currentMatrix = teleportMatrix;
        playerLine = 0;
        playerColumn = 0;
      }
    }
  }
}


void teleportToNextLevel() {
  level++;
  currentMatrix = teleportMatrix;
  realNoOfEnemies = levels[level - 1].initialNoOfEnemies;
  generateEnemy(levels[level - 1].initialNoOfEnemies);

  if (level == noOfLevels) {
    wallsCoverage = levels[level - 1].walls * 2;
  } else {
    wallsCoverage = levels[level - 1].walls;
  }
  inGame = true;
  stopTimeCount = false;
  time = levels[level - 1].timeLimit;
  lives = noOfLives;
  playerLine = startLine;
  playerColumn = startColumn;
  precedentLevelScore = score;

  opened = false;
}

void closePortals() {

  //for each room defined we close its corresponding portals
  for (int index = 0; index < noOfRooms; index++) {
    byte size = rooms[index].portalsNumber;

    for (int portal = 0; portal < size; portal++) {

      byte destination = rooms[index].portals[portal].toIndex;
      byte source = rooms[index].portals[portal].fromIndex;

      //we close all the portals from one room to another except for the portal from room 3 -> 4 and vice versa
      if ((destination == noOfLevels && source != noOfLevels - 1) || (destination == noOfLevels - 1 && source != noOfLevels)) {
        /*
        we also close only the portals from lower levels to greater ones
        we don't want to close portal from room 2 -> 1 for example because there is no way we can get to room 2 if we did't get through
        */
        if (destination > source) {
          rooms[index].portals[portal].isOpen = false;
        }
      }
    }
  }
}


//after we complete all the 3 levels
void endGame() {

  displayEmoji(happyEmoji);
  isTheEnd = true;

  //we first wait for the message that tells the user if he is on the podium to end
  if (anotherMessage) {
    podiumMessage();
    shown = false;
  }

  else {

    if (!shown) {
      shown = true;
      lcd.clear();
    }

    if (firstEndMessage) {
      displayFirstEndMessage();

    } else {
      displayScoreMessage();
    }


    //after user's button press we change the displayed message 
    if (isButtonPressed) {
      if (firstEndMessage) {
        firstEndMessage = false;
        shown = false;
      } else {
        //after the last message was displayed we get back to the main menu
        inMenu = true;
        currentMenu = MainMenu;
        currentOption = 0;
        shown = false;
        gameStarted = false;
        resetGame = true;
      }
      isButtonPressed = false;
    }
  }
}

void displayFirstEndMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Congrats! You"));
  lcd.setCursor(0, 1);
  lcd.print(F("reached the end"));
}

void displayScoreMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Your final score"));
  lcd.setCursor(0, 1);
  lcd.print(F("was : "));
  lcd.setCursor(5, 1);
  lcd.print(score);
}

void openPortals() {

  //portals from bigger levels to lower levels are already open
  // we only need to open the ones from lower levels to bigger ones
  // we open all the portals towards the room corresponding to the next level

  for (int index = 0; index < noOfRooms; index++) {
    byte size = rooms[index].portalsNumber;

    for (int portal = 0; portal < size; portal++) {
      if (rooms[index].portals[portal].toIndex == level || (level == 2 && rooms[index].portals[portal].toIndex == 3)) {
        rooms[index].portals[portal].isOpen = true;
      }
    }
  }
}


bool checkIfInPortal() {

  byte size = rooms[currentRoom].portalsNumber;

  for (int index = 0; index < size; index++) {

    int line = rooms[currentRoom].portals[index].line;
    int column = rooms[currentRoom].portals[index].column;

    //we are in the portal if the portal is open and we make the correct move towards the correct matrix
    if (currentMove == rooms[currentRoom].portals[index].transitionMove
        && rooms[currentRoom].portals[index].isOpen
        && currentMatrix == rooms[currentRoom].portals[index].fromMatrix) {
      if ((line != -1 && playerLine == line) || (column != -1 && playerColumn == column)) {

        //we memorate the destination matrix the portal leads us to and we update the current room
        teleportMatrix = rooms[currentRoom].portals[index].toMatrix;
        currentRoom = rooms[currentRoom].portals[index].toIndex;
        return true;
      }
    }
  }

  return false;
}



void nextLevelMessage() {
  if (!shown) {
    shown = true;
    lcd.clear();
  }
  lcd.setCursor(0, 0);
  lcd.print(F("Follow the arrow"));
  lcd.setCursor(0, 1);
  lcd.print(F("to the next room"));
}


//after a bomb is detonated we check is player was hit 
void checkPlayerDamage(byte minLine, byte maxLine, byte minColumn, byte maxColumn, byte bombLine, byte bombColumn) {

  if (lives > 0) {
    if ((playerLine <= maxLine && playerLine >= minLine && playerColumn == bombColumn)
        || (playerColumn <= maxColumn && playerColumn >= minColumn && playerLine == bombLine)) {
      lives--;
    }
  }

  checkPlayerAlive();
}

void checkPlayerAlive() {
  if (lives == 0) {
    isAlive = false;
    shown = false;
    inMenu = true;
    currentOption = 0;

    //we check if the player score was greater than the current ones
    checkEepromScore();
    //play the "Game over" song
    songEnded = false;
    //and we display the restart game menu
    checkGameRestart();
  }
}

void checkEepromScore() {

  unsigned int first, second, third;

  //retreive the top scores
  EEPROM.get(firstPlayerMemoryLocation + maxNameCharacters, first);
  EEPROM.get(secondPlayerMemoryLocation + maxNameCharacters, second);
  EEPROM.get(thirdPlayerMemoryLocation + maxNameCharacters, third);


  //compare the current score with the existing ones
  if (score > first) {
    place = 1;
    updateEepromScore(firstPlayerMemoryLocation);
    podiumMessage();

  } else if (score > second) {
    place = 2;
    updateEepromScore(secondPlayerMemoryLocation);
    podiumMessage();
  } else if (score > third) {
    place = 3;
    updateEepromScore(thirdPlayerMemoryLocation);
    podiumMessage();
  }
}

void updateEepromScore(byte memoryLocation) {
  EEPROM.put(memoryLocation, name);
  EEPROM.update(memoryLocation + maxNameCharacters, score);
}


void podiumMessage() {

  //podiumDisplayed flag ensures that we display only one time the annouce that a player is on the podium
  if (!podiumDisplayed) {
    if (lastMessageDisplay == 0) {
      lastMessageDisplay = millis();
    }

    //we ensure the congratulations message is displayed for a certain period of time
    if (millis() - lastMessageDisplay >= messageDisplayTime) {
      anotherMessage = false;
      podiumDisplayed = true;
      lastMessageDisplay = 0;
    }

    else {
      anotherMessage = true;
      lcd.clear();

      if (place == 1) {
        printHighscoreMessage();
      }

      else {
        printPodiumMessage();
      }
    }
  }
}

void printHighscoreMessage() {
  lcd.setCursor(0, 0);
  lcd.print(F("You've just set"));
  lcd.setCursor(0, 1);
  lcd.print(F("a new highscore"));
}

void printPodiumMessage() {
  lcd.setCursor(0, 0);
  lcd.print(F("You're on the"));
  lcd.setCursor(0, 1);
  lcd.print(F("podium.Congrats!"));
}