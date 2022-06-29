#include "board.hpp"

int Board::coordinateVerificator(int& y, int& x, int type) {
	if (y >= 1 && y < size + 1 && x >= 1 && x < size + 1) {
		y--;
		x--;
		switch (type) {
		case 1:							// when placing ships
			if (board[y][x] == 4)
				return 4;
			else
				return 0;
		case 2:							// when shooting
			if (board[y][x] == 0)
				return 0;				//std::cout << "You missed " << std::endl;
			else if (board[y][x] == 4)
				return 4;    //std::cout << "You hit the ship " <<std::endl;
			else
				return -1;
		}
	}
	else {
		std::cout << "Coordinates out of board. Try again! " << std::endl;
		return 0;
	}
}

bool Board::shipVerificator(std::vector<int>& userInput) {
	int shipSize = userInput.back();
	int xBegin = userInput[1];
	int xEnd = userInput[3];
	int yBegin = userInput[0];
	int yEnd = userInput[2];

	if ((yBegin != yEnd == true) && (xBegin != xEnd == true)) {
		std::cout << "Coordinetas are not horizontal or vertical. Try again!" << std::endl;
		return false;
	}
	else if (abs(yBegin - yEnd) > (shipSize - 1) == true || abs(xBegin - xEnd) > (shipSize - 1) == true) {
		std::cout << "Coordinetas are too far from each other. Try again!" << std::endl;
		return false;
	}
	else if (yBegin == yEnd && xBegin == xEnd) {
		std::cout << "first and second Coordinetas are the same. Try again!" << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool Board::placementVerificator(std::vector<int> userInput) {
	int y_ = userInput[0];
	int x_ = userInput[1];
	int typeSize = userInput.back();
	if (userInput.size() > 3 && shipVerificator(userInput) == false) {
		return false;
	}

	int x = 0;

	for (int i = 1; i < userInput.size(); i += 2) {
		y_ = userInput[i - 1] - 1;
		x_ = userInput[i] - 1;
		if (coordinateVerificator(y_, x_, 1) == 4) {
			return false;
			std::cout << "There is a ship already! ";
		}
		for (int y = std::max(0, y_ - 1); y < std::min(size, y_ + 2); y++) {
			int temp = board[y][x_];
			if (board[y][x_] == 4 && y != y_) {
				std::cout << "Another ship is too close! Try again: " << std::endl;
				return false;
			}
			else {
				continue;
			}
		}
		for (x = std::max(0, x_ - 1); x < std::min(size, x_ + 2); x++) {
			if (board[y_][x] == 4 && x != x_) {
				std::cout << "Another ship is too close! Try again: " << std::endl;
				return false;
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