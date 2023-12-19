struct Portal {
    int line;  //a whole line/column should be a portal 
    int column;
    volatile bool isOpen;
    byte transitionMove; //UP, DOWN etc.
    byte fromIndex;
    byte toIndex;
    byte (*fromMatrix)[matrixSize];
    byte (*toMatrix)[matrixSize];
};


const byte MAX_PORTALS = 2;
volatile bool opened = false;

const byte noOfRooms = 4;

struct Room{
  byte portalsNumber;
  Portal portals[MAX_PORTALS];
};


byte currentRoom = 0;

Room rooms[noOfRooms] = {
  // Room 1
  {
    .portalsNumber = 2,
    .portals = {
      // Portal 1
      {
        .line = matrixSize - 1,
        .column = -1,
        .isOpen = false,
        .transitionMove = DOWN,
        .fromIndex = 0,
        .toIndex = 2,
        .fromMatrix = matrix1,
        .toMatrix = matrix3
      },
      // Portal 2
      {
        .line = -1,
        .column = matrixSize - 1,
        .isOpen = false,
        .transitionMove = RIGHT,
        .fromIndex = 0,
        .toIndex = 1,
        .fromMatrix = matrix1,
        .toMatrix = matrix2
      }
    }
  },

  // Room 2
  {
    .portalsNumber = 2,
    .portals = {
      // Portal 1
      {
        .line = -1,
        .column = 0,
        .isOpen = true,
        .transitionMove = LEFT,
        .fromIndex = 1,
        .toIndex = 0,
        .fromMatrix = matrix2,
        .toMatrix = matrix1
      },
      // Portal 2
      {
        .line = matrixSize - 1,
        .column = -1,
        .isOpen = false,
        .transitionMove = DOWN,
        .fromIndex = 1,
        .toIndex = 3,
        .fromMatrix = matrix2,
        .toMatrix = matrix4
      }
    }
  },

  // Room 3
  {
    .portalsNumber = 2,
    .portals = {
      // Portal 1
      {
        .line = 0,
        .column = -1,
        .isOpen = true,
        .transitionMove = UP,
        .fromIndex = 2,
        .toIndex = 0,
        .fromMatrix = matrix3,
        .toMatrix = matrix1
      },
      // Portal 2
      {
        .line = -1,
        .column = matrixSize - 1,
        .isOpen = true,
        .transitionMove = RIGHT,
        .fromIndex = 2,
        .toIndex = 3,
        .fromMatrix = matrix3,
        .toMatrix = matrix4
      },
    }
  },

  // Room 4
  {
    .portalsNumber = 2,
    .portals = {
      // Portal 1
      {
        .line = -1,
        .column = 0,
        .isOpen = true,
        .transitionMove = LEFT,   
        .fromIndex = 3,
        .toIndex = 2,
        .fromMatrix = matrix4,
        .toMatrix = matrix3
      },
      // Portal 2
      {
        .line = 0,
        .column = -1,
        .isOpen = true,
        .transitionMove = UP,
        .fromIndex = 3,
        .toIndex = 1,
        .fromMatrix = matrix4,
        .toMatrix = matrix2
      }
    }
  }
};


struct Level {
  byte walls;
  byte initialNoOfEnemies;
  byte timeLimit;
};

const byte noOfLevels = 3;

Level levels[noOfLevels] = {
  // Level 1
  {
    .walls = 15,
    .initialNoOfEnemies = 0,
    .timeLimit = 80,
  },

  // Level 2
  {
    .walls = 23,
    .initialNoOfEnemies = 1,
    .timeLimit = 90,
  },

  // Level 3
  {   
    .walls = 28,
    .initialNoOfEnemies = 3,
    .timeLimit = 150,
  }
};
