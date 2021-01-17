#pragma once
#include "BookDatabase.h"
#include <stack>

class AdministratorController
{
private:
	BookDatabase m_admin_controller;
    std::stack <std::pair <Book, int> > undoStack, redoStack;  //1-if we add, 2-if we delete, 3-if we update;

public:
	/*
	DESCRIPTION: Adds a new book to the database
	IN: the title, author, genre, description, cover - strings and publication_year - int, of the book
	OUT: string with the operation status, book added or not
	*/
    std::string addAdmin (std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover);


	/*
	DESCRIPTION: Deletes a book from the database
	IN: the title and author - strings of the book
	OUT: string with the operation status, book deleted or not
	*/
	std::string deleteAdmin(std::string title, std::string author);

	/*
	DESCRIPTION: Updates a book from the database
	IN: the title, author, genre, description, cover - strings and publication_year - int, of the book
	OUT: string with the operation status, book updated or not
	*/
	std::string updateAdmin(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover);

	/*
	DESCRIPTION: Returns the string representation of the database
	IN: -
	OUT: string - the string representation of the books from the database
	*/
	std::string seeAllAdmin();

	/*
	DESCRIPTION: Returns the admin database
	IN: -
	OUT: vector<Book> - the books from the database
	*/
    std::vector<Book> returnAdminDatabase() { return this->m_admin_controller.returnDatabase(); }

	/*
	DESCRIPTION: Load initial data to the book database
	IN: file - the file from which it loads the data
	OUT: string with the operation status, if the books were added to the database 
	*/
    //std::string loadFromFile(const std::string& file);

    /*
    DESCRIPTION: Load initial data to the book database from the file given by the admin
    IN: file - the file from which it loads the data JSON/TXT
    OUT: string with the operation status, if the books were added to the database
    */
    std::string persistenceLoad(std::string& fileName);
    std::string persistenceSave(std::string& fileName);

    /*
    @brief - Undoes a step
    @return - true if the step is successfully undone, otherwise throws an exception
    */
    bool undoOperation();

    /*
    @brief - Redoes a step
    @return - true if the step is successfully redone, otherwise throws an exception
    */
    bool redoOperation();
};

