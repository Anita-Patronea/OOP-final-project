#pragma once
#include "PersistenceEngine.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "MyExceptions.h"
#include <fstream>

bool PersistenceEngineJSON::load(QString &fileName)
{
    Book book;
    QFile file{fileName};

    bool opened = file.open(QFile::ReadOnly | QFile::Text);
    if(!opened){
        throw AdminException("Unable to open JSON file to load the data!\n\n");
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonArray array = document["bookJSONDatabase"].toArray();

    for(const QJsonValue& bk: array) {
        QJsonObject b = bk.toObject();
        book.setTitle(b["title"].toString().toUtf8().constData());
        book.setAuthor(b["author"].toString().toUtf8().constData());
        book.setGenre(b["genre"].toString().toUtf8().constData());
        book.setDescription(b["description"].toString().toUtf8().constData());
        book.setPublicationYear(b["publicationYear"].toInt());
        book.setCover(b["cover"].toString().toUtf8().constData());

        this->m_database.addBook(book.getTitle(),book.getAuthor(),book.getGenre(),book.getDescription(),book.getPublicationYear(),book.getCover());
    }
    return true;
}

bool PersistenceEngineJSON::save(QString &fileName)
{
    QJsonArray array;
    QJsonObject databaseObject;

    for(auto book:this->m_database.returnDatabase()) {
        array.append(book.toJSONObject());
    }
    databaseObject["bookJSONDatabase"] = array;

    QFile file{fileName};
    bool opened = file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    if(!opened){
        throw AdminException("Unable to open JSON file to save the data!\n\n");
    }

    QJsonDocument saveDocument(databaseObject);
    file.write(saveDocument.toJson());
    file.close();

    return true;
}


bool PersistenceEngineTXT::load(QString &fileName)
{
    std::ifstream iFile;
    iFile.open(fileName.toStdString());
    if(!iFile.is_open())
        throw AdminException("Unable to open TXT file to load the data!\n\n");
    else {
        Book book;
        while (iFile >> book)
        {
            if(book.getTitle()=="EMPTY LINE" && iFile.eof())
                break;
            this->m_database.addBook(book.getTitle(), book.getAuthor(), book.getGenre(), book.getDescription(), book.getPublicationYear(), book.getCover());
        }
        iFile.close();
        return true;
    }
}

bool PersistenceEngineTXT::save(QString &fileName)
{
    std::ofstream oFile;
    oFile.open (fileName.toStdString());
    if(!oFile.is_open())
        throw AdminException("Unable to open TXT file to save the data!\n\n");
    for(auto book:this->m_database.returnDatabase()){
        oFile << book;
    }
    oFile.close();
    return true;
}
