#include "Player.hpp"
std::string Player::getName() {
	return name;
}

void Player::setName() {
	std::string temp;
	for (;;) {
		std::cout << "Please enter your name (max 10 characters):" << std::endl;
		std::cin >> temp;
		if (temp.size() > 10) {
			std::cout << "Incorrect size, try again" << std::endl;
			Sleep(3000);
			continue;
		}
		else {
			name = temp;
			break;
		}
	}
}

bool Player::checkNumbers(char c)
{
	return c >= '0' && c <= '9';
}

bool Player::isFormatCorrect(std::string& inputCoordinates)
{
	int toInt = 0;
	std::string temp;

	std::transform(inputCoordinates.cbegin(), inputCoordinates.cend(), inputCoordinates.begin(), [](unsigned char c) { return std::toupper(c); });

	if (inputCoordinates.size() < 2 || inputCoordinates.size() > 3 || !isalpha(inputCoordinates[0])) {
		std::cout << "Bad format! You need to enter a letter and number. Try again : " << std::endl;
		Sleep(2000);
		system("cls");
		return false;
	}
	for (int i = 1; i < inputCoordinates.size(); i++) {
		temp.push_back(inputCoordinates[i]);
		if (isdigit(inputCoordinates[i]) == false) {
			std::cout << "Bad format! You need to enter a letter and number. Try again : " << std::endl;
			Sleep(2000);
			system("cls");
			return false;
		}

		if (checkNumbers(temp[i] == true && (inputCoordinates.size() - 1) == i))
		{
			return true;
		}
		else if (checkNumbers(temp[i] == false))
		{
			std::cout << "Bad format! You need to enter a letter and number. Try again:  " << std::endl;
			return false;
		}
	}
	return true;
}

std::vector <int> Player::convertToInt(std::string inputCoordinates)
{
	char arr = inputCoordinates[0];
	int firstLetter = (int)arr - 65 + 1;
	int toInt = 0;
	std::string temp;

	for (int i = 1; i < inputCoordinates.size(); i++)
	{
		temp.push_back(inputCoordinates[i]);
	}

	toInt = std::stoi(temp);
	std::vector<int>inputStringToInt;
	inputStringToInt.push_back(firstLetter);
	inputStringToInt.push_back(toInt);
	return inputStringToInt;
}

std::vector<int> Player::placeShips(Board* ptr, int &ship1, int &ship2) {
	std::vector <int> oneShip(2, 1);
	bool format = false;
	std::string choice{};
	std::string coordinates1{};
	std::string coordinates2{};
	int choice1{ 0 };
	bool isChoiceCorrect{};

	do {
		std::cout << "Enter number to choose type of ship: " << std::endl;
		std::cout << "1. One-block long " << std::endl;
		std::cout << "2. Two-block long " << std::endl;
		std::cin >> choice;
		isChoiceCorrect = isdigit(choice[0]);
		if (choice == "exit") {
			oneShip.push_back(-1);
			return oneShip;
		}
		else if (isChoiceCorrect == false){
			system("cls");
			ptr->displayBoard();
			std::cout << "Wrong value! Try again: " << std::endl;
		}
		else if ((ship1 == 0 && (choice1 = std::stoi(choice)) == 1) || (ship2 == 0 && (choice1 = std::stoi(choice)) == 2)) {
			system("cls");
			ptr->displayBoard();
			std::cout << "This kind of ship has already been placed! " << std::endl;
			isChoiceCorrect = false;
		}
		else {
			choice1 = std::stoi(choice);
			if (choice1 < 1 || choice1 > 2) {
				system("cls");
				ptr->displayBoard();
				std::cout << "Wrong value! Try again: " << std::endl;
			}
		}
	} while (isChoiceCorrect == false || (choice1 < 1 || choice1 > 2));
	do
	{
		switch (choice1)
		{
		case 1:
			std::cout << "Enter coordinate to place a ship: " << std::endl;
			std::cin >> (coordinates1);
			if (coordinates1 == "exit") 
				return exitChoice();
			placeShipsTakeCoordinates(oneShip, ptr, format, coordinates1, 1);
			break;
		case 2:
			std::cout << "Enter first coordinate to place a ship: " << std::endl;
			std::cin >> coordinates1;
			if (coordinates1 == "exit")
				return exitChoice();
			placeShipsTakeCoordinates(oneShip, ptr, format, coordinates1, 1);
			std::cout << "Enter second  coordinate to place a ship: " << std::endl;
			std::cin >> coordinates2;
			if (coordinates1 == "exit")
				return exitChoice();
			placeShipsTakeCoordinates(oneShip, ptr, format, coordinates2, 2);
			break;
		}
	} while (format == false);
	return oneShip;
}

std::vector<int> Player::shooting()
{
	std::vector<int> target;
	int size{}; //temp
	std::string coordinates1{};
	std::cout << "Enter coordinate to shoot " << std::endl;
	std::cin >> coordinates1;

	if (isFormatCorrect(coordinates1) == true)
	{
		target = convertToInt(coordinates1);
		target[0] --;
		target[1] --;
		target.push_back(2);
	}
	return target;
}

std::vector<int> Player::exitChoice() {
	std::vector<int> exit(1, -1);
	return exit;
}

void Player::placeShipsTakeCoordinates(std::vector<int> &oneShip, Board*& ptr, bool& format, std::string coordinates, int switch_) {
	format = isFormatCorrect(coordinates);
	if (format == true)
	{
		if (switch_ == 1)
				oneShip = convertToInt(coordinates);
		else if (switch_ == 2) {
			std::vector<int> temp;
			temp = convertToInt(coordinates);
			oneShip.insert(oneShip.end(), temp.begin(), temp.end());
			oneShip.push_back(2);
		}
	}
	else {
		system("cls");
		ptr->displayBoard();
	}
}

int Player::userInput(int selectMode) {
	std::string temp;
	int size;
	for (;;) {
		system("cls");
		if (selectMode == 1) {
			std::cout << "Please enter the size of battlefield:" << std::endl;
			std::cin >> temp;
			if (temp == "exit") {
				return -1;
			}
			size = stoi(temp);
			if ((size > 5) && (size < 27)) {
				return size;
			}
			else {
				std::cout << "wrong value, try again" << std::endl;
				Sleep(3000);
				continue;
			}
		}
		else if (selectMode == 2) {
			std::cout << "Please enter the number of turns:" << std::endl;
			std::cin >> temp;
			if (temp == "exit") {
				return -1;
			}
			size = stoi(temp);
			if (size >= 0 < 700) {
				return size;
			}
			else {
				std::cout << "wrong value, try again" << std::endl;
				Sleep(3000);
				continue;
			}
		}
	}
}

int Player::howManyFields(int boardSize){
	int fields = pow(boardSize, 2);              
	return fields;
}

std::vector<int> Player::howManyShips(int fields){		// this method calculate number of ships dependent from board size
	std::vector<int> ships;
	int howManyFieldsForShips, howManyShip1, howManyShip2;
	howManyFieldsForShips = round(fields * 0.1);         // <-- this is multiplier for number of ships 

	if (howManyFieldsForShips % 2 == 1)
	{                                                               
		ships.push_back(howManyFieldsForShips / 2 + 1);
		ships.push_back((howManyFieldsForShips - 1) / 4);
	}
	else
	{
		ships.push_back(howManyShip1 = howManyFieldsForShips / 2);
		ships.push_back(howManyFieldsForShips / 4);
	}
	return ships;
}