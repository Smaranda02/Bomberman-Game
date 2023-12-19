
//driver connections
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;

byte matrix1[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte matrix2[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


byte matrix3[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};



byte matrix4[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


byte (*matrixPointers[4])[matrixSize][matrixSize] = {
  &matrix1,
  &matrix2,
  &matrix3,
  &matrix4
};

byte (*currentMatrix)[matrixSize] = matrix1;
byte (*teleportMatrix)[matrixSize];

const byte sadFace[matrixSize][matrixSize] PROGMEM = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 }
};

const byte settingsEmoji[matrixSize][matrixSize] PROGMEM = {
  { 0, 0, 0, 0, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 1, 1, 1 },
  { 0, 0, 0, 0, 1, 1, 1, 1 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0 },
  { 1, 1, 0, 0, 0, 0, 0, 0 }
};

const byte highscoresEmoji[matrixSize][matrixSize] PROGMEM = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 0, 0, 0, 0, 1, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 }
};


const byte howToEmoji[matrixSize][matrixSize] PROGMEM = {
  { 0, 0, 1, 1, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 }
};


const byte aboutEmoji[matrixSize][matrixSize] PROGMEM = {
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 1, 1, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 1, 0, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0 }
};

const byte soundEmoji[matrixSize][matrixSize] PROGMEM = {
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 0, 1},
  {1, 1, 1, 0, 0, 1, 0, 1},
  {1, 1, 1, 0, 0, 1, 0, 1},
  {0, 1, 1, 0, 0, 1, 0, 1},
  {0, 0, 1, 0, 1, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 0}
};


const byte noSoundEmoji[matrixSize][matrixSize] PROGMEM = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 1, 0, 0, 1},
  {1, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 1, 0, 0, 1},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const byte menuEmoji[matrixSize][matrixSize] PROGMEM = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 1, 0, 0, 0, 0, 1, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 }
};


const byte startEmoji[matrixSize][matrixSize] PROGMEM= {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 1, 1, 1},
  {1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 1, 0, 1},
  {1, 0, 1, 1, 0, 1, 0, 1},
  {1, 0, 0, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const byte happyEmoji[matrixSize][matrixSize] PROGMEM= {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};

byte matrixBrightness = 4;
byte matrixBrightnessMemoryLocation = 1;
byte minMatrixBrightness = 1;
byte maxMatrixBrightness = 15;
byte matrixBrightnessStep = 3;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);  //DIN, CLK, LOAD, No. DRIVER


//direction matrix
int directionMatrix[4][2] = {
  //line column
  { -1, 0 },  //UP
  { 1, 0 },   //DOWN
  { 0, -1 },  //LEFT
  { 0, 1 }    //RIGHT
};


byte wallsCoverage = 1;
volatile bool cleanMatrix = false;



const byte arrowSize = 4;
byte Arrow[arrowSize][2] = {
  { 3, 6 },
  { 4, 6 },
  { 4, 7 },
  { 5, 6 }
};


byte DownArrow[arrowSize][2] = {
  { 6, 3 },
  { 6, 4 },
  { 6, 5 },
  { 7, 4 }
};
unsigned long lastArrowBlink = 0;
volatile bool arrowState = LOW;

