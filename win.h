int checkWin(Board** table, Settings* inSettings, char* player);

int checkPlayer(char* player);

int checkHorizontal(Board** table,Settings* inSettings,char* player);

int checkVertical(Board** table,Settings* inSettings,char* player);

int checkDiagonal(Board** table,Settings* inSettings,char* player);

int checkAntiDiagonal(Board** table,Settings* inSettings,char* player);
