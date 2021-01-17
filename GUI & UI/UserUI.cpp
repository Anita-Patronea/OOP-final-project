#pragma once
#include "UserUI.h"
#include "Utils.h"


void UserUI::printOptions()
{
	std::cout << "As user, you can perform the following on your 'TO LISTEN' list: \n";
	std::cout << "\t 1. \t See all the books in your list\n";
	std::cout << "\t 2. \t Add a new book in your list, by going through the database\n";
	std::cout << "\t 3. \t Delete a book from your list\n";
	std::cout << "\t 0. \t Exit \n\n";
}

void UserUI::addU()
{
	std::string genre ="";
	std::cout << "You can see the books in the database by genre, or you can view them all by leaving the genre field blank!\n";
	std::cout << "Give the genre: "; std::cin.get(); std::getline(std::cin, genre); std::cout << "\n";

	this->m_user.shuffleThroughDatabaseUser(genre);
}

void UserUI::deleteU()
{
	std::string title, author;
	std::cout << "Give the title of the book you want to delete: "; std::cin.get(); std::getline(std::cin, title); std::cout << "\n";
	std::cout << "Give the author of the book you want to delete: "; std::getline(std::cin, author); std::cout << "\n";
	std::cout << this->m_user.deleteUser(title, author);
}


void UserUI::seeAllU()
{
	std::cout << this->m_user.seeAllUser();
}

void UserUI::runUserUI()
{
	int option;
	do
	{
		try
		{
			this->printOptions();
			std::cout << "Please give an option: ";
			option = readInt();
			std::cout << "\n";

			switch (option)
			{
			case 0:
				return;
			case 1:
				this->seeAllU();
				break;
			case 2:
				this->addU();
				break;
			case 3:
				this->deleteU();
				break;
			default:
				std::cout << "Please give a valid option!\n\n";
			}
			std::cout << "\n";
		}
		catch (BaseException& e)
		{
			std::cout << e.what();
			std::cout << "\n";
		}
		catch (...)
		{
			std::cout << "Something went wrong! \n\n";
		}
	} while (true);
}
