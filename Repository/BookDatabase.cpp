#pragma once
#include "BookDatabase.h"
#include <algorithm>

bool BookDatabase::addBook (std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover)
{
    if (searchBook(title, author) == this->m_database.size()) {
        Book book{ title, author, genre, description, publication_year, cover };
        this->m_database.push_back(book);
        return true;
    }
    return false; 
}

Book BookDatabase::deleteBook(std::string title, std::string author)
{
    int it = searchBook(title, author);
    if (it == this->m_database.size())
        throw std::string("Inexistent book!");
    Book book=this->m_database[it];
    this->m_database.erase(this->m_database.begin()+it);
    return book;
}

bool BookDatabase::updateBook(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover)
{
    int it = searchBook(title, author);
    if (it == this->m_database.size())
        return false;
    else {
        if (genre != "")
            this->m_database[it].setGenre(genre);
        if (description != "")
            this->m_database[it].setDescription(description);
        if (publication_year != 0)
            this->m_database[it].setPublicationYear(publication_year);
        if (cover != "")
            this->m_database[it].setCover(cover);
    }
    return true;
}

BookDatabase &BookDatabase::operator=(const BookDatabase & otherDB)
{
    for (auto book: otherDB.m_database){
        this->addBook(book.getTitle(),book.getAuthor(),book.getGenre(),book.getDescription(), book.getPublicationYear(), book.getCover());
    }
    return *this;
}
    
int BookDatabase::searchBook(std::string title, std::string author )
{
    int it=0;
    while (it != this->m_database.size()){
        if (this->m_database[it].getTitle() == title && this->m_database[it].getAuthor() == author)
            return it;
        it++;
    }
    return it;
}
