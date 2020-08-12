// Wilson Wu
// 301350197
// CMPT310 Final Project


#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <vector>
using namespace std;
//Used for Colors: https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define BLUE    "\033[34m"      /* Blue */

class Board {
public:	
	//The default Board
	int tiles[8][8] = { { 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,1,2,0,0,0 },
					{ 0,0,0,2,1,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 },
					{ 0,0,0,0,0,0,0,0 } };
	//Used for keeping track of board before Playouts
	int reset[8][8] = { { 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,1,2,0,0,0 },
				{ 0,0,0,2,1,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 },
				{ 0,0,0,0,0,0,0,0 } };
	
	//Array for containing win/lose heuristics for MCTS
	int wins[8][8] = { { 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 } };
	//Array for containing win/lose heuristics for bestAI
	int bestAIWins[8][8]= { { 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 } };
	//Weighted Array for Left Corner
	int bestAIWinsV1[8][8] = { { 0,500,250,100,0,0,0,0 },
						{ 500,250,100,0,0,0,0,0 },
						{ 250,100,0,0,0,0,0,0 },
						{ 100,0,0,0,0,0,0,0 },
						{0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 } };
	//Weighted Array for Right Corner
	int bestAIWinsV2[8][8] = { { 0,0,0,0,100,250,500,0 },
							   { 0,0,0,0,0,100,250,500 },
							   { 0,0,0,0,0,0,100,200 },
							   { 0,0,0,0,0,0,0,100 },
							   { 0,0,0,0,0,0,0,0 },
							   { 0,0,0,0,0,0,0,0 },
							   { 0,0,0,0,0,0,0,0 },
							   { 0,0,0,0,0,0,0,0 } };
	//Weighted Array for Bottom Left Corner
	int bestAIWinsV3[8][8] = { { 0,0,0,0,0,0,0,0 },
							{ 0,0,0,0,0,0,0,0 },
							{ 0,0,0,0,0,0,0,0 },
							{ 0,0,0,0,0,0,0,0 },
							{ 100,0,0,0,0,0,0,0 },
							{ 200,100,0,0,0,0,0,0 },
							{ 500,200,100,0,0,0,0,0 },
							{ 0,500,250,100,0,0,0,0 } };
	//Weighted Array for Bottom Right Corner
	int bestAIWinsV4[8][8] = { { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,100 },
							  { 0,0,0,0,0,0,100,250 },
							  { 0,0,0,0,0,100,250,500 },
							  { 0,0,0,0,100,250,500,0 } };
	//Weighted Array for Left and Right Corner
	int bestAIWinsV12[8][8] = { { 0,500,250,100,100,250,500,0 },
								{ 500,250,100,0,100,250,500,0 },
								{ 250,100,0,0,0,0,100,250 },
								{ 100,0,0,0,0,0,0,100 },
								{0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 },
								{ 0,0,0,0,0,0,0,0 } };
	//Weighted Array for Bottom Left and Bottom Right Corner
	int bestAIWinsV34[8][8]= { { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 0,0,0,0,0,0,0,0 },
							  { 100,0,0,0,0,0,0,100 },
							  { 250,100,0,0,0,0,100,250 },
							  { 500,250,100,0,0,100,250,500 },
							  { 0,500,250,100,100,250,500,0 } };
	//Array for reseting bestAIWins array after bestAI function
	int bestAIWinsReset[8][8]= { { 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 },
						{ 0,0,0,0,0,0,0,0 } };
	
	//Array for reseting tiles array during playouts	
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
	
	std::vector<int> playerTiles{};	//Playable player tiles
	std::vector<int> robotTiles{};	//Playable robot tiles
	std::vector<int> init{};		//Playable Initial tiles
	std::vector<int> init2{};		//Playable Initial tiles (Used with BestAI)

	//Display the current board
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

	//Play the tile at number,second for player. Return False if the tile is already taken.
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
	
	//Play the tile at number,second for robot. Return False if the tile is already taken.
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

	//Set the tile at number,second back to 0 (open tile)
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

	//Check if Player can play anymore tiles. If not, return false
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
	
	//Check if Robot can play anymore tiles. If not, return false
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

	//Return number of player tiles on the current board
	int getNumOfPlayerTiles() {
		int player = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (tiles[i][j] == 1) {
					player++;
				}
			}
		}
		return player;
	}

	//Return the winners amount of tiles at the end of a match/playout
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

	//Return the winners at the end of a match/playout
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

	//Once a tile is played, flip all opposing tiles
	void changeTiles(int number, int second, int direction, int tileCounter, bool player) {
		int i;
		if (player == true) {
			i = 1;
		}
		else {
			i = 2;
		}
		if (direction == 0) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number][second - 1 - x] = i;
				
			}
		}
		else if (direction == 1) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number][second + 1 + x] = i;
				
			}

		}
		else if (direction == 2) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second] = i;
				
			}

		}
		else if (direction == 3) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second] = i;
			}

		}
		else if (direction == 4) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second - 1 - x] = i;
			}
		}
		else if (direction == 5) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number - 1 - x][second + 1 + x] = i;
			}

		}
		else if (direction == 6) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second - 1 - x] = i;
			}

		}
		else if (direction == 7) {
			tilesFlipped += tileCounter;
			for (int x = 0; x < tileCounter; x++) {
				tiles[number + 1 + x][second + 1 + x] = i;
			}
		}
	}

	//Return true if a tile is playable. Otherwise return false
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
						changeTiles(number, second, 6, tileCounter, player);
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
						changeTiles(number, second, 6, tileCounter, player);
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

	
	int tilesFlipped = 0;
	int winCon = 0;
	int whileCounter = 0;
	int thisCounter = 0;
	bool corner1 = false;
	bool corner2 = false;
	bool corner3 = false;
	bool corner4 = false;

	//MONTE CARLO TREE SEARCH FUNCTION. CALCULATES PLAYOUTS AND PLAYS THE BEST TILE.
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
		int first;
		int second;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		
		// Prepare to Reset the tiles before start of function
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				reset[i][j] = tiles[i][j];
			}
		}
		

		playableInitialTiles();	//Calculate Playable Initial Robot Tiles

		//For Every Playable Tile
		for (int x = 0; x <init.size(); x++) {
			
			//Reset the tiles at start of function
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					tiles[i][j] = reset[i][j];
				}
			}

			//Convert number to its coordinates in the 2D array
			first = floor(init[x] / 8);
			second = init[x] % 8;
			//Play the tile for robot 
			playRobotTile(first, second);
			//Check if the move is valid. Play the initial tile if true.
			if (validPlayerMoves(first, second, false, true) == true) {
				//Prepare to Reset the board after a playout
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						reset1[i][j] = tiles[i][j];
					}
				}
				
				finalTilePlayed = true; 			
				
				//Start of playouts
				for (int k = 0; k < playouts; k++) {
					//Reset board 		
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							tiles[i][j] = reset1[i][j];
						}
					}
					
					gameOverPlayer = false;
					gameOverRobot = false;
					
					while (gameOverPlayer == false || gameOverRobot == false) {
						whileCounter++;
						//Player Goes

						//Check if player can play a tile
						gameOverPlayer = false;
						if (winCondition1() == false) {
							gameOverPlayer = true;
							if (gameOverRobot == true) {
								break;
							}
							//cout << "Player CANT PLAY A TILE"<<'\n';
						}
						else {
							
							//Player CAN play a tile
							validInput = false;
							while (validInput == false) {
								//Pick Random Numbers from playerTiles (Which are playable tiles)	
								index = rand() % playerTiles.size(); 
								value = playerTiles[index]; 
								//Convert number to coordinate
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;							
								playPlayerTile(randomNumber1, randomNumber2);
								thisCounter++;							
								if (validPlayerMoves(randomNumber1, randomNumber2, true, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {					
									//VALID MOVE! TILE IS PLAYED
									//displayBoard();
									validInput = true;
								}															
							}
						}

						//Robot Goes

						//Check If Robot can play a tile
						gameOverRobot = false;
						if (winCondition2() == false) {
							gameOverRobot = true;

							//cout << "ROBOT CANT PLAY A TILE";
						}
						else {
							
							
							validInput = false;
							while (validInput == false) {
								//Pick Random Numbers from robotTiles (Which are playable tiles)	

								index = rand() % robotTiles.size(); 
								value = robotTiles[index]; 
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;															
								playRobotTile(randomNumber1, randomNumber2);								
								thisCounter++;
								if (validPlayerMoves(randomNumber1, randomNumber2, false,true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {			
									//VALID MOVE! TILE IS PLAYED
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
					
					//Robot is Winner
					if (winner() == 2) {
						wins[first][second] += 5;
						//Add 5 to win board at first,second
					}
					//Player is Winner
					else if (winner() == 1)
					{
						wins[first][second] -= 2;
						//Subtract 2 from win board at first,second
					}
					
				}
				
			}
			//Tile wasn't valid. Set the tile back to 0.
			else {
				undoTile(first, second);
			}

		}
		//Reset tiles after all playouts
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tiles[i][j] = reset[i][j];
				//cout << wins[i][j]<<" ";
			}
		}
		//Calculate the best tile to play
		if (finalTilePlayed == true) {
			int max = -99999;
			int row;
			int col;
			//Loop through every tile in wins
			for (int i = 0; i < 8; i++) {
				//cout << '\n';
				for (int j = 0; j < 8; j++) {
					//cout << wins[i][j] << " ";
					
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
			if (validPlayerMoves(row, col, false, true) == false) {
				// This should never be printed. Otherwise, there is a bug
				cout << "ERROR" << '\n';
				cout << max;
			}
			
			//cout << "MAX: " << max;
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "ENTIRE MCTS TIME= " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
		//cout << "WHILE: " << whileCounter << '\n';
		//cout << "VALIDPLAYERMOVES CALLS: " << thisCounter << '\n';
		//cout << "WIN CON TOTAL CALLS: " << winCon << '\n';
		//winCon = 0;
		//whileCounter = 0;
		//thisCounter = 0;


		return finalTilePlayed;
	}

	//Modified Version of MCTS
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
		// Prepare board for reset before and after playouts
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				reset[i][j] = tiles[i][j];
			}
		}
		int first;
		int second;
		
		
		playableInitialTiles2();	//Calculate playable initial player tiles

		//For Every Playable Tile
		for (int x = 0; x < init2.size(); x++) {
			
			//Reset Board 
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					tiles[i][j] = reset[i][j];
				}
			}

			//Convert number to coordinates first,second
			first = floor(init2[x] / 8);
			second = init2[x] % 8;
			//Play the tile
			playPlayerTile(first, second);
			if (validPlayerMoves(first, second, true, true) == true) {
				//Valid Move! Play the initial tile
				
				//Prepare reset for tiles during playouts 
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						reset1[i][j] = tiles[i][j];
					}
				}
				
				finalTilePlayed = true;				
				//Start of playouts
				for (int k = 0; k < playouts; k++) {

					//Reset tiles during playout
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							tiles[i][j] = reset1[i][j];
						}
					}
					gameOverPlayer = false;
					gameOverRobot = false;
					//Until both player and robot cannot play anymore moves
					while (gameOverPlayer == false || gameOverRobot == false) {
						whileCounter++;
						//Robot Goes

						//Check if Robot can play a tile
						gameOverRobot = false;
						if (winCondition2() == false) {
							gameOverRobot = true;
							if (gameOverPlayer == true) {
								break;
							}
							//cout << "ROBOT CANT PLAY A TILE";
						}
						else {
							//Robot CAN play a tile
							validInput = false;
							while (validInput == false) {
								//Pick Random Number from playble robot tiles

								index = rand() % robotTiles.size(); 
								value = robotTiles[index]; 
								//Convert to coordinates
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								playRobotTile(randomNumber1, randomNumber2);
								thisCounter++;
								if (validPlayerMoves(randomNumber1, randomNumber2, false, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//Invalid move
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';
								}
								else {
									//Valid move!
									
									validInput = true;
								}
							}
						}
						//Player Goes
						
						//Check if player can play a tile
						gameOverPlayer = false;
						if (winCondition1() == false) {
							gameOverPlayer = true;
							if (gameOverRobot == true) {
								break;
							}
							//cout << "Player CANT PLAY A TILE"<<'\n';
						}
						else {
							//Player CAN play a tile

							validInput = false;
							while (validInput == false) {
						
								//Pick Random Numbers from playerTiles
								index = rand() % playerTiles.size(); 
								value = playerTiles[index];
								//Conver to coordinates
								randomNumber1 = floor(value / 8);
								randomNumber2 = value % 8;
								playPlayerTile(randomNumber1, randomNumber2);
								thisCounter++;
								if (validPlayerMoves(randomNumber1, randomNumber2, true, true) == false) {
									undoTile(randomNumber1, randomNumber2);
									//Invalid Move
									//cout << "INVALID MOVE, TRY AGAIN" << '\n';								
								}
								else {
									//Valid Move!
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
					
					int playerTiles = getNumOfPlayerTiles();
					
					//Winner = Player
					if (winner() == 1) {
												
						bestAIWins[first][second] +=playerTiles;
						
						//If Corner Tile is playble, set weight such that it will play it
						if (first == 0 && second == 0) {
							bestAIWins[first][second] += 100000;
							corner1 = true;
						}
						else if (first == 0 && second == 7) {
							bestAIWins[first][second] += 100000;
							corner2 = true;
						} 
						else if (first == 7 && second == 0) {
							bestAIWins[first][second] += 100000;
							corner3 = true;
						}
						else if (first == 7 && second == 7) {
							bestAIWins[first][second] += 100000;
							corner4 = true;
						}									
					}						
					//Winner = Robot
					else if (winner() == 2)
					{						
						bestAIWins[first][second] -= playerTiles*2;
					}				
				}
			}
			else {
				undoTile(first, second);
				//Invalid Tile, try again
			}

		}
		//Reset tiles 
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				tiles[i][j] = reset[i][j];
			}
		}
		//Calculate tile to play from win array
		if (finalTilePlayed == true) {
			int max = -99999;
			int row;
			int col;
			for (int i = 0; i < 8; i++) {
				//cout << '\n';
				for (int j = 0; j < 8; j++) {
					//cout << bestAIWins[i][j] << " ";
					if (bestAIWins[i][j] > max) {
						if (playPlayerTile(i, j) == true) {
							if ((validPlayerMoves(i, j, true, false) == true)) {
								max = bestAIWins[i][j];
								row = i;
								col = j;
							}
							undoTile(i, j);

						}

					}
					// Reset bestAIWins according to which corners have been played
					if (corner1 == true&& corner2 == true) {
						bestAIWins[i][j] = bestAIWinsV12[i][j];
					}
					else if (corner3 == true && corner4 == true) {
						bestAIWins[i][j] = bestAIWinsV34[i][j];
					}					
					else if (corner1 == true) {
						bestAIWins[i][j] = bestAIWinsV1[i][j];
					}
					else if (corner2 == true) {
						bestAIWins[i][j] = bestAIWinsV2[i][j];
					}
					else if (corner3 == true) {
						bestAIWins[i][j] = bestAIWinsV3[i][j];
					}
					else if (corner4 == true) {
						bestAIWins[i][j] = bestAIWinsV4[i][j];
					}
					else {
						bestAIWins[i][j] = bestAIWinsReset[i][j];
					}
					

				}
			}

			tiles[row][col] = 1;
			cout << '\n'<<"BEST AI PLAYED:" << row << " " << col << '\n';
			if (validPlayerMoves(row, col, true, true) == false) {
				//Should never reach here. Otherwise there is a bug.
				cout << "ERROR" << '\n';
				cout << max;
			}
			//cout << "MAX: " << max;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "ENTIRE BestAI TIME = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
		//cout << "WHILE: " << whileCounter << '\n';
		//cout << "VALIDPLAYERMOVES CALLS: " << thisCounter << '\n';
		//cout << "WIN CON TOTAL CALLS: " << winCon << '\n';
		//winCon = 0;
		//whileCounter = 0;
		//thisCounter = 0;
		return finalTilePlayed;
	}

};//end of class









int manual()
{

	cout << "Starting Manual Game";
	Board board;
	bool gameOverPlayer = false;
	bool gameOverRobot = false;
	bool gameOver = false;
	int choice = 0;
	bool validTile = false;
	//cout << "Who goes first? 0 or 1" << '\n'; 
	//cin >> choice;
	while (gameOverRobot == false || gameOverPlayer == false) {
		
		board.displayBoard();
		
		gameOverPlayer = false;
		if (board.winCondition1() == false) {
			gameOverPlayer = true;
			if (gameOverRobot == true) {
				break;
			}
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
					
						if (board.playPlayerTile(number, second)==true) {
							if (board.validPlayerMoves(number, second, true, true)==false) {
								board.undoTile(number, second);
								cout << "INVALID MOVE, TRY AGAIN" << '\n';
							}
							else {
								board.displayBoard();
								validInput = true;
							}

						}
						else {
							cout << "ERROR: Tile already occupied!" << '\n';
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
		bool result = board.MCTS(5000);
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
	string winner;
	if (board.winner() == 1) {
		winner = "PLAYER";
	}
	else {
		winner = "MCTS";
	}

	cout << '\n' << "-------GAME OVER-------" << '\n';
	cout << winner <<" WINS, WITH A SCORE OF: "<< board.calculateWinner();
	return 0;
};


//Test MCTS against RANDOM PLAYER MOVES. Test until the player wins.
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
		board.displayBoard();
		while (gameOverRobot == false || gameOverPlayer == false) {						
			gameOverPlayer = false;
			if (board.winCondition1() == false) {
				//cout << "Here";
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
						validTile = board.validPlayerMoves(randomNumber1, randomNumber2, true, false);
						if (validTile == false) {
							board.undoTile(randomNumber1, randomNumber2);
							//cout << "INVALID MOVE, TRY AGAIN" << '\n';
						}
						else {
							board.validPlayerMoves(randomNumber1, randomNumber2, true, true);
							cout << "Player Plays: " << randomNumber1 << ":" << randomNumber2;
							board.displayBoard();
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
			
			cout << "MCTS:" << '\n';
			gameOverRobot = false;
			bool result = board.MCTS(1000);
			cout  << "RESULT:" << result << '\n';
			board.displayBoard();
			if (result == 0) {
				gameOverRobot = true;
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						board.tiles[i][j] = board.reset[i][j];
					}
				}
			}



		}
		string winner;
		if (board.winner() == 1) {
			winner = "BEST AI";			
		}
		else {
			winner = "MCTS";			
		}

		cout << '\n' << "-------GAME OVER-------" << '\n';
		cout << winner << " WINS, WITH A SCORE OF:" << " " << board.calculateWinner()<< '\n';
		cout << "MCTS GAMES WON: " << counter  << '\n';
		if (board.winner() == 1) {
			robotWins = false;
			
		}
		counter++;

		
	}
	
	return 0;
};

//Test BestAI VERSUS MCTS
int testingAgainstBestAI() 
{
	bool robotWins = true;
	int counter = 0;
	int ai=0;
	int mcts=0;
	//Test up to 250 games
	while (counter < 250) {
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
			
			cout << '\n' << "-------BEST AI-------";
			result1 = board.bestAI(1000);
			gameOverPlayer = false;
			cout << "BEST AI RESULT: " << result1 << '\n';
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

			cout << '\n' << "-------MCTS-------" << '\n';
			gameOverRobot = false;
			result2 = board.MCTS(1000);
			cout << "MCTS RESULT: " << result2 << '\n';
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
		if (board.winner() == 1) {
			winner = "BEST AI";
			ai++;
		}
		else {
			winner = "MCTS";
			mcts++;
		}
		
		cout << '\n' << "-------GAME OVER-------" << '\n';
		cout << winner<< " WINS, WITH A SCORE OF:" << " " << board.calculateWinner() << '\n';
		cout << "GAMES WON FOR BESTAI " << ai << '\n';
		cout << "GAMES WON FOR MCTS " << mcts << '\n';
		cout << "WINNER TILES:" << board.calculateWinner() << '\n';
		cout << "LOSER TILES:"<< 64 - board.calculateWinner() << '\n';
		counter++;

	}
	return 0;
};

int main() {
	int option;
	cout<<"-------WELCOME-------" << '\n';
	cout << RED <<"Red X = Player OR BestAI" <<RESET<< '\n';
	cout <<BLUE<<"Blue O = MCTS" <<RESET<< '\n';
	cout << "---------------------" << '\n';
	cout << "ALL PLAYOUTS ARE SET TO 1000 BY DEFAULT."<<'\n';
	cout<< "OPTION 3 IS SET TO 250 GAMES BY DEFAULT" << '\n';
	cout << "------------------------------------------------"<< '\n';
	cout  << "OPTION 1: PLAY AGAINST MCTS MANUALLY" << '\n';
	cout << "OPTION 2: MCTS PLAYS AGAINST RANDOM MOVES" << '\n';
	cout << "OPTION 3: MCTS VS. MODIFIED VERSION (Named BestAI)" << '\n';
	cout << "------------------------------------------------" << '\n';
	cout <<"Enter 1 for Option 1 | Enter 2 for Option 2 | Enter 3 for Option 3"<< '\n';
	
	cin >> option;

	bool validOption = false;
	while(validOption == false){
		if (option == 1) {
			manual();
		}
		else if (option == 2) {
			testing();
		}
		else if (option == 3) {
			testingAgainstBestAI();
		}
	}
};
