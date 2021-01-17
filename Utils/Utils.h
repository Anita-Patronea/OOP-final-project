#pragma once
#include <iostream>

//Reads an int. The function will stop and return the input only when it is correct
static int readInt()
{
	int number = 0;
	bool ok = false;
	while (ok != true) {
		std::cin >> number;
		ok = true;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input! Try again!\n";
			ok = false;
		}
	}
	return number;
}