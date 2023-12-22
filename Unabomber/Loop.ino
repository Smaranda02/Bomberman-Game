
void loop() {

  if (gameStarted) {

    navigateMenu();

    if (isAlive) {

      readJoystickValues();
      checkDirection();

      checkTimePass();
      levelRules();

      checkButtonPress();

      movePlayer();

      for (int index = 0; index < maximumBombs; index++) {
        if (bombs[index].isDetonated == false && bombs[index].bombCoutdownStart != 0) {
          bombs[index].checkBombState();
        }
      }

      lightUpMatrixRules();
      blinkPlayer();
    } else {
      displayEmoji(sadFace);
    }
  }

  //we are navigating through the menu if we haven't pressed the Start Game option yet
  else {
    navigateMenu();
  }
}
