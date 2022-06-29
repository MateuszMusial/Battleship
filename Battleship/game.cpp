#include "game.hpp"

std::vector <int> menu() {
	std::vector <int> choice;
	int size=0;
	int turns=0;
	std::cout << "Welcome to battleship game" << std::endl;
	Player p1;
	//p1.setName();
	Player p2;
	//p2.setName();
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
	while (choice[0] != 0 && choice[1] != 0) {
		temp = p1.placeShips();

		if (b1.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b1.setElement(temp[i-1]-1, temp[i]-1, 4);
				i++;
			}
			if (temp.size() > 3) {
				b1.displayBoard();
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
				choice[1]--;
			}
			else {
				b1.displayBoard();
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
				choice[0] --;
			}
		}
		else {
			Sleep(3000);
			system("cls");
			b1.displayBoard();
		}
		
	}


	choice = p2.howManyShips(p2.howManyFields(size));

	Board b2(choice[0], choice[1], size);
	b2.initialFill();
	Board b2Oponnent(size);
	b2Oponnent.initialFill();

	while (choice[0] != 0 && choice[1] != 0) {
		std::vector <int> temp;
		temp = p2.placeShips();

		if (b2.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b2.setElement(temp[i-1]-1, temp[i]-1, 4);
			}
			if (temp.size() > 3) {
				b2.displayBoard();
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
				choice[1]--;
			}
			else {
				b2.displayBoard();
				std::cout << "You have to place " << choice[0] << "of single ships and " << choice[1]
					<< "of double ships." << std::endl;
				choice[0] --;
			}
		}
		else {
			Sleep(3000);
			system("cls");
			b1.displayBoard();
		}
	}

	int q = 0;
	if (turns > 0)
		q = turns;

	while (q > 0 || turns == 0) {
		std::vector <int> temp;
		int targetz;
		do {
			targetz = b2.coordinateVerificator(temp[0], temp[1], temp[2]);
			temp = p1.shooting();
			temp.push_back(1);
		} while (targetz < 0);

		switch (targetz)
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
			targetz = b1.coordinateVerificator(temp[0], temp[1], temp[2]);
			temp = p2.shooting();
			temp.push_back(1);
		} while (targetz < 0);

		switch (targetz)
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