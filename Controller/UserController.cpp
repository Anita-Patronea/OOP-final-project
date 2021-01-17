#pragma once
#include "UserController.h"
#include<algorithm>

std::vector<Book> UserController::filterByGenre(std::string genre)
{
	std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
	std::vector<Book> result;
	std::copy_if(this->m_admin_database.begin(), this->m_admin_database.end(), back_inserter(result),
		[genre](Book b) {
			if (b.getGenre().find(genre) != std::string::npos)
				return true;
			return false; });
	return result;
}

std::string UserController::getOptionForShuffle()
{
	std::stringstream str;
	std::string option;
	str << "Give an option: \n";
	str << "\t 'a' - Add book to the 'to listen' list and go to the next one\n";
	str << "\t 'n' - Go to the next book \n";
	str << "\t 'e' - Exit from browsing through the books\n \n";
	str << "Your option is: ";
	std::cout << str.str();
	std::cin.clear(); std::getline(std::cin, option);
	return option;
}

std::string UserController::addUser(Book book)
{
	if (this->m_to_listen.addBook(book.getTitle(), book.getAuthor(), book.getGenre(), book.getDescription(), book.getPublicationYear(), book.getCover()))
		return "Book added to the 'to listen' list!\n\n";
	else return "Add operation failed, duplicate book!\n\n";
}


UserController::UserController(std::vector<Book>& admin_database)
{
	this->m_admin_database = admin_database;
}


void UserController::shuffleThroughDatabaseUser(std::string genre)
{
	std::stringstream strBook;
	std::vector<Book> filteredDatabase;

	if (genre == "")
		filteredDatabase = this->m_admin_database;
	else filteredDatabase=filterByGenre(genre);

	if (filteredDatabase.empty())
		throw UserException("There are no books in the database with the given genre!\n\n");
	else{	
		std::string option;
		int iterator=0;

		while (true) {
			if (iterator == filteredDatabase.size()){
				iterator = 0;
			}

			auto book = filteredDatabase[iterator];
			std::cout<<book<< "\n";
			option=getOptionForShuffle();

			if (option == "a") {
				std::cout << addUser(book);
				iterator += 1;
			}
			else if (option == "n") {
				iterator += 1;
			}
			else if (option == "e")
				return;
			else {
				std::cout << "Invalid option! Please give a valid option!\n\n";
			}
		}
	}
}

std::string UserController::deleteUser(std::string title, std::string author)
{
	if (this->m_to_listen.returnDatabase().empty())
		throw UserException("Empty 'to listen' list!\n");
    try {
        Book book=this->m_to_listen.deleteBook(title, author);
		return "Book deleted from the 'to listen' list!\n";
    }
    catch(...){
    return "Delete operation failed, inexistent book!\n";
    }
}

std::string UserController::seeAllUser()
{
	std::stringstream stream;
	if (this->m_to_listen.returnDatabase().empty())
		stream << "Empty 'to listen' list!\n";
	else {
		stream << "THE BOOKS 'TO LISTEN' ARE: \n\n";
		for (auto book : this->m_to_listen.returnDatabase()) {
			stream << book;
		}
	}
	return stream.str();
}
