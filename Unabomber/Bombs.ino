void Bomb::checkBombState() {

  //we blink the bomb until detonation time is reached
  if (millis() - bombCoutdownStart >= bombDetonationTime) {
    explodeBomb();
  }

  else {
    blinkBomb();
  }
}


void Bomb::blinkBomb() {

  if (millis() - lastBombBlink >= bombBlinkingTime) {

    //we blink the bomb only if the player has moved from that position
    if (playerLine != bombLine || playerColumn != bombColumn) {
      bombState = !bombState;
      lc.setLed(0, bombLine, bombColumn, bombState);
      lastBombBlink = millis();
    }
  }
}

void Bomb::explodeSound() {
  //we let the the buzzer make a sound only if it hasn't buzzed yet and the sound setting is on
  if (!buzzed && EEPROM.read(soundMemoryLocation)) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    buzzed = true;
  }
}

void Bomb::explodeBomb() {
  startExplosion = millis();

   if (EEPROM.read(soundMemoryLocation)) {
     explodeSound();
   }

  //distroy the affected walls
  distroyWalls();
  //we turn off the bomb
  currentMatrix[bombLine][bombColumn] = 0;
  isDetonated = true;
  bombsNumber--;
}

void Bomb::distroyWalls() {
  byte maxLine = min(7, bombLine + actionArea);
  byte minLine = max(0, bombLine - actionArea);
  byte minColumn = max(0, bombColumn - actionArea);
  byte maxColumn = min(7, bombColumn + actionArea);

  //up to down
  for (int line = minLine; line <= maxLine; line++) {

    if (currentMatrix[line][bombColumn] != bombMarker) {
      if (currentMatrix[line][bombColumn] == 1) {
        //we count the damage done only on the walls (not also the bomb itself)
        wallsCoverage--;
      }
      currentMatrix[line][bombColumn] = explosionMarker;
    }
  }


  //left to right
  for (int column = minColumn; column <= maxColumn; column++) {
    if (currentMatrix[bombLine][column] != bombMarker) {
      if (currentMatrix[bombLine][column] == 1) {
        wallsCoverage--;
      }

      currentMatrix[bombLine][column] = explosionMarker;
    }
  }

  checkPlayerDamage(minLine, maxLine, minColumn, maxColumn, bombLine, bombColumn);
  for (int index = 0; index < realNoOfEnemies; index++) {
    enemies[index].checkEnemyDamage(minLine, maxLine, minColumn, maxColumn, bombLine, bombColumn);
  }
}
