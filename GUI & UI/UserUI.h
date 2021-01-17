#pragma once
#include "UserController.h"

class UserUI
{
private:
	UserController m_user;

	//see the user menu
	void printOptions();
	//print all the books from the 'to listen' list
	void seeAllU();
    //add a book to the users 'to listen' list
    void addU();
    //delete a book from the users 'to listen' list
    void deleteU();

public:
    UserUI(std::vector<Book>& database) : m_user(database) {};
    void updateDatabase(std::vector<Book>& database) { m_user.updateDatabase(database); }
	//funtion that calls a private function from those above, depending on the admins option
	void runUserUI();
};
