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

    std::vector<int> placeShips(Board* ptr);
    std::vector<int> shooting();

    void waitingScreen();

    bool isFormatCorrect(std::string& inputCoordinates);
    bool checkNumbers(char c);
    std::vector <int> convertToInt(std::string inputCoordinates);

    int howManyFields(int boardSize);
    std::vector<int> howManyShips(int fields);
    int userInput(int selectMode);
};
