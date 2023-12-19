//player variables
unsigned int playerBlinkTime = 400;
unsigned long lastPlayerBlink = 0;
volatile bool playerState = LOW;
byte noOfLives = 3;
byte lives = noOfLives;
volatile bool isAlive = true;
unsigned int score = 0;
unsigned int precedentLevelScore = 0;
volatile bool resetGame = true;
byte time;
volatile bool stopTimeCount = false;
byte level = 1;
byte place = 0;
byte startLine = 0;
byte startColumn = 0;
unsigned long lastTimeCount = 0;
unsigned int timeDelay = 1000;
volatile bool highscoreDisplayed = false;
volatile bool podiumDisplayed = false;
unsigned int messageDisplayTime = 2000;
unsigned long lastMessageDisplay = 0;
volatile bool anotherMessage = false;

volatile bool inGame = false;

const byte maxNameCharacters = 5;
byte maxPodiumPlayers = 3;

//player position
byte playerLine = 0;
byte playerColumn = 0;
char name[maxNameCharacters] = "USER";
int nameIndex = -1;

bool isTheEnd = false;