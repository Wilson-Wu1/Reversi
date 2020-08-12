#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <vector>
using namespace std;
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */

class Board {
public:	
	/*
	int tiles2[8][8] = { { 2,0,0,0,0,0,0,0 },
						{ 2,2,0,0,0,0,0,0 },
						{ 2,2,1,0,0,1,0,0 },
						{ 2,2,1,2,2,0,0,0 },
						{ 2,2,0,2,2,1,0,0 },
						{ 2,2,0,0,0,0,0,0 },
						{ 2,2,0,0,0,0,0,0 },
						{ 0, 1, 0, 0, 0, 0, 0, 0 } };

	int tiles1[8][8] = { { 1,1,1,2,1,1,2,1 },
						{ 2,1,1,2,1,2,1,1 },
						{ 1,1,1,2,2,1,1,1 },
						{ 2,1,1,2,2,1,1,2 },
						{ 2,1,2,2,2,2,2,2 },
						{ 2,2,1,2,1,2,1,1 },
						{ 1,1,2,2,2,1,1,1 },
						{ 2,2,2,0,2,2,2,2 } };
	int reset2[8][8] = { { 1,1,1,2,1,1,2,1 },
						{ 2,1,1,2,1,2,1,1 },
						{ 1,1,1,2,2,1,1,1 },
						{ 2,1,1,2,2,1,1,2 },
						{ 2,1,2,2,2,2,2,2 },
						{ 2,2,1,2,1,2,1,1 },
						{ 1,1,2,2,2,1,1,1 },
						{ 2,2,2,0,2,2,2,2 } };

	*/

	int tiles[8][8] = { { 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,1,2,0,0,0 },
					{ 0,0,0,2,1,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 } };
	
	int reset[8][8] = { { 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,1,2,0,0,0 },
				{ 0,0,0,2,1,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 } };
	
	int wins[8][8] = { { 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 } };

	
	int bestAIWins[8][8] = { { 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 } };
	
	int reset1[8][8] = { { 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,1,2,0,0,0 },
			{ 0,0,0,2,1,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0 } };

	std::chrono::steady_clock::time_point start1;
	std::chrono::steady_clock::time_point end1;
	std::chrono::steady_clock::time_point clock;
	std::vector<int> avaliableTiles{};
	std::vector<int> finalMoves{};
	std::vector<int> playerTiles{};
	std::vector<int> robotTiles{};
	std::vector<int> init{};
	std::vector<int> init2{};

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
			cout << counter << " ";
			counter++;
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 0) {
					cout << " |";
				}
				else if (tiles[i][j] == 1) {
					cout <<RED<< "O"<<RESET<<"|";
				}
				else if (tiles[i][j] == 2) {
					cout <<BLUE<< "X" << RESET << "|";
				}


			}
		}
		cout << "\n";


	}

	bool playPlayerTile(int number, int second) {

		if (tiles[number][second] != 0) {
			//cout << '\n' << "ERROR(PLAYER): Tile already taken! at " << number << ":" << second << '\n';
			//cout << tiles[number][second];

			return false;
		}
		else {
			tiles[number][second] = 1;
			return true;
		}

	}

	bool playRobotTile(int number, int second) {

		if (tiles[number][second] != 0) {
			//cout <<'\n' << "ERROR(ROBOT): Tile already taken! at " <<number<<":"<<second<<'\n';
			//cout << tiles[number][second];
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

	void playablePlayerTiles() {
		playerTiles.clear();
		
		
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 0) {
					if (tiles[i - 1][j] == 2 || tiles[i + 1][j] == 2 || tiles[i][j - 1] == 2 || tiles[i][j + 1] == 2 || tiles[i + 1][j + 1] == 2 || tiles[i + 1][j - 1] == 2 || tiles[i - 1][j + 1] == 2 || tiles[i - 1][j - 1] == 2) {
												
						playerTiles.push_back((8 * i) + j);
						//cout <<f (8 * i) + j << " " << i << ":" << j<< " " << '\n';
							
					}
				}

			}
		}
		

		
	}	
	
	void playableRobotTiles() {
		robotTiles.clear();
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 0) {
					if (tiles[i - 1][j] == 1 || tiles[i + 1][j] == 1 || tiles[i][j - 1] == 1 || tiles[i][j + 1] == 1 || tiles[i + 1][j + 1] == 1 || tiles[i + 1][j - 1] == 1 || tiles[i - 1][j + 1] == 1 || tiles[i - 1][j - 1] == 1) {
						robotTiles.push_back((8 * i) + j);
					}
				}

			}
		}
		

		
	}

	void playableInitialTiles() {
		init.clear();
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 0) {
					if (tiles[i - 1][j] == 1 || tiles[i + 1][j] == 1 || tiles[i][j - 1] == 1 || tiles[i][j + 1] == 1 || tiles[i + 1][j + 1] == 1 || tiles[i + 1][j - 1] == 1 || tiles[i - 1][j + 1] == 1 || tiles[i - 1][j - 1] == 1) {
						init.push_back((8 * i) + j);
						
					}
				}

			}
		}



	}
	
	void playableInitialTiles2() {
		init2.clear();
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 0) {
					if (tiles[i - 1][j] == 2 || tiles[i + 1][j] == 2 || tiles[i][j - 1] == 2 || tiles[i][j + 1] == 2 || tiles[i + 1][j + 1] == 2 || tiles[i + 1][j - 1] == 2 || tiles[i - 1][j + 1] == 2 || tiles[i - 1][j - 1] == 2) {

						init2.push_back((8 * i) + j);
						//cout << (8 * i) + j << " " << i << ":" << j<< " " << '\n';

					}
				}

			}
		}

	}

	bool winCondition1() {

		
		int first;
		int second;
		playablePlayerTiles();

		for (int i = 0; i < playerTiles.size(); i++) {
			first = floor(playerTiles[i] / 8);
			second = playerTiles[i] % 8;
			
			//validMove(first, second);
			winCon++;
			playPlayerTile(first, second);
			if (validPlayerMoves(first, second, true,false) == true) {
				tiles[first][second] = 0;
				
				return true;
			}
			tiles[first][second] = 0;
		}
		
		return false;
		
	}
	
	bool winCondition2() {

		int first;
		int second;
		playableRobotTiles();
		for (int i = 0; i < robotTiles.size(); i++) {
			first = floor(robotTiles[i] / 8);
			second = robotTiles[i] % 8;
			//validMove(first, second);
			winCon++;
			playRobotTile(first, second);
			if (validPlayerMoves(first, second, false,false) == true) {
				tiles[first][second] = 0;
			
				return true;
			}
			
			tiles[first][second] = 0;

		}
		
		return false;
		

	}

	int calculateWinner() {
		int player = 0;
		int robot = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 1) {
					player++;
				}
				else if (tiles[i][j] == 2) {
					robot++;
				}
			}
		}
		if (robot > player) {
			return robot;
		}
		else {
			return player;
		}
	}

	int winner() {
		int winner;
		int robot = 0;
		int player = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 1) {
					player++;
				}
				else if (tiles[i][j] == 2) {
					robot++;
				}
			}
		}
		if (robot > player) {
			return winner = 2;
		}
		else {
			return winner = 1;
		}
	}
	
	
	
	int winCon;
	int whileCounter = 0;
	int thisCounter = 0;

	bool MCTS(int playouts) {
		bool gameOverPlayer;
		bool gameOverRobot;
		int randomNumber1;
		int randomNumber2;
		bool spaceNotTaken;
		bool validInput;
		bool validTile;
		bool validInitial;
		bool finalTilePlayed = false;
		int value;
		int index;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				reset[i][j] = tiles[i][j];
			}
		}
		int first;
		int second;
		//For Every Tile

		playableInitialTiles();
		for (int x = 0; x <init.size(); x++) {

			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					tiles[i][j] = reset[i][j];
				}
			}

			first = floor(init[x] / 8);
			second = init[x] % 8;

			playRobotTile(first, second);

			//validMove(first, second);
			if (validPlayerMoves(first, second, false, true) == true) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						reset1[i][j] = tiles[i][j];
					}
				}
				// Play the initial tile
				finalTilePlayed = true; 
				
				//cout << "START OF PLAYOUTS**************************************" << '\n;';
				for (int k = 0; k < playouts; k++) {
					
					
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							tiles[i][j] = reset1[i][j];
						}
					}
					
					//cout << "INITIAL TILE BEING PLAYED";
					//displayBoard();
					gameOverPlayer = false;
					gameOverRobot = false;

					
					while (gameOverPlayer == false || gameOverRobot == false) {
						whileCounter++;

						//Player Goes
						//cout << "Player MOVE" << '\n';
						gameOverPlayer = false;
						if (winCondition1() == false) {
							gameOverPlayer = true;
							if (gameOverRobot == true) {
								break;
							}
							//cout << "Player CANT PLAY A TILE"<<'\n';
						}
						else {
							//cout << "NUM OF PLAYER TILES: " << playerTiles.size() << '\n';
							validInput = false;

							while (validInput == false) {

								//Create Random Numbers
								//calculatePlayablePlayerTiles();
								index = rand() % playerTiles.size(); // pick a random index
								value = playerTiles[index]; // a random value taken from that list
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								//randomNumber1 = rand() % 8;
								//randomNumber2 = rand() % 8;
								
								playPlayerTile(randomNumber1, randomNumber2);
								thisCounter++;
								//validMove(randomNumber1, randomNumber2);


								if (validPlayerMoves(randomNumber1, randomNumber2, true, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {									
									//displayBoard();
									validInput = true;
								}															
							}
						}

						//Robot Goes
						//cout << "ROBOT MOVE" << '\n';
						gameOverRobot = false;
						if (winCondition2() == false) {
							gameOverRobot = true;

							//cout << "ROBOT CANT PLAY A TILE";
						}
						else {
							//cout << "NUM OF ROBOT TILES: " << robotTiles.size()<<'\n';
							validInput = false;
							while (validInput == false) {
								//Create Random Numbers
								//calculatePlayableRobotTiles();
								index = rand() % robotTiles.size(); // pick a random index
								value = robotTiles[index]; // a random value taken from that list
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								//randomNumber1 = rand() % 8;
								//randomNumber2 = rand() % 8;
															
								playRobotTile(randomNumber1, randomNumber2);
								//validMove(randomNumber1, randomNumber2);
								thisCounter++;
								if (validPlayerMoves(randomNumber1, randomNumber2, false,true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {									
									//displayBoard();
									validInput = true;
								}																
							}
						}

					}

					//cout << "PLAYOUT ENDED"<<'\n';
					//cout << '\n';
					//cout << calculateWinner() << " " << winner()<<i<<":"<<j<<'\n';

					//displayBoard();

					if (winner() == 2) {
						wins[first][second] += 5;

					}
					else if (winner() == 1)
					{
						wins[first][second] -= 3;
					}
					
				}
				
			}
			else {
				undoTile(first, second);
			}

		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tiles[i][j] = reset[i][j];
				//cout << wins[i][j]<<" ";
			}
		}
		if (finalTilePlayed == true) {
			int max = -99999;
			int row;
			int col;
			for (int i = 0; i < 8; i++) {
				cout << '\n';
				for (int j = 0; j < 8; j++) {
					cout << wins[i][j] << " ";
					
					if (wins[i][j] > max) {
						//validMove(i, j);
						if (playRobotTile(i, j) == true) {
							if ((validPlayerMoves(i, j, false, false) == true)) {
								max = wins[i][j];
								row = i;
								col = j;
							}
							undoTile(i, j);

						}

					}
					
					wins[i][j] = 0;

				}
			}

			tiles[row][col] = 2;
			cout << "MCTS PLAYED:" << row << " " << col << '\n';
			//validMove(row, col);
			if (validPlayerMoves(row, col, false, true) == false) {
				cout << "ERRORERRORERRORERRORERRORERRORERRORERRORERRORERROR" << '\n';
				cout << max;
			}

			cout << "MAX: " << max;
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "ENTIRE MCTS TIME= " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
		cout << "WHILE: " << whileCounter << '\n';
		cout << "VALIDPLAYERMOVES CALLS: " << thisCounter << '\n';
		cout << "WIN CON TOTAL CALLS: " << winCon << '\n';
		winCon = 0;
		whileCounter = 0;
		thisCounter = 0;



		return finalTilePlayed;
	}
	
	bool bestAI(int playouts) {
		bool gameOverPlayer;
		bool gameOverRobot;
		int randomNumber1;
		int randomNumber2;
		bool spaceNotTaken;
		bool validInput;
		bool validTile;
		bool validInitial;
		bool finalTilePlayed = false;
		int value;
		int index;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				reset[i][j] = tiles[i][j];
			}
		}
		int first;
		int second;
		//For Every Tile

		playableInitialTiles2();
		for (int x = 0; x < init2.size(); x++) {
			
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					tiles[i][j] = reset[i][j];
				}
			}

			first = floor(init2[x] / 8);
			second = init2[x] % 8;

			playPlayerTile(first, second);

			//validMove(first, second);
			if (validPlayerMoves(first, second, true, true) == true) {
				
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						reset1[i][j] = tiles[i][j];
					}
				}
				// Play the initial tile
				finalTilePlayed = true;

				//cout << "START OF PLAYOUTS**************************************" << '\n;';
				for (int k = 0; k < playouts; k++) {
					

					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							tiles[i][j] = reset1[i][j];
						}
					}

					//cout << "INITIAL TILE BEING PLAYED";
					//displayBoard();
					gameOverPlayer = false;
					gameOverRobot = false;


					while (gameOverPlayer == false || gameOverRobot == false) {
						whileCounter++;



						//Robot Goes
						//cout << "ROBOT MOVE" << '\n';
						gameOverRobot = false;
						if (winCondition2() == false) {
							gameOverRobot = true;
							if (gameOverPlayer == true) {
								break;
							}

							//cout << "ROBOT CANT PLAY A TILE";
						}
						else {
							//cout << "NUM OF ROBOT TILES: " << robotTiles.size()<<'\n';
							validInput = false;
							while (validInput == false) {
								//Create Random Numbers
								//calculatePlayableRobotTiles();
								index = rand() % robotTiles.size(); // pick a random index
								value = robotTiles[index]; // a random value taken from that list
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								//randomNumber1 = rand() % 8;
								//randomNumber2 = rand() % 8;

								playRobotTile(randomNumber1, randomNumber2);
								//validMove(randomNumber1, randomNumber2);
								thisCounter++;
								if (validPlayerMoves(randomNumber1, randomNumber2, false, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {
									//displayBoard();
									validInput = true;
								}
							}
						}
						//Player Goes
						//cout << "Player MOVE" << '\n';
						gameOverPlayer = false;
						if (winCondition1() == false) {
							gameOverPlayer = true;
							if (gameOverRobot == true) {
								break;
							}
							//cout << "Player CANT PLAY A TILE"<<'\n';
						}
						else {
							//cout << "NUM OF PLAYER TILES: " << playerTiles.size() << '\n';
							validInput = false;

							while (validInput == false) {

								//Create Random Numbers
								//calculatePlayablePlayerTiles();
								index = rand() % playerTiles.size(); // pick a random index
								value = playerTiles[index]; // a random value taken from that list
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								//randomNumber1 = rand() % 8;
								//randomNumber2 = rand() % 8;

								playPlayerTile(randomNumber1, randomNumber2);
								thisCounter++;
								//validMove(randomNumber1, randomNumber2);


								if (validPlayerMoves(randomNumber1, randomNumber2, true, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {
									//displayBoard();
									validInput = true;
								}
							}
						}

					}

					//cout << "PLAYOUT ENDED"<<'\n';
					//cout << '\n';
					//cout << calculateWinner() << " " << winner()<<i<<":"<<j<<'\n';

					//displayBoard();

					if (winner() == 1) {
						bestAIWins[first][second] += 5;

					}
					else if (winner() == 2)
					{
						bestAIWins[first][second] -= 3;
					}

				}

			}
			else {
				undoTile(first, second);
			}

		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tiles[i][j] = reset[i][j];
				//cout << wins[i][j]<<" ";
			}
		}
		if (finalTilePlayed == true) {
			int max = -99999;
			int row;
			int col;
			for (int i = 0; i < 8; i++) {
				cout << '\n';
				for (int j = 0; j < 8; j++) {
					cout << bestAIWins[i][j] << " ";

					if (bestAIWins[i][j] > max) {
						//validMove(i, j);
						if (playPlayerTile(i, j) == true) {
							if ((validPlayerMoves(i, j, true, false) == true)) {
								max = bestAIWins[i][j];
								row = i;
								col = j;
							}
							undoTile(i, j);

						}

					}

					bestAIWins[i][j] = 0;

				}
			}

			tiles[row][col] = 1;
			cout << "BEST AI PLAYED:" << row << " " << col << '\n';
			//validMove(row, col);
			if (validPlayerMoves(row, col, true, true) == false) {
				cout << "ERRORERRORERRORERRORERRORERRORERRORERRORERRORERROR" << '\n';
				cout << max;
			}

			cout << "MAX: " << max;
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "ENTIRE MCTS TIME= " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
		cout << "WHILE: " << whileCounter << '\n';
		cout << "VALIDPLAYERMOVES CALLS: " << thisCounter << '\n';
		cout << "WIN CON TOTAL CALLS: " << winCon << '\n';
		winCon = 0;
		whileCounter = 0;
		thisCounter = 0;



		return finalTilePlayed;
	}
	



	void changeTiles(int number, int second, int direction, int tileCounter, bool player) {
		int i;
		if (player == true) {
			i = 1;
		}
		else {
			i = 2;
		}
		if (direction == 0) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number][second - 1 - x] = i;
			}
		}
		else if (direction == 1) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number][second + 1 + x] = i;
			}

		}
		else if (direction == 2) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second] = i;
			}

		}
		else if (direction == 3) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second] = i;
			}

		}
		else if (direction == 4) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second - 1 - x] = i;
			}
		}
		else if (direction ==5) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second + 1 + x] = i;
			}

		}
		else if (direction == 6) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second - 1 - x] = i;
			}

		}
		else if (direction ==7) {
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second + 1 + x] = i;
			}
		}
	}


	bool validPlayerMoves(int number, int second, bool player, bool change) {
		bool minValidMove = false;
		int tileCounter;
		int i;
		int j;
		int p;
		int opposite;
		bool tileExist = true;
		if (player == true) {
			p = 1;
			opposite = 2;
		
			

			//LEFT OF TILE

			if (tiles[number][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = second - 1;

				while (i >= 0) {
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
				//cout << "I: " << i;

				if ((i != -1 || tiles[number][i + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 0, tileCounter, player);
					}

				}

				//cout << "LEFT" << tileCounter << '\n';
			}
			//RIGHT OF TILE
			if (tiles[number][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = second + 1;
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
				if ((i != 8 || tiles[number][i - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 1, tileCounter, player);
					}
				}

				//cout << "RIGHT" << tileCounter << '\n';

			}
			//UP OF TILE
			if (tiles[number - 1][second] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;

				while (i >= 0) {
					//cout << tiles[number][second] << " " << tiles[i][second];
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

				if ((i != -1 || tiles[i + 1][second] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second,2, tileCounter, player);
					}
				}
				//cout << "UP" << tileCounter << '\n';

			}
			//DOWN OF TILE
			if (tiles[number + 1][second] == opposite) {
				tileExist = true;
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

				if ((i != 8 || tiles[i - 1][second] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second,3, tileCounter, player);
					}
				}
				//cout << "DOWN" << tileCounter << '\n';

			}
			//UPLEFT of Tile
			if (tiles[number - 1][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;
				j = second - 1;
				while (i >= 0 && j >= 0) {
					// Clean break
					if (tiles[number][second] == tiles[i][j]) {
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

				if ((i != -1 || tiles[i + 1][j + 1] == p) && (j != -1 || tiles[i + 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 4, tileCounter, player);
					}
				}

				//cout << "UPLEFT" << tileCounter << '\n';

			}
			//UPRIGHT of tile
			if (tiles[number - 1][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;
				j = second + 1;
				while (i >= 0 && j <= 7) {
					//cout << tiles[number][second] << " " << tiles[i][j] << '\n';
					if (tiles[number][second] == tiles[i][j]) {
						break;
					}
					if (tiles[i][j] == 0) {
						tileExist = false;
						break;
					}
					//Tile has nothing on it

					i--;
					j++;
					tileCounter++;
				}


				if ((i != -1 || tiles[i + 1][j - 1] == p) && (j != 8 || tiles[i + 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 5, tileCounter, player);
					}
				}
				//cout << "UPRIGHT" << tileCounter << '\n';

			}
			//DOWNLEFT of tile
			if (tiles[number + 1][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number + 1;
				j = second - 1;
				while (i <= 7 && j >= 0) {
					if (tiles[number][second] == tiles[i][j]) {
						break;
					}
					if (tiles[i][j] == 0) {
						tileExist = false;
						break;
					}
					//Tile has nothing on it

					i++;
					j--;
					tileCounter++;
				}

				if ((i != 8 || tiles[i - 1][j + 1] == p) && (j != -1 || tiles[i - 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second,6, tileCounter, player);
					}
				}
				//cout << "DOWNLEFT" << tileCounter << '\n';

			}
			//DOWNRIGHT of tile
			if (tiles[number + 1][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number + 1;
				j = second + 1;
				while (i <= 7 && j <= 7) {
					if (tiles[number][second] == tiles[i][j]) {
						break;
					}
					if (tiles[i][j] == 0) {
						tileExist = false;
						break;
					}
					//Tile has nothing on it

					i++;
					j++;
					tileCounter++;
				}

				if ((i != 8 || tiles[i - 1][j - 1] == p) && (j != 8 || tiles[i - 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;

					if (change == true) {
						changeTiles(number, second, 7, tileCounter, player);
					}
				}
				//cout << "DOWNRIGHT" << tileCounter << '\n';

			}


		}
		
		else if (player == false) {
			p = 2;
			opposite = 1;
		
			bool tileExist = true;

			//LEFT OF TILE

			if (tiles[number][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = second - 1;

				while (i >= 0) {
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
				//cout << "I: " << i;

				if ((i != -1 || tiles[number][i + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 0, tileCounter, player);
					}

				}

				//cout << "LEFT" << tileCounter << '\n';
			}
			//RIGHT OF TILE
			if (tiles[number][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = second + 1;
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
				if ((i != 8 || tiles[number][i - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 1, tileCounter, player);
					}
				}

				//cout << "RIGHT" << tileCounter << '\n';

			}
			//UP OF TILE
			if (tiles[number - 1][second] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;

				while (i >= 0) {
					//cout << tiles[number][second] << " " << tiles[i][second];
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

				if ((i != -1 || tiles[i + 1][second] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 2, tileCounter, player);
					}
				}
				//cout << "UP" << tileCounter << '\n';

			}
			//DOWN OF TILE
			if (tiles[number + 1][second] == opposite) {
				tileExist = true;
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

				if ((i != 8 || tiles[i - 1][second] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 3, tileCounter, player);
					}
				}
				//cout << "DOWN" << tileCounter << '\n';

			}
			//UPLEFT of Tile
			if (tiles[number - 1][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;
				j = second - 1;
				while (i >= 0 && j >= 0) {
					// Clean break
					if (tiles[number][second] == tiles[i][j]) {
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

				if ((i != -1 || tiles[i + 1][j + 1] == p) && (j != -1 || tiles[i + 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 4, tileCounter, player);
					}
				}

				//cout << "UPLEFT" << tileCounter << '\n';

			}
			//UPRIGHT of tile
			if (tiles[number - 1][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number - 1;
				j = second + 1;
				while (i >= 0 && j <= 7) {
					//cout << tiles[number][second] << " " << tiles[i][j] << '\n';
					if (tiles[number][second] == tiles[i][j]) {
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


				if ((i != -1 || tiles[i + 1][j - 1] == p) && (j != 8 || tiles[i + 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second, 5, tileCounter, player);
					}
				}
				//cout << "UPRIGHT" << tileCounter << '\n';

			}
			//DOWNLEFT of tile
			if (tiles[number + 1][second - 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number + 1;
				j = second - 1;
				while (i <= 7 && j >= 0) {
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

				if ((i != 8 || tiles[i - 1][j + 1] == p) && (j != -1 || tiles[i - 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;
					if (change == true) {
						changeTiles(number, second,6, tileCounter, player);
					}
				}
				//cout << "DOWNLEFT" << tileCounter << '\n';

			}
			//DOWNRIGHT of tile
			if (tiles[number + 1][second + 1] == opposite) {
				tileExist = true;
				tileCounter = 0;
				i = number + 1;
				j = second + 1;
				while (i <= 7 && j <= 7) {
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

				if ((i != 8 || tiles[i - 1][j - 1] == p) && (j != 8 || tiles[i - 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					minValidMove = true;

					if (change == true) {
						changeTiles(number, second, 7, tileCounter, player);
					}
				}
				//cout << "DOWNRIGHT" << tileCounter << '\n';

			}


			
		}


		
		//cout << minValidMove;


		return minValidMove;
	}

	bool validMovesLeft(int number, int second, bool player) {
		bool minValidMove = false;
		int tileCounter;
		int i;
		int j;
		int p;
		if (player == true) {
			p = 1;
		}
		else if (player == false) {
			p = 2;
		}
		for (int k = 0; k < finalMoves.size(); k++) {

			
			bool tileExist = true;

			//LEFT OF TILE

			if (finalMoves[k] == 0 && tiles[number][second - 1] != 0 && tiles[number][second - 1] != p) {

				tileCounter = 0;
				i = second - 1;

				while (i >= 0) {
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
				//cout << "I: " << i;

				if ((i != -1 || tiles[number][i + 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;

				}

				//cout << "LEFT" << tileCounter << '\n';
			}
			//RIGHT OF TILE
			else if (finalMoves[k] == 1 && tiles[number][second + 1] != 0 && tiles[number][second + 1] != p) {
				tileCounter = 0;
				i = second + 1;
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
				if ((i != 8 || tiles[number][i - 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}

				//cout << "RIGHT" << tileCounter << '\n';

			}
			//UP OF TILE
			else if (finalMoves[k] == 2 && tiles[number - 1][second] != 0 && tiles[number - 1][second] != p) {
				tileCounter = 0;
				i = number - 1;

				while (i >= 0) {
					//cout << tiles[number][second] << " " << tiles[i][second];
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

				if ((i != -1 || tiles[i + 1][second] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}
				//cout << "UP" << tileCounter << '\n';

			}
			//DOWN OF TILE
			else if (finalMoves[k] == 3 && tiles[number + 1][second] != 0 && tiles[number + 1][second] != p) {

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

				if ((i != 8 || tiles[i - 1][second] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}
				//cout << "DOWN" << tileCounter << '\n';

			}
			//UPLEFT of Tile
			else if (finalMoves[k] == 4 && tiles[number - 1][second - 1] != 0 && tiles[number - 1][second - 1] != p) {
				tileCounter = 0;
				i = number - 1;
				j = second - 1;
				while (i >= 0 && j >= 0) {
					// Clean break
					if (tiles[number][second] == tiles[i][j]) {
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

				if ((i != -1 || tiles[i + 1][j + 1] == p) && (j != -1 || tiles[i + 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}

				//cout << "UPLEFT" << tileCounter << '\n';

			}
			//UPRIGHT of tile
			else if (finalMoves[k] == 5 && tiles[number - 1][second + 1] != 0 && tiles[number - 1][second + 1] != p) {
				tileCounter = 0;
				i = number - 1;
				j = second + 1;
				while (i >= 0 && j <= 7) {
					//cout << tiles[number][second] << " " << tiles[i][j] << '\n';
					if (tiles[number][second] == tiles[i][j]) {
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


				if ((i != -1 || tiles[i + 1][j - 1] == p) && (j != 8 || tiles[i + 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}
				//cout << "UPRIGHT" << tileCounter << '\n';

			}
			//DOWNLEFT of tile
			else if (finalMoves[k] == 6 && tiles[number + 1][second - 1] != 0 && tiles[number + 1][second - 1] != p) {
				tileCounter = 0;
				i = number + 1;
				j = second - 1;
				while (i <= 7 && j >= 0) {
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

				if ((i != 8 || tiles[i - 1][j + 1] == p) && (j != -1 || tiles[i - 1][j + 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}
				//cout << "DOWNLEFT" << tileCounter << '\n';

			}
			//DOWNRIGHT of tile
			else if (finalMoves[k] == 7 && tiles[number + 1][second + 1] != 0 && tiles[number + 1][second + 1] != p) {
				tileCounter = 0;
				i = number + 1;
				j = second + 1;
				while (i <= 7 && j <= 7) {
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

				if ((i != 8 || tiles[i - 1][j - 1] == p) && (j != 8 || tiles[i - 1][j - 1] == p) && tileCounter != 0 && tileExist != false) {
					return true;
				}
				//cout << "DOWNRIGHT" << tileCounter << '\n';

			}
			

		}
		
		return minValidMove;
	}










};//end of class








/*
int manual()
{

	cout << "Starting Manual Game";
	Board board;
	bool gameOverPlayer = false;
	bool gameOverRobot = false;
	bool gameOver = false;
	int choice = 0;
	bool validTile = false;
	bool noMorePlayerTiles = false;
	//cout << "Who goes first? 0 or 1" << '\n'; 
	//cin >> choice;
	while (gameOverRobot == false || gameOverPlayer == false) {
		noMorePlayerTiles = false;
		board.displayBoard();
		
		gameOverPlayer = false;
		if (board.winCondition(true) == 1) {
			noMorePlayerTiles = true;
			gameOverPlayer = true;
			cout << "No Player Moves Left"<<'\n';

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
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board.reset[i][j] = board.tiles[i][j];
			}
		}
		cout << "MCTS:" << '\n';
		bool result = board.MCTS(100);
		cout << '\n' << "RESULT:" << result << '\n';
		if (result == 0) {
			gameOverRobot = true;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					board.tiles[i][j] = board.reset[i][j];
				}
			}
		}

		
	}

	cout << '\n' << "-------GAME OVER-------" << '\n';
	cout << board.calculateWinner()<<" WINS, WITH A SCORE OF:"<< " " << board.winner();
	return 0;
};
*/

int testing()
{
	bool robotWins = true;
	int counter = 0;
	while (robotWins == true) {

		srand((unsigned int)time(NULL));
		cout << '\n'<<"Starting Test Number: "<<counter<<'\n';
		Board board;
		bool gameOverPlayer = false;
		bool gameOverRobot = false;
		bool gameOver = false;
		int choice = 0;
		bool validTile = false;
		
		int randomNumber1;
		int randomNumber2;
		//cout << "Who goes first? 0 or 1" << '\n'; 
		//cin >> choice;
		while (gameOverRobot == false || gameOverPlayer == false) {
			
			board.displayBoard();

			gameOverPlayer = false;
			if (board.winCondition1() == false) {
				cout << "Here";
				gameOverPlayer = true;
				if (gameOverRobot == true) {
					break;
				}
				//cout << "No Player Moves Left" << '\n';

			}
			else {
				
				bool validInput = false;
				bool spaceNotTaken = false;
				string playerInput;
				while (validInput != true) {
					//Create Random Numbers
					randomNumber1 = rand() % 8;
					randomNumber2 = rand() % 8;
					if (board.playPlayerTile(randomNumber1, randomNumber2) == true) {

						//board.validMove(randomNumber1, randomNumber2);
						validTile = board.validPlayerMoves(randomNumber1, randomNumber2, true, false);
						if (validTile == false) {
							board.undoTile(randomNumber1, randomNumber2);
							//cout << "INVALID MOVE, TRY AGAIN" << '\n';
						}
						else {
							board.validPlayerMoves(randomNumber1, randomNumber2, true, true);
							cout << "Player Plays: " << randomNumber1 << ":" << randomNumber2;
							//displayBoard();
							validInput = true;
							
						}

					}
				}


			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					board.reset[i][j] = board.tiles[i][j];
				}
			}
			board.displayBoard();
			cout << "MCTS:" << '\n';
			gameOverRobot = false;
			bool result = board.MCTS(1000);
			cout << '\n' << "RESULT:" << result << '\n';
			if (result == 0) {
				gameOverRobot = true;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						board.tiles[i][j] = board.reset[i][j];
					}
				}
			}



		}

		cout << '\n' << "-------GAME OVER-------" << '\n';
		cout << board.winner() << " WINS, WITH A SCORE OF:" << " " << board.calculateWinner()<< '\n';
		cout << "GAMES WON" << counter  << '\n';
		if (board.winner() == 1) {
			robotWins = false;
			
		}
		counter++;

		
	}
	
	return 0;
};


int testingAgainstBestAI() 
{
	bool robotWins = true;
	int counter = 0;
	int ai=0;
	int mcts=0;
	while (counter < 25) {
		srand((unsigned int)time(NULL));
		cout << '\n' << "Starting Test Number: " << counter << '\n';
		Board board;
		bool gameOverPlayer = false;
		bool gameOverRobot = false;
		bool gameOver = false;
		int choice = 0;
		bool validTile = false;
		int randomNumber1;
		int randomNumber2;
		bool result1;
		bool result2;
		board.displayBoard();
		while (gameOverRobot == false || gameOverPlayer == false) {
			
			cout << "BEST AI:" << '\n';
			result1 = board.bestAI(250);

			cout << '\n' << "BEST AI RESULT: " << result1 << '\n';
			if (result1 == 0) {
				gameOverPlayer = true;
				cout << "Could not play bestAI move";
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						board.tiles[i][j] = board.reset[i][j];
					}
				}
			}

			
			board.displayBoard();
			
			cout << "MCTS:" << '\n';
			gameOverRobot = false;
			result2 = board.MCTS(250);
			cout << '\n' << "MCTS RESULT: " << result2 << '\n';
			if (result2 == 0) {
				gameOverRobot = true;
				cout << "Could not play robot move";
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						board.tiles[i][j] = board.reset[i][j];
					}
				}
			}
			board.displayBoard();

		}


		string winner;
		if (board.winner() == 0) {
			winner = "BESTAI";
			ai++;
		}
		else {
			winner = "MCTS";
			mcts++;
		}
		cout << '\n' << "-------GAME OVER-------" << '\n';
		cout << winner<< " WINS, WITH A SCORE OF:" << " " << board.calculateWinner() << '\n';
		cout << "GAMES WON FOR BESTAI" << ai << '\n';
		cout << "GAMES WON FOR MCTS" << mcts << '\n';
		counter++;

	}
	return 0;
};

int main() {
	cout<<"-------WELCOME-------" << '\n';
	testingAgainstBestAI();
};
