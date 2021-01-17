#pragma once
#include <QString>
#include <vector>
#include <Book.h>
#include "BookDatabase.h"

class PersistenceEngine
{
protected:
    BookDatabase & m_database;

public:
    PersistenceEngine(BookDatabase& database):m_database(database){};

    virtual bool load(QString& fileName) = 0;
    virtual bool save(QString& fileName) = 0;
};


class PersistenceEngineJSON : public PersistenceEngine
{
public:
    PersistenceEngineJSON(BookDatabase& database): PersistenceEngine{database}{};

    bool load(QString& fileName) override;
    bool save(QString& fileName) override;
};

class PersistenceEngineTXT : public PersistenceEngine
{
public:
    PersistenceEngineTXT(BookDatabase& database): PersistenceEngine{database}{};

    bool load(QString& fileName) override;
    bool save(QString& fileName) override;
};



