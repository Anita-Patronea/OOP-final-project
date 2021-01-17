#pragma once
#include "Book.h"
#include <array>
#include <vector>


Book::Book(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover)
{
	std::array<std::string, 33> availableGenres = { "action and adventure", "anthology", "classic", "comic and graphic novel", "crime and detective",
		"drama", "fable", "fairy tale", "fan - fiction", "fantasy",  "historical", "horror", "humor", "legend", "magical realism", "mystery",
		"mythology", "realistic fiction", "romance", "satire", "science fiction (sf)", "short story", "thriller", "biography / autobiography",
		"essay", "memoir", "narrative nonfiction", "periodicals", "reference books", "self - help book", "speech", "textbook", "poetry" };
	std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
	int it = 0; bool found = false;
	while (it<33 && found==false){
		if (availableGenres[it].find(genre) != std::string::npos){
			this->m_genre = availableGenres[it];
			found = true;
		}
		it++;
	}
	if (found==false)
		throw BookException("Invalid genre!\n");

	publication_year > 0 ? this->m_publication_year = publication_year : throw BookException("Invalid publication year!\n");

	this->m_title = trim(title);
	this->m_author = trim(author);
	this->m_description = trim(description);
    this->m_cover = trim(cover);
}

Book::Book(const Book &other)
{
    this->m_title = other.m_title;
    this->m_author = other.m_author;
    this->m_genre=other.m_genre;
    this->m_description = other.m_description;
    this->m_publication_year=other.m_publication_year;
    this->m_cover = other.m_cover;
}

Book::~Book()
{
}

void Book::setGenre(std::string genre)
{
	std::array<std::string, 33> availableGenres = { "action and adventure", "anthology", "classic", "comic and graphic novel", "crime and detective",
		"drama", "fable", "fairy tale", "fan - fiction", "fantasy",  "historical", "horror", "humor", "legend", "magical realism", "mystery",
		"mythology", "realistic fiction", "romance", "satire", "science fiction (sf)", "short story", "thriller", "biography / autobiography",
		"essay", "memoir", "narrative nonfiction", "periodicals", "reference books", "self - help book", "speech", "textbook", "poetry"};
	std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);
    int it = 0; bool found = false;
	while (it < availableGenres.size() && found == false){
		if (availableGenres[it].find(genre) != std::string::npos){
			this->m_genre = availableGenres[it];
			found = true;
		}
		it++;
	}
	if (found == false)
        throw BookException("Invalid genre!\n");
}

QJsonObject Book::toJSONObject()
{
    QJsonObject bookObject;

    bookObject["title"] = QString::fromStdString(this->m_title);
    bookObject["author"] = QString::fromStdString(this->m_author);
    bookObject["genre"] = QString::fromStdString(this->m_genre);
    bookObject["description"] = QString::fromStdString(this->m_description);
    bookObject["publicationYear"] = this->m_publication_year;
    bookObject["cover"] = QString::fromStdString(this->m_cover);

    return bookObject;
}


std::ostream& operator<<(std::ostream& stream, const Book& book)
{
//	stream << std::left;
//	stream << std::setw(20) << "TITLE: " << book.m_title << "\n";
//	stream << std::setw(20) << "AUTHOR:" << book.m_author << "\n";
//	stream << std::setw(20) << "GENRE: " << book.m_genre << "\n";
//	stream << std::setw(20) << "DESCRIPTION: " << book.m_description << "\n";
//	std::stringstream s;
//	s << book.m_publication_year;
//	stream << std::setw(20) << "PUBLICATION YEAR: " << s.str() << "\n";
//	stream << std::setw(20) << "COVER" << book.m_cover << "\n";
//	stream << "\n";
//	return stream;
    stream<<book.m_title<<"|"<<book.m_author<<"|"<<book.m_genre<<"|"<<book.m_description<<"|"<<book.m_publication_year<<"|"<<book.m_cover<<"\n";
    return stream;
}


/**
	DESCRIPTION: Tokenizes a string
	IN: str - the string to be tokenized and delimiter - char - the delimiter used for tokenization
	OUT: a vector of strings, containing the tokens
**/
std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream stream(str);
    std::string token;
    while (getline(stream, token, delimiter))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& stream, Book& book) {
    std::string line;
    getline(stream, line);
    if(!line.empty()){
        std::vector<std::string> tokens = tokenize(line, '|');
        if (tokens.size() != 6)
            throw BookException("Error occurred when reading book from file! Invalid number of arguments given for a book!\n");
        book.m_title = tokens[0];
        book.m_author = tokens[1];
        book.m_genre = tokens[2];
        book.m_description = tokens[3];
        int publication_year=0;
        std::istringstream(tokens[4]) >> publication_year;
        book.m_publication_year = publication_year;
        book.m_cover = tokens[5];
    }
    else
        book.m_title="EMPTY LINE";
    return stream;
}

bool operator==(const Book& b1, const Book& b2)
{
	return (b1.m_title==b2.m_title && b1.m_author==b2.m_author && b1.m_genre==b2.m_genre && b1.m_description==b2.m_description && b1.m_publication_year==b2.m_publication_year && b1.m_cover==b2.m_cover);
}
