#pragma once
#include "AdministratorController.h"
#include<fstream>
#include"MyExceptions.h"
#include "PersistenceEngine.h"


std::string AdministratorController::addAdmin(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover)
{
    if (this->m_admin_controller.addBook(title, author, genre, description, publication_year, cover)){
        Book book={title,author,genre,description,publication_year,cover};
        this->undoStack.push({book,1 });  //mark that the operation called was add
        return "Book added to the database!\n";
    }
	else return "Add operation failed, duplicate book!\n";
}

std::string AdministratorController::deleteAdmin(std::string title, std::string author)
{
	if (this->m_admin_controller.returnDatabase().empty())
		throw AdminException("Empty database!\n");
    try{
        Book book=this->m_admin_controller.deleteBook(title, author);
        this->undoStack.push({book,2});      //mark that the operation called was delete
		return "Book deleted from the database!\n";
    }
    catch(...){
        return "Delete operation failed, inexistent book!\n";
    }
}

std::string AdministratorController::updateAdmin(std::string title, std::string author, std::string genre, std::string description, int publication_year, std::string cover)
{
	if (this->m_admin_controller.returnDatabase().empty())
		throw AdminException("Empty database!\n");
	if (this->m_admin_controller.updateBook(title, author, genre, description, publication_year, cover))
		return "Book updated successfully!\n";
	else return "Update operation failed, inexistent book!\n";
}

std::string AdministratorController::seeAllAdmin()
{
	std::stringstream stream;
	if (this->m_admin_controller.returnDatabase().empty())
		stream << "Empty database!\n";
	else {
		stream << "THE BOOKS IN THE DATABASE ARE: \n\n";
		for (auto book : this->m_admin_controller.returnDatabase()) {
			stream << book;
		}
	}
    return stream.str();
}

//std::string AdministratorController::loadFromFile(const std::string& file)
//{
//	std::ifstream f;
//	f.open(file);
//	if(!f.is_open())
//        throw AdminException("Initial data load from file failed! File opening failed!\n");

//	else {
//		Book book;
//		while (f >> book)
//		{
//			this->m_admin_controller.addBook(book.getTitle(), book.getAuthor(), book.getGenre(), book.getDescription(), book.getPublicationYear(), book.getCover());
//			if (f.eof())
//				break;
//		}
//		f.close();
//		return "Books successfully loaded from file!\n\n";
//    }

//}

std::string AdministratorController::persistenceSave(std::string &fileName)
{
    QString fileNameQ = QString::fromStdString(fileName);
    BookDatabase database=this->m_admin_controller;
    if (fileName.find(".json") != std::string::npos){
        PersistenceEngineJSON JSON{database};
        bool ok=JSON.save(fileNameQ);
            if(ok==1)
                return "Successfully saved to JSON!\n\n";
    }
    else if (fileName.find(".txt") != std::string::npos){
        PersistenceEngineTXT TXT{database};
        bool ok=TXT.save(fileNameQ);
            if(ok==1)
                return "Successfully saved to TXT!\n\n";
    }
    else throw AdminException("The changes made to the database were not saved in any file!\n\n");
}

std::string AdministratorController::persistenceLoad(std::string &fileName)
{
   QString fileNameQ = QString::fromStdString(fileName);
   BookDatabase database;
   if (fileName.find(".json") != std::string::npos){
       PersistenceEngineJSON JSON{database};
       bool ok=JSON.load(fileNameQ);
           if(ok==1){
               this->m_admin_controller=database;
               return "Successfully loaded from JSON!\n\n";
           }
   }
   else if (fileName.find(".txt") != std::string::npos){
       PersistenceEngineTXT TXT{database};
       bool ok=TXT.load(fileNameQ);
           if(ok==1){
               this->m_admin_controller=database;
               return "Successfully loaded from TXT!\n\n";
           }
   }
   else throw AdminException("Invalid file type!\n\n");
}

bool AdministratorController::undoOperation()
{
    if (!undoStack.empty())
    {
        Book b = this->undoStack.top().first;
        switch (this->undoStack.top().second)
        {
        case 1:     //op was add elem to repo => we have to delete elem from the repo
            this->m_admin_controller.deleteBook(b.getTitle(), b.getAuthor());
            this->redoStack.push({ b, 1 }); //mark that the initial op was add
            break;
        case 2:     //op was delete elem from repo=> we have to add elem to the repo
            this->m_admin_controller.addBook(b.getTitle(),b.getAuthor(),b.getGenre(),b.getDescription(),b.getPublicationYear(),b.getCover());
            this->redoStack.push({ b, 2 }); //mark that the initial op was add
            break;
        default:
            throw std::string("No such undo operation!");
        }
        this->undoStack.pop();

        return true;
    }
    else throw std::string("No available undo steps!");
}

bool AdministratorController::redoOperation()
{
    if (!redoStack.empty())
    {
        Book b = this->redoStack.top().first;
        switch (this->redoStack.top().second)
        {
        case 1:     //initial op was add elem to repo => we have to re-add elem to the repo
            this->m_admin_controller.addBook(b.getTitle(),b.getAuthor(),b.getGenre(),b.getDescription(),b.getPublicationYear(),b.getCover());
            this->undoStack.push({ b, 1 });
            break;
        case 2:     //initial op was delete elem from repo=> we have to delete again elem from the repo
            this->m_admin_controller.deleteBook(b.getTitle(), b.getAuthor());
            this->undoStack.push({ b, 2 });
            break;
        default:
            throw std::string("No such redo operation!");
        }
        this->redoStack.pop();
        return true;
    }
    else throw std::string("No available redo steps!");
}

