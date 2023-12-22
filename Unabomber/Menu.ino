void navigateMenu() {
  //when we first power up the game
  if (startGreet == 0) {
    startGreet = millis();
  }

  if (!greeted) {
    if (millis() - startGreet >= greetingDisplayTime) {
      inMenu = true;
      lcd.clear();
      greeted = true;
    } else {
      displayGreeting();
    }
  }

  else {
    if (inMenu) {
      checkMenuOption();
    } else if (inGame) {
      displayGameDetails();
    }
  }
}

void displayGreeting() {
  lcd.setCursor(0, 0);
  lcd.print(F("WELCOME TO"));
  lcd.setCursor(0, 1);
  lcd.print(F("     UNABOMBER"));
}


void checkMenuOption() {

  switch (currentMenu) {
    case MainMenu:
      mainMenu();
      break;
    case StartMenu:
      StartGameMenu();
      break;
    case AboutGameMenu:
      AboutMenu();
      break;
    case HighscoreMenu:
      HighscoresMenu();
      break;
    case GameSettingsMenu:
      SettingsMenu();
      break;
    case InstructionsMenu:
      HowToPlayMenu();
      break;
    case GameRestartMenu:
      checkGameRestart();
      break;
    case BrightnessControlMenu:
      brightnessControl();
      break;
    case EnterNameMenu:
      enterNameMenu();
      break;
    case SaveNameMenu:
      saveNameMenu();
      break;
    case SoundMenu:
      soundMenu();
      break;
    case ResetHighscoresMenu:
      resetHighscoresMenu();
      break;
  }
}


void mainMenu() {
  currentMenu = MainMenu;

  //clear LCD before first diplay
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  //we update if needed the currentOption
  menuSize = mainMenuSize;
  menuPointer = MENU;
  checkSelection();
  displayMenu();
  displayEmoji(menuEmoji);

  //only if we confirm our option by pressing the button we go to that option
  if (isButtonPressed) {

    menuInteractionSound();
    isButtonPressed = false;

    switch (currentOption) {
      case 0:
        {
          shown = false;
          currentOption = 0;
          StartGameMenu();
        }
        break;
      case 1:
        {
          shown = false;
          currentOption = 0;
          AboutMenu();
        }
        break;

      case 2:
        {
          shown = false;
          currentOption = 0;
          HighscoresMenu();
        }

        break;

      case 3:
        {
          shown = false;
          currentOption = 0;
          SettingsMenu();
        }

        break;

      case 4:
        {
          shown = false;
          currentOption = 0;
          HowToPlayMenu();
        }

        break;
    }
  }
}


void StartGameMenu() {

  currentMenu = StartMenu;
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  menuSize = startGameMenuSize;
  checkSelection();
  printArrow(1, 0, 1, 9);
  displayStartGame();
  displayEmoji(startEmoji);


  if (isButtonPressed) {

    isButtonPressed = false;
    switch (currentOption) {

      case 0:
        {
          shown = false;
          gameStarted = true;
          inGame = true;
          displayGameDetails();
        }
        break;
      case 1:
        {
          shown = false;
          currentOption = 0;
          menuInteractionSound();
          mainMenu();
        }
        break;
    }
  }
}


void AboutMenu() {
  currentMenu = AboutGameMenu;

  if (!shown) {
    lcd.clear();
    shown = true;
  }


  menuSize = aboutMenuSize;
  checkSelection();
  menuPointer = About;
  displayMenu();
  displayEmoji(aboutEmoji);


  if (isButtonPressed) {
    if (currentOption == menuSize - 1) {
      isButtonPressed = false;
      currentMenu = 0;
      currentOption = 0;
      shown = false;
      menuInteractionSound();
    }
    isButtonPressed = false;
  }
}


void scrollMessages(const char* message) {
  byte length = strlen(message);
  byte line;
  byte column;

  if (currentOption % 2 == 0) {
    column = 1;
    line = 0;
  } else {
    line = 1;
    column = 1;
  }


  if (scrollIndex <= length) {

    lcd.setCursor(column, line);
    lcd.print(message + scrollIndex);

    //we clear the rest of the LCD to the right edge in order to erase the charcaters displayed in the past
    if (strlen(message + scrollIndex) < 16) {
      clearLCD(message + scrollIndex);
    }

    if (millis() - lastScroll >= scrollTime) {
      scrollIndex++;
      lastScroll = millis();
    }
  }

  else {
    scrollIndex = 0;
  }
}

void checkSelection() {

  readJoystickValues();
  checkDirection();


  //moving the joystick down means incrementing the current option and up means decrementing it 
  switch (currentMove) {
    //UP
    case UP:
      {
        if (currentOption > 0) {
          currentOption--;
          currentMove = -1;
        }
      }
      break;

    //DOWN
    case DOWN:
      {
        if (currentOption < menuSize - 1) {
          currentOption++;
          currentMove = -1;
        }
      }
      break;
  }
}

void displayMenu() {

  byte first;
  byte second;

  char buffer[30];

  if (currentOption % 2 == 0) {
    first = currentOption;
    second = currentOption + 1;

    //if (strlen(menuPointer[currentOption]) > 16) {
    strcpy_P(buffer, (char*)pgm_read_word(&menuPointer[currentOption]));

    if (strlen(buffer) > 16) {

      if (scrollOnFirst == false) {
        //at a change of scroll element we reset the scroll Index
        scrollIndex = 0;
      }
      scrollOnFirst = true;
    } else {
      scrollOnFirst = false;
    }
    scrollOnSecond = false;


  }

  else {
    first = currentOption - 1;
    second = currentOption;

    //if (strlen(menuPointer[currentOption]) > 16) {
    strcpy_P(buffer, (char*)pgm_read_word(&menuPointer[currentOption]));

    if (strlen(buffer) > 16) {
      if (scrollOnSecond == false) {
        scrollIndex = 0;
      }
      scrollOnSecond = true;
    } else {
      scrollOnSecond = false;
    }
    scrollOnFirst = false;
  }

  printArrow(0, 0, 1, 0);

  char bufferFirst[30];
  char bufferSecond[30];
  //lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&menuPointer[second])));  // Read PROGMEM pointers
  strcpy_P(bufferFirst, (char*)pgm_read_word(&menuPointer[first]));
  if (second <= menuSize - 1) {
    strcpy_P(bufferSecond, (char*)pgm_read_word(&menuPointer[second]));
  }

  if (!scrollOnFirst) {
    lcd.setCursor(1, 0);
    lcd.print(bufferFirst);
    //we clear the artifacts from the last printings on the display (About appears Aboutings)
    clearLCD(bufferFirst);
  } else {
    scrollMessages(bufferFirst);
  }

  if (!scrollOnSecond) {
    if (second <= menuSize - 1) {
      lcd.setCursor(1, 1);
      lcd.print(bufferSecond);
      clearLCD(bufferSecond);
    } else {
      lcd.setCursor(1, 1);
      lcd.print(F("                "));
    }
  }

  else {
    scrollMessages(bufferSecond);
  }
}


void clearLCD(char* message) {
  byte length = strlen(message);
  for (byte i = length; i < 16; i++) {
    lcd.print(" ");
  }
}


void displayStartGame() {
  lcd.setCursor(0, 0);
  lcd.print(F("Wanna start ?"));
  lcd.setCursor(0, 1);

  lcd.setCursor(1, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&StartGame[0])));  // Read PROGMEM pointers
  lcd.setCursor(10, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&StartGame[1])));  // Read PROGMEM pointers
}

void printArrow(byte line1, byte column1, byte line2, byte column2) {
  if (currentOption % 2 == 0) {
    lcd.setCursor(column2, line2);
    lcd.write(' ');
    lcd.setCursor(column1, line1);

  } else {
    lcd.setCursor(column1, line1);
    lcd.write(' ');
    lcd.setCursor(column2, line2);
  }
  lcd.print(arrow);
}


void displayGameDetails() {

  if (!shown) {
    lcd.clear();
    restartGame();
    turnOffMatrix();
    songEnded = false;
    shown = true;
  }

  inMenu = false;

  if (!songEnded && EEPROM.read(soundMemoryLocation) && level == 1) {
    playMelody(StartMelody, sizeof(StartMelody) / sizeof(StartMelody[0]));
  }


  if (!anotherMessage) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(F("Score:"));
    lcd.setCursor(6, 0);
    lcd.print(score);


    lcd.setCursor(10, 0);
    lcd.write(byte(0));  // Display the custom character from the specified index in the special characters array
    lcd.setCursor(11, 0);
    lcd.print(lives);


    lcd.setCursor(13, 0);
    lcd.write(byte(1));
    lcd.setCursor(14, 0);
    lcd.print(F(":"));
    lcd.setCursor(15, 0);
    lcd.print(realNoOfEnemies);


    lcd.setCursor(0, 1);
    lcd.print(F("Walls:"));
    lcd.setCursor(6, 1);
    lcd.print(wallsCoverage);

    lcd.setCursor(9, 1);
    lcd.write(byte(2));
    lcd.setCursor(10, 1);
    lcd.print(currentRoom + 1);

    lcd.setCursor(12, 1);
    lcd.print(time);
    lcd.setCursor(15, 1);
    lcd.print(F("s"));
  }
}

void HighscoresMenu() {
  currentMenu = HighscoreMenu;

  menuSize = 4;
  checkSelection();
  printArrow(0, 0, 1, 0);
  displayHighscores();
  displayEmoji(highscoresEmoji);


  if (isButtonPressed) {
    if (currentOption == menuSize - 1) {
      isButtonPressed = false;
      currentMenu = 0;
      currentOption = 0;
      shown = false;
      turnOffMatrix();
      menuInteractionSound();
    }
    isButtonPressed = false;
  }
}

void displayHighscores() {

  char firstName[maxNameCharacters + 1];
  char secondName[maxNameCharacters + 1];
  char thirdName[maxNameCharacters + 1];

  EEPROM.get(firstPlayerMemoryLocation, firstName);
  EEPROM.get(secondPlayerMemoryLocation, secondName);
  EEPROM.get(thirdPlayerMemoryLocation, thirdName);

  int first, second, third;

  EEPROM.get(firstPlayerMemoryLocation + maxNameCharacters, first);
  EEPROM.get(secondPlayerMemoryLocation + maxNameCharacters, second);
  EEPROM.get(thirdPlayerMemoryLocation + maxNameCharacters, third);

  String firstPlayer = "#1 " + String(firstName) + " " + String(first);
  String secondPlayer = "#2 " + String(secondName) + " " + String(second);
  String thirdPlayer = "#3 " + String(thirdName) + " " + String(third);

  char Back[5] = "Back";

  if (!shown) {
    lcd.clear();
    shown = true;
  }

  if (currentOption % 2 == 0) {
    first = currentOption;
    second = currentOption + 1;
  }

  else {
    first = currentOption - 1;
    second = currentOption;
  }

  if (first == 0) {
    lcd.setCursor(1, 0);
    lcd.print(firstPlayer);
    clearLCDString(firstPlayer);
    lcd.setCursor(1, 1);
    lcd.print(secondPlayer);
    clearLCDString(secondPlayer);

  } else {
    lcd.setCursor(1, 0);
    lcd.print(thirdPlayer);
    clearLCDString(thirdPlayer);
    lcd.setCursor(1, 1);
    lcd.print(Back);
    clearLCD(Back);
  }
}

void clearLCDString(String string) {
  for (int index = string.length() + 1; index < 16; index++) {
    lcd.print(' ');
  }
}

void checkGameRestart() {

  currentMenu = GameRestartMenu;

  if (!songEnded && EEPROM.read(soundMemoryLocation)) {
    playMelody(EndMelody, sizeof(EndMelody) / sizeof(EndMelody[0]));
  }


  if (anotherMessage) {
    podiumMessage();
    shown = false;
  }


  else {
    if (!shown) {
      shown = true;
      lcd.clear();
    }


    menuSize = restartGameMenuSize;
    checkSelection();
    printArrow(1, 0, 1, 9);
    displayRestartGame();


    if (isButtonPressed) {
      isButtonPressed = false;
      menuInteractionSound();

      switch (currentOption) {

        case 0:
          {
            shown = false;
            gameStarted = true;
            inGame = true;
            displayGameDetails();
          }
          break;
        case 1:
          {
            shown = false;
            gameStarted = false;
            currentOption = 0;
            resetGame = true;
            mainMenu();
          }
          break;
      }
    }
  }
}


void displayRestartGame() {
  lcd.setCursor(0, 0);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(gameOverMessage));

  lcd.setCursor(1, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&RestartGame[0])));

  lcd.setCursor(10, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&RestartGame[1])));
}


void SettingsMenu() {
  currentMenu = GameSettingsMenu;
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  menuSize = settingsMenuSize;
  menuPointer = Settings;
  checkSelection();
  displayMenu();
  displayEmoji(settingsEmoji);

  if (isButtonPressed) {

    isButtonPressed = false;
    menuInteractionSound();

    switch (currentOption) {

      case 0:
        {
          shown = false;
          currentOption = 0;
          controlVariable = lcdSelection;
          brightnessControl();
        }
        break;
      case 1:
        {
          shown = false;
          currentOption = 0;
          controlVariable = matrixSelection;
          brightnessControl();
        }
        break;
      case 2:
        {
          shown = false;
          currentLetter = 0;
          //we reset the name first
          for (int index = 0; index < maxNameCharacters; index++) {
            name[index] = ' ';
          }
          enterNameMenu();
        }
        break;
      case 3:
        {
          shown = false;
          currentOption = 0;
          soundMenu();
        }
        break;
      case 4:
        {
          shown = false;
          currentOption = 0;
          resetHighscoresMenu();
        }
        break;
      case 5:
        {
          shown = false;
          currentOption = 0;
          turnOffMatrix();
          mainMenu();
        }
        break;
    }
  }
}

void soundMenu() {

  currentMenu = SoundMenu;

  if (!shown) {
    lcd.clear();
    shown = true;
  }

  checkSelection();
  printArrow(0, 0, 1, 0);
  displaySoundMenu();
  if (soundValue) {
    displayEmoji(soundEmoji);
  } else {
    displayEmoji(noSoundEmoji);
  }

  if (isButtonPressed) {

    isButtonPressed = false;
    menuInteractionSound();

    if (currentOption == 0) {
      soundValue = !soundValue;
      EEPROM.update(soundMemoryLocation, soundValue);
    }

    else {
      shown = false;
      currentOption = 0;
      SettingsMenu();
    }
  }
}

void displaySoundMenu() {

  lcd.setCursor(1, 0);
  lcd.print(F("Sound : "));
  lcd.setCursor(9, 0);
  if (soundValue) {
    lcd.print(F("ON "));
  } else {
    lcd.print(F("OFF"));
  }

  lcd.setCursor(1, 1);
  lcd.print(F("Back"));
}

void enterNameMenu() {

  currentMenu = EnterNameMenu;
  displayAlphabet();

  checkLetterSelection();
  checkCurrentLetter();


  if (isButtonPressed) {

    isButtonPressed = false;


    //any letter
    if (currentLetter >= 0 && currentLetter <= 25) {
      if (nameIndex < maxNameCharacters - 1) {
        nameIndex++;
        name[nameIndex] = currentLetterValue;
      }
    }

    //N
    else if (currentLetter == 31) {
      shown = false;
      currentOption = 0;
      nameIndex = -1;
      for (int index = 0; index < maxNameCharacters; index++) {
        name[index] = ' ';
      }
      SettingsMenu();
    }

    //Y
    else if (currentLetter == 29) {
      shown = false;
      saveNameMenu();
    }

    //<
    else if (currentLetter == 27) {
      name[nameIndex] = ' ';
      if (nameIndex > 0) {
        nameIndex--;
      }
    }
  }
}


void resetHighscoresMenu() {

  currentMenu = ResetHighscoresMenu;
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  checkSelection();
  printArrow(0, 0, 1, 0);
  displayResetHighscores();

  if (isButtonPressed) {

    isButtonPressed = false;

    if (currentOption == 0) {

      //we check the transition from resetDone false -> true in order to update the EEPROM only once
      if (!resetDone) {
        resetHighscoreValues();
      }

      resetDone = true;
    }

    else {
      shown = false;
      currentOption = 0;
      SettingsMenu();
    }
  }
}


void resetHighscoreValues() {

  //reset the names
  char emptyName[] = "EMPTY";
  EEPROM.put(firstPlayerMemoryLocation, emptyName);
  EEPROM.put(secondPlayerMemoryLocation, emptyName);
  EEPROM.put(thirdPlayerMemoryLocation, emptyName);

  //reset the scores
  EEPROM.update(firstPlayerMemoryLocation + maxNameCharacters, 0);
  EEPROM.update(secondPlayerMemoryLocation + maxNameCharacters, 0);
  EEPROM.update(thirdPlayerMemoryLocation + maxNameCharacters, 0);
}

void displayResetHighscores() {

  lcd.setCursor(1, 0);
  if (!resetDone) {
    lcd.print(F("Press to reset"));
  } else {
    lcd.print(F("Reset done     "));
    lcd.setCursor(12, 0);
    lcd.write(byte(3));
  }

  lcd.setCursor(1, 1);
  lcd.print(F("Back "));
}


void saveNameMenu() {
  currentMenu = SaveNameMenu;
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  menuSize = saveNameMenuSize;
  checkSelection();
  printArrow(1, 0, 1, 9);
  displaySaveName();


  if (isButtonPressed) {

    isButtonPressed = false;

    switch (currentOption) {

      //after save we get back to the menu
      case 0:
        {
          shown = false;
          currentOption = 0;
          mainMenu();
        }
        break;
      case 1:
        {
          shown = false;
          enterNameMenu();
        }
        break;
    }
  }
}

//!!!!
void displaySaveName() {

  lcd.setCursor(0, 0);
  lcd.print(F("Your name: "));
  lcd.setCursor(11, 0);
  for (int index = 0; index < maxNameCharacters; index++) {
    lcd.print(name[index]);
  }

  lcd.setCursor(1, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&EnterName[0])));

  lcd.setCursor(10, 1);
  lcd.print(reinterpret_cast<const __FlashStringHelper*>(pgm_read_word(&EnterName[1])));
}


//we blink the selected letter
void checkCurrentLetter() {

  if (millis() - lastLetterBlink >= letterBlinkTime) {
    letterState = !letterState;
    lastLetterBlink = millis();
  }

  if (currentLetter <= 25) {
    currentLetterValue = char('A' + currentLetter);
  }

  else {
    switch (currentLetter) {
      case 27:
        currentLetterValue = '<';
        break;
      case 29:
        currentLetterValue = 'Y';
        break;
      case 30:
        currentLetterValue = '/';
        break;
      case 31:
        currentLetterValue = 'N';
        break;
      default:
        currentLetterValue = ' ';
        break;
    }
  }

  if (currentLetter >= 0 && currentLetter <= 15) {
    if (letterState) {
      alphabet1[currentLetter] = currentLetterValue;
    } else {
      alphabet1[currentLetter] = ' ';
    }
  }

  else {
    if (letterState) {
      alphabet2[currentLetter % 16] = currentLetterValue;
    } else {
      alphabet2[currentLetter % 16] = ' ';
    }
  }
}


void checkLetterSelection() {

  readJoystickValues();
  checkDirection();

  if (currentMove != -1) {

    switch (currentMove) {
      //UP
      case UP:
        {
          if (currentLetter > 15) {
            changeLetter();
            currentLetter -= 16;
          }
          currentMove = -1;
        }
        break;

      //DOWN
      case DOWN:
        {
          if (currentLetter < 16) {
            changeLetter();
            currentLetter += 16;
          }
          currentMove = -1;
        }
        break;

      //RIGHT
      case RIGHT:
        {
          if (currentLetter % 16 < 15) {
            changeLetter();
            currentLetter++;
          }
          currentMove = -1;
        }
        break;

      //LEFT
      case LEFT:
        {
          if (currentLetter % 16 > 0) {
            changeLetter();
            currentLetter--;
          }
          currentMove = -1;
        }
        break;
    }
  }
}


void changeLetter() {

  if (currentLetter > 15) {
    alphabet2[currentLetter % 16] = currentLetterValue;
  } else {
    alphabet1[currentLetter] = currentLetterValue;
  }
}

void brightnessControl() {

  currentMenu = 7;
  if (!shown) {
    shown = true;
    lcd.clear();
  }

  menuSize = joystickControlMenuSize;
  checkSelection();
  menuPointer = JoystickControl;
  displayMenu();

  if (currentOption == 0) {
    brightnessValues();
  }

  if (isButtonPressed && currentOption == 1) {
    isButtonPressed = false;
    menuInteractionSound();
    shown = false;
    currentOption = 0;
    SettingsMenu();
  }
}

void brightnessValues() {

  readJoystickValues();
  checkDirection();

  turnOnMatrix();

  switch (currentMove) {
    case RIGHT:
      {
        //lcd
        if (controlVariable == lcdSelection) {
          if (backLightValue <= maxLcdBrightness - lcdBrightnessStep) {
            backLightValue += lcdBrightnessStep;
          }
        } else {
          if (matrixBrightness <= maxMatrixBrightness - matrixBrightnessStep) {
            matrixBrightness += matrixBrightnessStep;
          }
        }
        currentMove = -1;
      }
      break;

    case LEFT:
      {
        if (controlVariable == lcdSelection) {
          if (backLightValue >= minLcdBrightness + lcdBrightnessStep) {
            backLightValue -= lcdBrightnessStep;
          }
        } else {
          if (matrixBrightness >= minMatrixBrightness + matrixBrightnessStep) {
            matrixBrightness -= matrixBrightnessStep;
          }
        }
        currentMove = -1;
      }
      break;
  }

  setBrightness(backLightValue);
  EEPROM.update(matrixBrightnessMemoryLocation, matrixBrightness);
  lc.setIntensity(0, matrixBrightness);
}

void turnOnMatrix() {
  for (int i = 0; i < matrixSize; i++)
    for (int j = 0; j < matrixSize; j++) {
      lc.setLed(0, i, j, 1);
    }
}


void turnOffMatrix() {
  for (int i = 0; i < matrixSize; i++)
    for (int j = 0; j < matrixSize; j++) {
      lc.setLed(0, i, j, 0);
    }
}


void HowToPlayMenu() {
  currentMenu = InstructionsMenu;
  if (!shown) {
    lcd.clear();
    shown = true;
  }

  menuSize = howToMenuSize;
  menuPointer = HowTo;
  checkSelection();
  displayMenu();
  displayEmoji(howToEmoji);

  if (isButtonPressed) {
    if (currentOption == menuSize - 1) {
      isButtonPressed = false;
      menuInteractionSound();
      currentMenu = MainMenu;
      currentOption = 0;
      shown = false;
    }
    isButtonPressed = false;
  }
}
