#include "AdministratorUI.h"
#include "Utils.h"

std::string fileName;

//void AdministratorUI::loadDataFromFile(std::string& file)
//{
//	try {
//		std::cout << this->m_admin.loadFromFile(file);
//	}
//	catch (BaseException& e) {
//		std::cout << e.what();
//	}
//}

void AdministratorUI::printOptions()
{
	std::cout << "As administrator, you can perform the following on the book database: \n";
	std::cout << "\t 1. \t See all the books \n";
	std::cout << "\t 2. \t Add a new book \n";
	std::cout << "\t 3. \t Delete a book \n";
	std::cout << "\t 4. \t Update a book \n";
	std::cout << "\t 0. \t Exit \n\n";
}

void AdministratorUI::addA()
{
	std::string title, author, genre, description, cover;
	int publicationYear=0;
	std::cout << "Give the title: "; std::cin.get(); std::getline(std::cin, title); std::cout << "\n";
	std::cout << "Give the author: "; std::getline(std::cin, author); std::cout << "\n";
	std::cout << "Give the genre: "; std::getline(std::cin, genre); std::cout << "\n";
	std::cout << "Give the description: "; std::getline(std::cin, description); std::cout << "\n";
	std::cout << "Give the publication year (valid years: greater than 0): "; publicationYear = readInt(); std::cout << "\n";
	std::cout << "Give the link for the cover: "; std::cin.get(); std::getline(std::cin, cover); std::cout << "\n\n";
	std::cout<<this->m_admin.addAdmin(title, author, genre, description, publicationYear, cover);
}

void AdministratorUI::deleteA()
{
	std::string title, author;
	std::cout << "Give the title of the book you want to delete: "; std::cin.get(); std::getline(std::cin, title); std::cout << "\n";
	std::cout << "Give the author of the book you want to delete: "; std::getline(std::cin, author); std::cout << "\n";
	std::cout << this->m_admin.deleteAdmin(title, author);
}

void AdministratorUI::updateA()
{
	std::string title, author, genre = "", description = "", cover = "";
	int publicationYear = 0, option;
	std::cout << "Give the title of the book you want to update: "; std::cin.get(); std::getline(std::cin, title); std::cout << "\n";
	std::cout << "Give the author of the book you want to update: "; std::getline(std::cin, author); std::cout << "\n";

	std::cout << "Do you want to update the genre? (0 - NO, 1 - YES): "; option = readInt();
	while (option != 0 && option != 1) {
		std::cout << "Please give a valid option!\n";
		option = readInt();
	}
	if (option == 1) {
		std::cout << "Give the genre: "; std::cin.get(); std::getline(std::cin, genre); std::cout << "\n";
	}
	else if (option == 0)
		genre = ""; std::cout << "\n";

	std::cout << "Do you want to update the description? (0 - NO, 1 - YES): "; option = readInt();
	while (option != 0 && option != 1) {
		std::cout << "Please give a valid option!\n";
		option = readInt();
	}
	if (option == 1) {
		std::cout << "Give the description: "; std::cin.get(); std::getline(std::cin, description); std::cout << "\n";
	}
	else if (option == 0)
		genre = ""; std::cout << "\n";

	std::cout << "Do you want to update the publication year? (0 - NO, 1 - YES): "; option = readInt();
	while (option != 0 && option != 1) {
		std::cout << "Please give a valid option!\n";
		option = readInt();
	}
	if (option == 1) {
		std::cout << "Give the publication year (valid years: greater than 0): "; publicationYear = readInt();
	}
	else if (option == 0)
		genre = ""; std::cout << "\n";
	
	std::cout << "Do you want to update the cover? (0 - NO, 1 - YES): "; option = readInt();
	while (option != 0 && option != 1) {
		std::cout << "Please give a valid option!\n";
		option = readInt();
	}
	if (option == 1) {
		std::cout << "Give the link for the cover: "; std::cin.get(); std::getline(std::cin, cover); std::cout << "\n";
	}
	else if (option == 0)
		genre = ""; std::cout << "\n";

	std::cout << this->m_admin.updateAdmin(title, author, genre, description, publicationYear, cover);
}

void AdministratorUI::seeAllA()
{
    std::cout<<this->m_admin.seeAllAdmin();
}

void AdministratorUI::persistence()
{
    try{
    std::cout<<"Please give the name of the file from where you want to upload and save data (.json/ .txt): ";
    std::cin.get(); std::getline(std::cin, fileName);
    std::cout<<"\n";
    std::cout<<this->m_admin.persistenceLoad(fileName);
    }
    catch(BaseException& e){
        std::cout<<e.what();
    }
}

void AdministratorUI::runAdminUI()
{
    this->persistence();
    int option;
	do
	{
		try
		{
			this->printOptions();
			std::cout << "Please give an option: "; std::cin.clear();
			option = readInt();
			std::cout << "\n";

			switch (option)
			{
			case 0:
                try{
                std::cout<<this->m_admin.persistenceSave(fileName);}
                catch (BaseException& e)
                {
                    std::cout << e.what();
                    std::cout << "\n";
                }
                return;
			case 1:
				this->seeAllA();
				break;
			case 2:
				this->addA();
				break;
			case 3:
				this->deleteA();
				break;
			case 4:
				this->updateA();
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
