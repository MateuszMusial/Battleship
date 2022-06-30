#include "game.hpp"

void changePlayerPromt(std::string name) {
	system("cls");
	std::cout << "Switch places with player" << name << std::endl;
	std::cout << "press any key to continue" << std::endl;
	_getch();
}

bool endGameCheck(int turnsLeft, int maxPoints1, int maxPoints2, int maxPoints, Player* player1Ptr, Player* player2Ptr) {
	if (turnsLeft == 0) {
		std::cout << "GAME DRAW!" << std::endl;
		return true;
	}
	else if (maxPoints == maxPoints1) {
		std::cout << "\nPlayer: " << player1Ptr->getName() << " has won the game!" << std::endl;
		return true;
	}
	else if (maxPoints == maxPoints2) {
		std::cout << "\nPlayer: " << player2Ptr->getName() << " has won the game!" << std::endl;
		return true;
	}
}

std::vector <int> menu() {
	std::vector <int> choice;
	int size = 0;
	int turns = 0;
	int points1 = 0, points2 = 0;
	std::cout << "Welcome to the Battleship Gajm\n" << std::endl;
	std::cout << "if you want to quit, type ""exit"" anytime" << std::endl;
	Player p1;
	Player* player1Ptr = &p1;
	p1.setName();
	Player p2;
	Player* player2Ptr = &p2;
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
	int maxPoints = choice[0] + choice[1] * 2;

	Board b1(choice[0], choice[1], size);
	b1.initialFill();
	Board b1Oponnent(size);
	b1Oponnent.initialFill();

	std::vector <int> temp;
	int ship1 = 0, ship2 = 0;
	ship1 = choice[0];
	ship2 = choice[1];
	system("cls");
	b1.displayBoard();
	Board* ptr = &b1;

	while (((ship1 != 0) == true) || ((ship2 != 0) == true)) {

		temp = p1.placeShips(ptr, ship1, ship2);
		if (temp[0] == -1) {
			return temp;
		}

		else if (b1.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b1.setElement(temp[i - 1] - 1, temp[i] - 1, 4);
				i++;
			}
			if (temp.size() > 3) {
				system("cls");
				b1.displayBoard();
				ship2--;
				std::cout << "You have to place " << ship1 << " of single ships and " << ship2
					<< " of double ships." << std::endl;
			}
			else {
				system("cls");
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
	Sleep(2000);
	changePlayerPromt(p2.getName());
	choice = p2.howManyShips(p2.howManyFields(size));

	Board b2(choice[0], choice[1], size);
	b2.initialFill();
	Board b2Oponnent(size);
	b2Oponnent.initialFill();
	ptr = &b2;
	system("cls");
	b2.displayBoard();

	while (choice[0] != 0 || choice[1] != 0) {

		temp = p2.placeShips(ptr, choice[0], choice[1]);
		if (temp[0] == -1) {
			return temp;
		}

		else if (b2.placementVerificator(temp) == true) {
			for (int i = 1; i < temp.size(); i++) {

				b2.setElement(temp[i - 1] - 1, temp[i] - 1, 4);
				i++;
			}
			if (temp.size() > 3) {
				system("cls");
				b2.displayBoard();
				choice[1]--;
				std::cout << "You have to place " << choice[0] << " of single ships and " << choice[1]
					<< " of double ships." << std::endl;
			}
			else {
				system("cls");
				b2.displayBoard();
				choice[0] --;
				std::cout << "You have to place " << choice[0] << " of single ships and " << choice[1]
					<< " of double ships." << std::endl;
			}
		}
		else {
			Sleep(3000);
			system("cls");
			b2.displayBoard();
		}
	}
	Sleep(3000);
	changePlayerPromt(p1.getName());

	Board* ptr1 = &b1Oponnent;
	Board* ptr2 = &b2Oponnent;
	int turnsLeft = 0;
	if (turns > 0)
		turnsLeft = turns;

	while (turnsLeft > 0 || turns == 0) {
		std::vector <int> temp;
		int targetResult;
		do {
			system("cls");
			std::cout << p1.getName();
			if (turns == 0)
				std::cout << "        turns unlimited. " << std::endl << std::endl;
			else
				std::cout << "        turns left: " << q << std::endl << std::endl;

			ptr1->displayBoard();
			temp = p1.shooting();
			targetResult = b2.coordinateVerificator(temp[0], temp[1], temp[2], ptr1);
		} while (targetResult < 0);

		switch (targetResult)
		{
		case 0:
			system("cls");
			ptr1->displayBoard();
			b1Oponnent.setElement(temp[0], temp[1], 1);
			std::cout << "You are shooting like a lady!" << std::endl;
			Sleep(3000);
			break;
		case 3:
			system("cls");
			ptr1->displayBoard();
			b1Oponnent.setElement(temp[0], temp[1], 3);
			std::cout << "You destroyed enemy's ship\n";
			points1++;
			Sleep(3000);
			break;

		case 4:
			system("cls");
			ptr1->displayBoard();
			b1Oponnent.setElement(temp[0], temp[1], 2);
			b2.setElement(temp[0], temp[1], 2);
			std::cout << "You hit the target!" << std::endl;
			points1++;
			Sleep(3000);
			break;

		default:
			break;
		}
		if (endGameCheck(turnsLeft, points1, points2, maxPoints, player1Ptr, player2Ptr) == true) {
			choice[0] = 1;
			return choice;
		}
		changePlayerPromt(p2.getName());
		do {
			system("cls");
			std::cout << p2.getName();
			if (turns == 0)
				std::cout << "        turns unlimited. \n\n";
			else
				std::cout << "        turns left: " << q << std::endl << std::endl;

			ptr2->displayBoard();
			temp = p2.shooting();
			targetResult = b1.coordinateVerificator(temp[0], temp[1], temp[2], ptr2);
		} while (targetResult < 0);

		switch (targetResult)
		{
		case 0:
			system("cls");
			ptr2->displayBoard();
			b2Oponnent.setElement(temp[0], temp[1], 1);
			std::cout << "You are shooting like a lady!" << std::endl;
			Sleep(3000);
			break;
		case 3:
			system("cls");
			ptr2->displayBoard();
			b2Oponnent.setElement(temp[0], temp[1], 3);
			std::cout << "You destroyed enemy's ship\n";
			points2++;
			Sleep(3000);
			break;

		case 4:
			system("cls");
			ptr2->displayBoard();
			b2Oponnent.setElement(temp[0], temp[1], 2);
			b1.setElement(temp[0], temp[1], 2);
			std::cout << "You hit the target!" << std::endl;
			points2++;
			Sleep(3000);
			break;

		default:
			break;
		}
		
		turnsLeft--;

		if (endGameCheck(turnsLeft, points1, points2, maxPoints, player1Ptr, player2Ptr) == true){
			choice[0] = 1;
			return choice;
		}
		changePlayerPromt(p2.getName());
	}
}

bool endGameCheck(int turnsLeft, int maxPoints1, int maxPoints2, int maxPoints, Player* playerPtr) {
	if (turnsLeft == 0) {
		std::cout << "GAME DRAW!" << std::endl;
		return true;
	}
	else if (maxPoints == maxPoints1) {
		std::cout << "\nPlayer: " << p1.getName() << " has won the game!" << std::endl;
		return true;
	}
	else if (maxPoints == maxPoints2) {
		std::cout << "\nPlayer: " << p2.getName() << " has won the game!" << std::endl;
		return true;
	}
}