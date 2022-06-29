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

std::vector<int> Player::placeShips(Board* ptr) {
	std::vector <int> oneShip;
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
		if (choice == "exit"){
			 oneShip.push_back(-1);
			 return oneShip;
		}
		else if(isChoiceCorrect == false)
		{
			system("cls");
			ptr->displayBoard();
			std::cout << "Wrong value! Try again: " << std::endl;
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
			if (coordinates1 == "exit") {
				oneShip.push_back(-1);
				return oneShip;
			}
			format = isFormatCorrect(coordinates1);
			if (format == true)
			{
				oneShip = convertToInt(coordinates1);
				oneShip.push_back(1);
				break;
			}
			else {
				ptr->displayBoard();
				break;
			}
		case 2:
			std::cout << "Enter first coordinate to place a ship: " << std::endl;
			std::cin >> coordinates1;
			if (coordinates1 == "exit") {
				oneShip.push_back(-1);
				return oneShip;
			}
			format = isFormatCorrect(coordinates1);
			if (format == true)
			{
				oneShip = convertToInt(coordinates1);

			}
			else {
				ptr->displayBoard();
				break;
			}
			std::cout << "Enter second  coordinate to place a ship: " << std::endl;
			std::cin >> coordinates2;
			if (coordinates2 == "exit") {
				oneShip.push_back(-1);
				return oneShip;
			}
			format = isFormatCorrect(coordinates2);
			if (format == true)
			{
				std::vector<int> temp;
				temp = convertToInt(coordinates2);
				oneShip.insert(oneShip.end(), temp.begin(), temp.end());
				oneShip.push_back(2);
				break;
			}
			else {
				ptr->displayBoard();
				break;
			}
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
	}
	return target;
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

int Player::howManyFields(int boardSize)
{
	int fields = pow(boardSize, 2);//boardSize ^ 2;                funkcja liczy ile pol jest ogolem   <- nie ma czego? takiego jak ^
	return fields;
}

std::vector<int> Player::howManyShips(int fields)
{
	std::vector<int> ships;

	int howManyFieldsForShips, howManyShip1, howManyShip2;

	howManyFieldsForShips = round(fields * 0.1);       // funkcja zlicza i zaokragla ile jest pol na statki

	if (howManyFieldsForShips % 2 == 1)
	{                                                                // w zaleznosci od tego czy n jest parzyste czy nie funkcja wyswietla ile jest stakow 1 i 2.
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