int enemyIntensity = 5;
int moveInterval = 1000;  //each moveInterval ms the eney will change its direction
byte enemyPoints = 10;

byte realNoOfEnemies;
byte enemyMarker = 4;

class Enemy {
public:

  byte line;
  byte column;
  unsigned long lastMove = 0;

public:
  Enemy(){}

  Enemy(byte line, byte column){
    this->line = line;
    this->column = column;

  }

  void moveEnemy();
  void checkPlayerMeeting();
  void checkEnemyDamage(byte minLine, byte maxLine, byte minColumn, byte maxColumn, byte bombLine, byte bombColumn);

};

const int MAX_ENEMIES = 3;  //  maximum number of enemies
int enemiesIndex = -1;
Enemy enemies[MAX_ENEMIES];

