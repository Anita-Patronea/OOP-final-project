#pragma once
#include <iostream>
#include "Utils.h"
#include "AdministratorUI.h"
#include "UserUI.h"


static void runMainMenu()
{
	int option;
	AdministratorUI admin;
    std:: vector<Book> database = admin.database();
    UserUI user{ database };


	std::cout << "Hello there!\n\n";

	do {
		std::cout << "The application can be run in two modes: administrator mode and user mode!\n";
		std::cout << "\t 1. \t Run in administrator mode \n";
		std::cout << "\t 2. \t Run in user mode \n";
		std::cout << "\t 0. \t Exit \n\n";
		std::cout << "Give an option: ";
		option = readInt();
		std::cout << "\n";

		switch (option)
		{
		case 0:
			std::cout << "Bye!Bye!\n";
			return;
		case 1:
			admin.runAdminUI();
			break;
		case 2:
            std:: vector<Book> database = admin.database();
            user.updateDatabase(database);
			user.runUserUI();
			break;
        }
	} while (true);
}
