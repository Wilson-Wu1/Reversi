#include <iostream>
#include <string>
#include <list>
using namespace std;

class Board {
	public:
		int tiles1[8][8] = { { 2,0,0,0,0,0,0,0 },
							{ 2,0,0,0,0,0,0,0 },
							{ 2,0,1,0,0,1,0,0 },
							{ 2,0,1,2,2,0,0,0 },
							{ 2,0,0,2,2,1,0,0 },
							{ 2,0,0,0,0,0,0,0 },
							{ 2,0,0,0,0,0,0,0 },
							{ 0, 0, 0, 0, 0, 0, 0, 0 } };
		string finalMoves[9];
		int tiles[8][8] = { { 2,1,1,1,1,1,1,1 },
							{ 2,1,1,1,1,2,1,1 },
							{ 1,1,1,1,2,1,1,1 },
							{ 2,1,1,2,2,1,1,1 },
							{ 1,1,0,2,2,2,2,2 },
							{ 2,2,1,1,1,1,1,1 },
							{ 1,1,1,1,1,1,1,1 },
							{ 1,1,1,1,1,1,1,1 } };

		void displayBoard() {
			cout << '\n';
			cout << "  A B C D E F G H";
			cout << '\n';
			int counter = 0;
			for (int i = 0; i < 8; i++) {
				if (i != 0) {
					cout << "\n";
					cout << "  ----------------";
					cout << "\n";
				}
				cout << counter<<" ";
				counter++;
				for (int j = 0; j < 8; j++) {
					if (tiles[i][j] == 0) {
						cout << " |";
					}
					else if(tiles[i][j] == 1) {
						cout << "O|";
					}
					else if (tiles[i][j] == 2) {
						cout << "X|";
					}
					
						
				}
			}
			cout << "\n";


		}

		bool playPlayerTile(int number, int second) {
						
			if (tiles[number][second] != 0) {
				cout << "ERROR: Tile already taken!"<<'\n';
				return false;
			}
			else {
				tiles[number][second] = 1;
				return true;
			}
			
		}

		bool playRobotTile(int number, int second) {
			
			if (tiles[number][second] != 0) {
				cout << "ERROR: Tile already taken!" << '\n';
				return false;
			}
			else {
				tiles[number][second] = 2;
				return true;
			}

		}

		void undoTile(int number, int second) {

			tiles[number][second] = 0;
		}

		bool winCondition(bool player) {
			bool gameOver=true;
			bool tilesLeft;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (tiles[i][j] == 0) {
						validMove(i,j);
						playPlayerTile(i,j);
						tilesLeft = validPlayerMoves(i, j, player, false);
						undoTile(i, j);
						if (tilesLeft == 1) {
							gameOver = false;
						}
					}
				}
			}
			return gameOver;
		}

		//void MCTS() {
		//	int randomMove;
		//	bool validMove = false;
		//	for (int i = 0; i < 64; i++) {
		//		if (tiles[i] == 0) {
		//			while (validMove != true) {
		//				randomMove = rand() % 64;
		//				if (tiles[randomMove] != 0) {
		//					validMove = true;
		//					tiles[randomMove] = 2;
		//				}
		//			}
		//
		//			
//
//				}
//			}
//		}
		void changeTiles(int number, int second, string direction, int tileCounter, bool player) {
			int i;
			if (player == true) {
				i = 1;
			}
			else {
				i = 2;
			}
			if (direction == "left"){
				for (int x = 0; x < tileCounter; x++) {
					tiles[number][second - 1 - x] =i;
				}
			}
			else if (direction == "right"){
				for (int x = 0; x < tileCounter; x++) {
					tiles[number][second + 1 + x] = i;
				}

			}
			else if (direction == "up") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number - 1 - x][second] = i;
				}

			}
			else if (direction == "down") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number + 1 + x][second] = i;
				}

			}
			else if (direction == "upleft") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number - 1 - x][second - 1 - x] = i;
				}
			}
			else if (direction == "upright") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number - 1 - x][second + 1 + x] = i;
				}

			}
			else if (direction == "downleft") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number + 1 + x][second - 1 - x] = i;
				}

			}
			else if (direction == "downright") {
				for (int x = 0; x < tileCounter; x++) {
					tiles[number + 1 + x][second + 1 + x] = i;
				}
			}
		}
		
		void validMove(int number, int second) {
			
			string moves[] = { "up","down","left","right","upleft","upright","downleft","downright" };
			if (second == 0) {
				if (number == 0) {

					finalMoves[0] = moves[1];
					finalMoves[1] = moves[3];
					finalMoves[2] = moves[7];

				}
				else if (number == 7) {
					finalMoves[0] = moves[0];
					finalMoves[1] = moves[3];
					finalMoves[2] = moves[5];
				}
				else {
					finalMoves[0] = moves[0];
					finalMoves[1] = moves[1];
					finalMoves[2] = moves[3];
					finalMoves[3] = moves[5];
					finalMoves[4] = moves[7];
				}

			}
			else if (second == 7) {
				if (number == 0) {

					finalMoves[0] = moves[1];
					finalMoves[1] = moves[2];
					finalMoves[2] = moves[6];
				}
				else if (number == 7) {

					finalMoves[0] = moves[0];
					finalMoves[1] = moves[2];
					finalMoves[2] = moves[4];
				}
				else {
					finalMoves[0] = moves[0];
					finalMoves[1] = moves[1];
					finalMoves[2] = moves[2];
					finalMoves[3] = moves[4];
					finalMoves[4] = moves[6];
				}

			}
			else if (number == 0) {
				finalMoves[0] = moves[1];
				finalMoves[1] = moves[2];
				finalMoves[2] = moves[3];
				finalMoves[3] = moves[6];
				finalMoves[4] = moves[7];


			}
			else if (number == 7) {
				finalMoves[0] = moves[0];
				finalMoves[1] = moves[2];
				finalMoves[2] = moves[3];
				finalMoves[3] = moves[4];
				finalMoves[4] = moves[5];
			}
			else {
				finalMoves[0] = moves[0];
				finalMoves[1] = moves[1];
				finalMoves[2] = moves[2];
				finalMoves[3] = moves[3];
				finalMoves[4] = moves[4];
				finalMoves[5] = moves[5];
				finalMoves[6] = moves[6];
				finalMoves[7] = moves[7];

			}
		}
		
		bool validPlayerMoves(int number, int second, bool player, bool change){
			
			bool minValidMove = false;
			int tileCounter;
			int i;
			int j;
			int p;
			if (player == true) {
				p = 1;
			}
			else {
				p = 2;
			}
			//TODO: Change i to k for while loops. So you can init the k only once.
			for (int k = 0; k < 8; k++) {
				
				if (finalMoves[k] != "") {
					bool tileExist = true;
					
					//LEFT OF TILE
					if (finalMoves[k] == "left" && tiles[number][second - 1] != 0 && tiles[number][second - 1] != p) {
						tileCounter = 0;
						i = second - 1;
						
						while(i>=0) {
							if (tiles[number][second] == tiles[number][i]) {								
								break;
							}
							//Tile has nothing on it
							if (tiles[number][i] == 0) {
								tileExist = false;
								break;
							}
							i--;
							tileCounter++;

							
						}
						cout << "I: " << i;
						
						if ( (i != -1 || tiles[number][i+1] == p) && tileCounter!=0 && tileExist != false) {
							minValidMove = true;
							if (change == true) {
								changeTiles(number, second, "left", tileCounter, player);
							}
							
						}

						cout <<"LEFT"<< tileCounter << '\n';
					}
					//RIGHT OF TILE
					else if (finalMoves[k] == "right" && tiles[number][second+1] !=0 && tiles[number][second + 1] != p) {
						tileCounter = 0;
						i = second +1;
						while (i <= 7) {
							if (tiles[number][second] == tiles[number][i]) {
								break;
							}
							//Tile has nothing on it
							if (tiles[number][i] == 0) {
								tileExist = false;
								break;
							}
							i++;
							tileCounter++;


						}
						if ((i != 8 || tiles[number][i - 1] == p) &&tileCounter!=0 && tileExist != false) {
							minValidMove = true;
							if (change == true) {
								changeTiles(number, second, "right", tileCounter, player);
							}
						}

						cout <<"RIGHT"<< tileCounter << '\n';

					}
					//UP OF TILE
					else if (finalMoves[k] == "up" && tiles[number-1][second] != 0 && tiles[number - 1][second] != p) {
						tileCounter = 0;
						i = number - 1;
						
						while (i >= 0) {
							cout << tiles[number][second] << " " << tiles[i][second];
							if (tiles[number][second] == tiles[i][second]) {

								break;
							}
							//Tile has nothing on it
							if (tiles[i][second] == 0) {
								tileExist = false;
								break;
							}
							i--;
							tileCounter++;


						}
						
						if ((i != -1 || tiles[i+1][second] == p) &&tileCounter != 0 && tileExist != false ) {
							minValidMove = true;
							if (change == true) {
								changeTiles(number, second, "up", tileCounter, player);
							}
						}
						cout <<"UP"<< tileCounter << '\n';

					}
					//DOWN OF TILE
					else if (finalMoves[k] == "up" && tiles[number + 1][second] != 0 && tiles[number + 1][second] != p) {
						tileCounter = 0;
						i = number + 1;
						while (i <= 7) {

							if (tiles[number][second] == tiles[i][second]) {
								break;
							}
							//Tile has nothing on it
							if (tiles[i][second] == 0) {
								tileExist = false;
								break;
							}
							i++;
							tileCounter++;


						}
						
						if ((i != 8|| tiles[i - 1][second] == p) && tileCounter != 0 && tileExist != false) {
							minValidMove = true;
							if (change == true) {
								changeTiles(number, second, "down", tileCounter, player);
							}
						}
						cout <<"DOWN"<< tileCounter << '\n';

					}
					//UPLEFT of Tile
					else if (finalMoves[k] == "upleft" && tiles[number - 1][second - 1] != 0 && tiles[number - 1][second - 1] != p) {
						tileCounter = 0;
						i = number - 1;
						j = second - 1;
						while (i >= 0 || j >=0 ) {
							// Clean break
							if (tiles[number][second] == tiles[i][j]){
								break;
							}
							//Tile has nothing on it
							if (tiles[i][j] == 0) {
								tileExist = false;
								break;
							}
							i--;
							j--;
							tileCounter++;
						}

						if ((i != -1 || tiles[i + 1][second] == p)&& (j != -1 ||tiles[number][j+1] == p) && tileCounter != 0 && tileExist != false) {
							minValidMove = true;
							if (change == true) {
								changeTiles(number, second, "upleft", tileCounter, player);
							}
						}

						cout << "UPLEFT" << tileCounter << '\n';
						
					}
					//UPRIGHT of tile
					else if (finalMoves[k] == "upright" && tiles[number - 1][second +1 ] != 0 && tiles[number - 1][second + 1] != p) {
					tileCounter = 0;
					i = number - 1;
					j = second + 1;
					while (i >= 0||j<=7) {
						cout << tiles[number][second]<<" " << tiles[i][j] << '\n';
						if (tiles[number][second] == tiles[i][j] ) {
							break;
						}
						//Tile has nothing on it
						if (tiles[i][j] == 0) {
							tileExist = false;
							break;
						}
						i--;
						j++;
						tileCounter++;
					}

					if ((i != -1 || tiles[i + 1][second] == p) && (j != 8 || tiles[number][j - 1] == p) && tileCounter != 0 && tileExist != false) {
						minValidMove = true;
						if (change == true) {
							changeTiles(number, second, "upright", tileCounter, player);
						}
					}
					cout << "UPRIGHT" << tileCounter << '\n';

					}
					//DOWNLEFT of tile
					else if (finalMoves[k] == "downleft" && tiles[number + 1][second - 1] != 0 && tiles[number + 1][second - 1] != p) {
					tileCounter = 0;
					i = number + 1;
					j = second - 1;
					while (i <= 7 || j >=0) {
						if (tiles[number][second] == tiles[i][j]) {
							break;
						}
						//Tile has nothing on it
						if (tiles[i][j] == 0) {
							tileExist = false;
							break;
						}
						i++;
						j--;
						tileCounter++;
					}

					if ((i != 8 || tiles[i - 1][second] == p) && (j != -1 || tiles[number][j + 1] == p)&& tileCounter != 0 && tileExist != false) {
						minValidMove = true;
						if (change == true) {
							changeTiles(number, second, "downleft", tileCounter, player);
						}
					}
					cout << "DOWNLEFT" << tileCounter<<'\n';

					}
					//DOWNRIGHT of tile
					else if (finalMoves[k] == "downright" && tiles[number + 1][second + 1] != 0 && tiles[number + 1][second + 1] != p) {
					tileCounter = 0;
					i = number + 1;
					j = second + 1;
					while (i <= 7 || j <= 7) {
						if (tiles[number][second] == tiles[i][j]) {
							break;
						}
						//Tile has nothing on it
						if (tiles[i][j] == 0) {
							tileExist = false;
							break;
						}
						i++;
						j++;
						tileCounter++;
					}

					if ((i != 8 || tiles[i - 1][second] == p) && (j != 8 || tiles[number][j - 1] == p) && tileCounter != 0 && tileExist != false) {
						minValidMove = true;
						if (change == true) {
							changeTiles(number, second, "downright", tileCounter, player);
						}
					}
					cout << "DOWNRIGHT" << tileCounter << '\n';

					}
				}

			}
			//cout << minValidMove;

			
			return minValidMove;
		}
		








};//end of class









int main()
{
	cout << "Hello World!\n";
	Board board;
	board.displayBoard();

	bool gameOver = false;
	int choice = 0;
	bool validTile = false;
	bool noMorePlayerTiles = false;
	//cout << "Who goes first? 0 or 1" << '\n'; 
	//cin >> choice;
	while (gameOver != true) {
		noMorePlayerTiles = false;

		if (choice == 0) {

			if (board.winCondition(true) == 1) {
				noMorePlayerTiles = true;
				gameOver = true;
			}
			else {
				bool validInput = false;
				bool spaceNotTaken = false;
				string playerInput;
				while (validInput != true) {

					cout << '\n' << "Enter Player Move:" << '\n';
					cin >> playerInput;
					int number = (int)playerInput[0] - 48;
					int second;
					if (number >= 0 && number <= 7) {
						if (playerInput[1] == 'a' || playerInput[1] == 'b' || playerInput[1] == 'c' || playerInput[1] == 'd' || playerInput[1] == 'e' || playerInput[1] == 'f' || playerInput[1] == 'g' || playerInput[1] == 'h') {
							second = (int)playerInput[1] - 96 - 1;

							spaceNotTaken = board.playPlayerTile(number, second);

							if (spaceNotTaken == true) {

								board.validMove(number, second);
								validTile = board.validPlayerMoves(number, second, true, true);
								if (validTile == false) {
									board.undoTile(number, second);
									cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {
									board.displayBoard();
									validInput = true;
								}

							}

						}
						else {
							cout << "ERROR: Invalid Column (Between 'a' and 'h')" << '\n';
						}

					}
					else {
						cout << "ERROR: Invalid Row (Between 1 and 7)" << '\n';
					}






				}
			}
		}



	}



	return 0;
};




