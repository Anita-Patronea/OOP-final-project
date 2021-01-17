#pragma once
#include "AdministratorController.h"
#include <QString>

class AdministratorUI
{
private:
	AdministratorController m_admin;

	//print menu options for admin user
	void printOptions();
	//add a book to the boook database as admin
	void addA();
	//delete a book from the database as admin
	void deleteA();
	//update a book from the database as admin
	void updateA();
	//print all the books as admin
	void seeAllA();
    //decide on the persistence engine
    void persistence();

public:
	//function that loads books to the database from a file
    //void loadDataFromFile(std::string& filename);

	//funtion that calls a private function from those above, depending on the admins option
	void runAdminUI();

	//returns the admins database (used to set the users shuffling option over the updated database, i.e. an admin adds a new book to the database, the user that comes after him will also see this new book)
    std::vector<Book> database() { return this->m_admin.returnAdminDatabase(); }
};

