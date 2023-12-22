//buzzer
const byte buzzerPin = 8;
unsigned int buzzerTone = 1000;
unsigned int buzzerDuration = 500;

byte soundMemoryLocation = 40;
volatile bool soundValue = HIGH; 
byte melodyIndex = 0; //at what note we are at the moment 
byte songEnded = false;


struct Sound {
  unsigned int duration;
  float pitch;
  unsigned long lastCount;
};

 
Sound StartMelody[] = {
  {200,  1046.50, 0},
  {200, 1174.66, 0},
  {200, 1244.51, 0},
  {200, 1318.51, 0}
};


Sound EndMelody[] = {
  {400, 293.66, 0},
  {400, 277.18, 0},
  {400, 261.63, 0},
  {400, 246.94, 0}
};

unsigned int menuInteractionTone = 700;
unsigned int menuInteractionDuration = 300;

 