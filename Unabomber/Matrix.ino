void lightUpMatrixRules() {
  if (inGame) {
    cleanMatrix = false;
    lightUpMatrix();
  } else {
    if (!cleanMatrix) {
      lightUpMatrix();
      cleanMatrix = true;
    }

    if (level != noOfLevels) {
      if (level == 2) {
        blinkArrow(DownArrow);
      } else {
        blinkArrow(Arrow);
      }
    }
  }
}



void lightUpMatrix() {
  for (int line = 0; line < matrixSize; line++)
    for (int column = 0; column < matrixSize; column++) {
      //we light the current LED only if it's different from the player and the bomb
      if ((column != playerColumn || line != playerLine) && currentMatrix[line][column] != bombMarker && currentMatrix[line][column] != 3
          && currentMatrix[line][column] != enemyMarker && currentMatrix[line][column] != explosionMarker) {
        lc.setLed(0, line, column, currentMatrix[line][column]);
      }

      else if (currentMatrix[line][column] == enemyMarker) {
        lc.setLed(0, line, column, true);
        delay(5);
        lc.setLed(0, line, column, false);
      }

      else if (currentMatrix[line][column] == explosionMarker) {

        if (lastExplosion == 0) {
          lastExplosion = millis();
        }

        if (millis() - lastExplosion >= explosionTime) {
          lastExplosion = 0;
          for (int l = 0; l < matrixSize; l++)
            for (int col = 0; col < matrixSize; col++) {
              if (currentMatrix[l][col] == explosionMarker) {
                currentMatrix[l][col] = 0;
              }
            }
        } else {
          lc.setLed(0, line, column, true);
          delay(2);
          lc.setLed(0, line, column, false);
        }
      }
    }
}




void resetMatrix(byte (*matrix)[matrixSize]) {
  for (int line = 0; line < matrixSize; line++)
    for (int column = 0; column < matrixSize; column++) {
      matrix[line][column] = 0;
    }
}


void blinkArrow(byte arrow[arrowSize][2]) {
  if (millis() - lastArrowBlink >= playerBlinkTime) {
    arrowState = !arrowState;
    for (int line = 0; line < arrowSize; line++) {
      lc.setLed(0, arrow[line][0], arrow[line][1], arrowState);
    }
    lastArrowBlink = millis();
  }
}


void generateWalls(byte (*matrix)[matrixSize], byte size) {
byte nr = 0;
  for (int index = 0; index < size; index++) {

    int randomLine = random(0, 8);
    int randomColumn = random(0, 8);

    volatile bool isWallOk;

    isWallOk = checkGeneratedWall(randomLine, randomColumn);

    if (isWallOk) {
      matrix[randomLine][randomColumn] = 1;
    } else {
      index--;
    }
  }

}

bool checkGeneratedWall(int line, int column) {
  //we check we don't create walls around the player
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


void displayEmoji(byte matrix[matrixSize][matrixSize]) {
  for (int line = 0; line < matrixSize; line++)
    for (int column = 0; column < matrixSize; column++) {
      lc.setLed(0, line, column, pgm_read_byte(&matrix[line][column]));
    }
}