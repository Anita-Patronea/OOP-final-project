#pragma once
#include "AdministratorController.h"

class UserController
{
private:
	BookDatabase m_to_listen;
    std::vector<Book> m_admin_database;


	/*
	DESCRIPTION: Return the option given by the user when shuffling through the books in the database
	IN: -
	OUT: string with the option
	*/
	static std::string getOptionForShuffle();



public:
    UserController(std::vector<Book>& admin_database);

	//update the database of books after the admin does an update/delete/add on it
    void updateDatabase(std::vector<Book>& admin_database) { m_admin_database = admin_database; }

    /*
    DESCRIPTION: Adds a book to the 'to listen' list
    IN: a book - Book
    OUT: string with the operation status, book deleted or not
    */
    std::string addUser(Book book);

	/*
	DESCRIPTION: Shuffling operation that gives to the user the possibility to see all the books with a given genre from the database, one by one, and perform an add operation
	IN: the genre - string of the book
	OUT: -
	*/
	void shuffleThroughDatabaseUser(std:: string genre);

	/*
	DESCRIPTION: Deletes a book from the to listen list
	IN: the title and author - strings of the book
	OUT: string with the operation status, book deleted or not
	*/
	std::string deleteUser(std::string title, std::string author);

	/*
	DESCRIPTION: Returns the string representation of the to listen list
	IN: -
	OUT: string - the string representation of the books from the list
	*/
	std::string seeAllUser();

    /*
    DESCRIPTION: Returns a vector of books filtered by genre
    IN: the genre - string of the book
    OUT: vector with the books that respect the condition
    */
    std::vector<Book> filterByGenre(std::string genre);

    /*
    DESCRIPTION: Returns the to listen database of books
    IN: -
    OUT: a vector with the books
    */
    std::vector<Book> returnToListen(){return this->m_to_listen.returnDatabase();}
};

