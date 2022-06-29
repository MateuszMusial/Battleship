#include "game.hpp"


void changePlayerPromt() {
	system("cls");
	std::cout << "Switch places with player 2" << std::endl;
	std::cout << "press any key to continue" << std::endl;
	_getch();
}

std::vector <int> menu() {
	std::vector <int> choice;
	int size = 0;
	int turns = 0;
	std::cout << "Welcome to battleship game" << std::endl;
	Player p1;
	p1.setName();
	Player p2;
	p2.setName();
	choice.push_back(p1.userInput(1));
	if (choice[0] == -1) {

		return choice;
	}
	size = choice[0];
	choice.push_back(p1.userInput(2));
	if (choice[1] == -1) {
		return choice;
	}
	turns = choice[1];

	choice = p1.howManyShips(p1.howManyFields(size));

	Board b1(choice[0], choice[1], size);
	b1.initialFill();
	Board b1Oponnent(size);
	b1Oponnent.initialFill();

	std::vector <int> temp;
	int ship1 = 0, ship2 = 0;
	ship1 = choice[0];
	ship2 = choice[1];
	b1.displayBoard();
	Board* ptr = &b1;

	while (((ship1 != 0) == true) || ((ship2 != 0) == true)) {

		temp = p1.placeShips(ptr);
		if (temp[0] == -1) {
			return temp;
		}

		else if (b1.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b1.setElement(temp[i - 1] - 1, temp[i] - 1, 4);
				i++;
			}
			if (temp.size() > 3) {
				b1.displayBoard();
				ship2--;
				std::cout << "You have to place " << ship1 << " of single ships and " << ship2
					<< " of double ships." << std::endl;
			}
			else {
				b1.displayBoard();
				ship1--;
				std::cout << "You have to place " << ship1 << " of single ships and " << ship2
					<< " of double ships." << std::endl;
			}
		}
		else {
			Sleep(3000);
			system("cls");
			b1.displayBoard();
		}
	}
	changePlayerPromt();
	choice = p2.howManyShips(p2.howManyFields(size));

	Board b2(choice[0], choice[1], size);
	b2.initialFill();
	Board b2Oponnent(size);
	b2Oponnent.initialFill();
	ptr = &b2;

	while (choice[0] != 0 || choice[1] != 0) {

		temp = p2.placeShips(ptr);
		if (temp[0] == -1) {
			return temp;
		}

		else if (b2.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b2.setElement(temp[i - 1], temp[i] - 1, 4);
			}
			if (temp.size() > 3) {
				b2.displayBoard();
				choice[1]--;
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
			}
			else {
				b2.displayBoard();
				choice[0] --;
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
			}
		}
		else {
			Sleep(3000);
			system("cls");
			b1.displayBoard();
		}
	}

	changePlayerPromt();
	int q = 0;
	if (turns > 0)
		q = turns;

	while (q > 0 || turns == 0) {
		std::vector <int> temp;
		int z;
		do {
			z = b2.coordinateVerificator(temp[0], temp[1], temp[2]);
			temp = p1.shooting();
			temp.push_back(1);
		} while (z < 0);

		switch (z)
		{
		case 0:
			b1Oponnent.setElement(temp[0], temp[1], 1);

		case 4:
			b1Oponnent.setElement(temp[0], temp[1], 2);
			b2.setElement(temp[0], temp[1], 2);
		default:
			break;
		}

		do {
			z = b1.coordinateVerificator(temp[0], temp[1], temp[2]);
			temp = p2.shooting();
			temp.push_back(1);
		} while (z < 0);

		switch (z)
		{
		case 0:
			b2Oponnent.setElement(temp[0], temp[1], 1);

		case 4:
			b2Oponnent.setElement(temp[0], temp[1], 2);
			b1.setElement(temp[0], temp[1], 2);
		default:
			break;
		}
	}
}
