#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include "board.hpp"

class Player
{
private:
    std::string name;
    char c{};
public:

    std::string getName();
    void setName();

    std::vector<int> placeShips(Board* ptr, int &ship1, int &ship2);
    std::vector<int> shooting();
    std::vector<int> exitChoice();

    void placeShipsTakeCoordinates(std::vector<int> &oneShip, Board*& ptr, bool& format, std::string coordinates, int switch_);
    bool isFormatCorrect(std::string& inputCoordinates);
    bool checkNumbers(char c);
    std::vector <int> convertToInt(std::string inputCoordinates);

    int howManyFields(int boardSize);
    std::vector<int> howManyShips(int fields);
    int userInput(int selectMode);
};