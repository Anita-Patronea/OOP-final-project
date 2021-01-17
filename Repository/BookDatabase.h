#pragma once
#include "Book.h"
#include <vector>

//Book Database class, designed to store all the available books.
class BookDatabase
{
private:
	std::vector<Book> m_database;

	/*
	DESCRIPTION: Searches for book in the database
	IN: the title, author - strings of the book
	OUT: position of the book - if the book is found, the lenght of the database - if the book is not in the database
	*/
	int searchBook(std::string title, std::string author);

public:
	/*
	DESCRIPTION: Adds a new book to the database
	IN: the title, author, genre, description, cover - strings and publication_year - int, of the book
	OUT: true - if the book was successfully added, false - if the book is already in the database 
	*/
	bool addBook(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover);

	/*
	DESCRIPTION: Deletes a book from the database
	IN: the title and author - strings of the book
    OUT: book - returns the book,if it was successfully deleted
	*/
    Book deleteBook(std::string title, std::string author);

	/*
	DESCRIPTION: Updates a book from the database
	IN: the title, author, genre, description, cover - strings and publication_year - int, of the book
	OUT: true - if the book was successfully updated, false - if the book is already in the database
	*/
	bool updateBook(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover);

	/*
	DESCRIPTION: Returns the database
	IN: -
	OUT: vector<Book> - the books from the database
	*/
	std::vector<Book> returnDatabase() { return this->m_database; }

    /*
    DESCRIPTION: Set the database
    IN: vector<Book> - the books from the database
    OUT: -
    */
    void setDatabase(std::vector <Book> database) { this->m_database = database; }

    BookDatabase &operator=(const BookDatabase&);

};

