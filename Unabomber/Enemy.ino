void Enemy::moveEnemy() {
  if (realNoOfEnemies) {
    if (millis() - lastMove >= moveInterval) {

      this->checkPlayerMeeting();

      lastMove = millis();

      byte move = random(0, 4);  //represing UP, DOWN, LEFT, RIGHT

      byte line = this->line + directionMatrix[move][0];
      byte column = this->column + directionMatrix[move][1];

      //we check if the current led is a valid position
      if ( (currentMatrix[line][column] == 0 || currentMatrix[line][column] == bombMarker || 
            (currentMatrix[line][column] == playerLine && currentMatrix[line][column] == playerColumn) )
            
             && (line >= 0 && line <= matrixSize - 1 && column >= 0 && column <= matrixSize - 1)) {
        currentMatrix[this->line][this->column] = 0;  //turn off the old enemy
        currentMatrix[line][column] = enemyMarker;              //this is how we mark the enemy
        //lc.setLed(0, line, column, 1);                // turn on the current enemy
        //in the end we update the enemy line and column
        this->line = line;
        this->column = column;
      }
    }
  }
}

void checkPlayerAlive();

void Enemy::checkPlayerMeeting() {
  if (playerLine == this->line && playerColumn == this->column) {
    if (EEPROM.read(soundMemoryLocation)) {
      tone(buzzerPin, buzzerTone, menuInteractionDuration);
    }
    lives--;
    checkPlayerAlive();
  }
}



void Enemy::checkEnemyDamage(byte minLine, byte maxLine, byte minColumn, byte maxColumn, byte bombLine, byte bombColumn) {

  if ((this->line <= maxLine && this->line >= minLine && this->column == bombColumn)
      || (this->column <= maxColumn && this->column >= minColumn && this->line == bombLine)) {
    realNoOfEnemies--;
    currentMatrix[this->line][this->column] = 0;  //turn off the old enemy
  }
}




bool checkGeneratedEnemy(int line, int column) {

  //we check we don't create an enemy around the player
  if (line == playerLine) {
    if (abs(playerColumn - column) == 1 || playerColumn == column) {
      return false;
    }
  } else if (column == playerColumn) {
    if (abs(playerLine - line) == 1 || playerLine == line) {
      return false;
    }
  }
  //we check the LED is not already ON
  else if (currentMatrix[line][column] == 1) {
    return false;
  }

  return true;
}


void generateEnemy(byte enemiesNumber) {

  for (int index = 0; index < enemiesNumber; index++) {

    int randomLine = random(0, 8);
    int randomColumn = random(0, 8);

    volatile bool isEnemyOk;

    isEnemyOk = checkGeneratedEnemy(randomLine, randomColumn);

    if (isEnemyOk) {
      currentMatrix[randomLine][randomColumn] = enemyMarker;
      enemies[++enemiesIndex] = Enemy(randomLine, randomColumn);
    } else {
      index--;
    }
  }
}
