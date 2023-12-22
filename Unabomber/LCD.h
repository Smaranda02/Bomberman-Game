const byte rs = 9;
const byte en = 7;
const byte d4 = 6;
const byte d5 = 3;
const byte d6 = 4;
const byte d7 = 13;

const byte backLightPin = 5;
byte lcdBrightnessStep = 20;
byte backLightValue = 50;
byte minLcdBrightness = 0;
byte maxLcdBrightness = 100;
byte minMappedValue = 0;
byte maxMappedValue = 255;
byte lcdBrightnessMemoryLocation = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


bool shown = false;
unsigned int letterBlinkTime = 400;
unsigned long lastLetterBlink = 0;
volatile bool letterState = LOW;

// char greetingMessage = "   WELCOME TO          UNABOMBER";
unsigned int greetingDisplayTime = 1500;

char alphabet1[] = "ABCDEFGHIJKLMNOP";
char alphabet2[] = "QRSTUVWXYZ < Y/N";
char currentLetterValue;  //A
byte currentLetter = 0;   // letter index

const char PROGMEM gameOverMessage[] = "Game over...";

volatile bool firstEndMessage = true;



byte heart[8] = {
  0b11011,
  0b11011,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100
};


byte enemy[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10001,
  B10001,
  B10001
};

byte door[8] = {
 B11111,
  B10001,
  B10001,
  B10001,
  B10011,
  B10001,
  B10001,
  B11111
};

byte tick[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000
};