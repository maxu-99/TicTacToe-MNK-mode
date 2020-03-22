void freeBoard(Board** table, int rows);
void play(Board** table,Settings* inSettings,LinkedList* log);
Board** createBoard(Settings* inSettings);
void changeSettings(Settings* inSettings);

int makeMove(Board** table,char* player,Settings* inSettings,int* x,int* y);

int checkDraw(int counter, Settings* inSettings, int winner); 
