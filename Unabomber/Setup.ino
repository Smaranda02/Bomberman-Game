void setup() {

  pinMode(ledPin, OUTPUT);

  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false);                 // turn off power saving, enables display
  lc.setIntensity(0, EEPROM.read(matrixBrightnessMemoryLocation));  // sets brightness (0~15 possible values)
  lc.clearDisplay(0);                    // clear screen

  pinMode(buttonPin, INPUT_PULLUP);  // activate pull-up resistor on the buttonPin
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING);

  //to initialize the random number generator with a fairly random input on subsequent executions of a sketch
  randomSeed(analogRead(0));

  for (int index = 0; index < noOfRooms; index++) {   
    currentMatrix = *matrixPointers[index];
    generateWalls(*matrixPointers[index], levels[index].walls);
  }

  //generate walls for room 4
  generateWalls(*matrixPointers[noOfRooms - 1], levels[noOfLevels - 1].walls);

  //generate enemies for level 1
  generateEnemy(levels[level - 1].initialNoOfEnemies);
  realNoOfEnemies = levels[level - 1].initialNoOfEnemies;

  currentMatrix = *matrixPointers[level - 1];

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //create the custom characters
  lcd.createChar(0, heart);
  lcd.createChar(1, enemy);
  lcd.createChar(2, door);
  lcd.createChar(3, tick);

  setBrightness(EEPROM.read(lcdBrightnessMemoryLocation));
  greeted = false;
  nameIndex = -1;
}
