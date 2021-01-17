#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include "MyExceptions.h"
#include <QJsonObject>


//Class defining a book. Book information: title, author, genre, description, publication year (>0), book cover.
class Book
{
private:
	std::string m_title;
	std::string m_author;
	std::string m_genre;
	std::string m_description;
	int m_publication_year;
	std::string m_cover;
	
	//Remove whitespace from both sides of a T, returns it trimmed.
	template <typename T>
	T trim(T);

public:
	//constructor and destructor
	Book(std::string title = "", std::string author = "", std::string genre = "", std::string description = "", int publication_year = 1, std::string cover = "");
    Book(const Book&);

	~Book();

	//getters
	std::string getTitle() { return this->m_title; }
	std::string getAuthor() { return this->m_author; }
	std::string getGenre() { return this->m_genre; }
	std::string getDescription() { return this->m_description; }
	int getPublicationYear() { return this->m_publication_year; }
	std::string getCover() { return this->m_cover; }

	//setters
	void setTitle(std::string title) { this->m_title = trim(title); }
	void setAuthor(std::string author) { this->m_author = trim(author); }
	void setGenre(std::string genre);
	void setDescription(std::string description) { this->m_description = trim(description); }
	void setPublicationYear(int publication_year) { publication_year > 0 ? this->m_publication_year = publication_year : throw BookException("Invalid publication year!"); }
	void setCover(std::string cover) { this->m_cover = trim(cover); }

	//overloading operators
	friend std::ostream& operator<<(std::ostream& stream, const Book& book);
	friend std::istream& operator>>(std::istream& stream, Book& book);
	friend bool operator==(const Book&, const Book&);

    //function to convert a Book to a JsonObject, then return it
    QJsonObject toJSONObject();

};

template<typename T>
inline T Book::trim(T toTrim)
{
	toTrim.erase(0, toTrim.find_first_not_of("\t\n\v\f\r "));
	toTrim.erase(toTrim.find_last_not_of("\t\n\v\f\r ") + 1);
	return toTrim;
}
