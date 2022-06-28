#include "board.hpp"

int Board::coordinateVerificator(int& y, int& x, int type) {
	if (y >= 1 && y < size + 1 && x >= 1 && x < size + 1) {
		y--;
		x--;
		switch (type) {
		case 1:							// when placing ships
			if (board[y][x] == 4) {
				return 4;
			}
			else {
				return 0;
			}

		case 2:							// when shooting
			if (board[y][x] == 0) {
				return 0;
			}
			else if (board[y][x] == 4) {
				return 4;
			}
			else{
				return -1;
			}
		}
	}
	else
		return 0;
}

bool Board::placementVerificator(std::vector<int> userInput) {
	int y_ = userInput[0];
	int x_ = userInput[1];
	int typeSize = userInput[2];
	if (coordinateVerificator(y_, x_, 1) == 4) {
		return false;
		std::cout << "there is a ship already !!!";
	}
	int x = 0;
	
	for (int i = 0; i < typeSize; i++) {
		y_ = userInput[i]-1;
		x_ = userInput[i + 1]-1;
		for (int y = std::max(0, y_ - typeSize); y < std::min(size, y_ + typeSize); y++) {
			if (board[y][x] == 4 && y != y_) {
			return false;
			}
			else {
				continue;
			}
			for (x = std::max(0, x_ - typeSize); x < std::min(size, x_ + typeSize); x++) {
				if (board[y][x] == 4 && x != x_) {
					return false;
				}
			}
		}
	}
	return true;
}



void Board::initialFill() {
	for (int y = 0; y < size; y++) {
		std::vector <int> v;
		for (int x = 0; x < size; x++) {
			v.push_back(0);
		}
		board.push_back(v);
	}
}

void Board::displayBoard() {
	system("cls");
	int cols = 1;
	char rows = 65;
	for (int y = -1; y < size; y++) {
		if (y >= 0) {
			std::cout << rows;
			rows++;
		}
		else {
			std::cout << " ";
		}
		for (int x = 0; x < size; x++) {
			if (y == -1) {
				printf(" %2d", cols);
				cols++;
			}
			else {
				switch (board[y][x]) {
				case 0:
					std::cout << "  0";
					break;
				case 1:
					std::cout << "  M";
					break;
				case 2:
					std::cout << "  H";
					break;
				case 3:
					std::cout << "  S";
					break;
				case 4:
					std::cout << "  X";
					break;
				}
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

void Board::setElement(int y, int x, int v) {
	board[y][x] = v;
}

int Board::getElement(int y, int x) {
	return board[y][x];
}

Board::Board(int ship1_, int ship2_, int size_) :
	ship1(ship1_),
	ship2(ship2_),
	size(size_)
{}
Board::Board(int _size) :
	size(_size)
{};