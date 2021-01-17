#pragma once
#include "admingui.h"
#include "AdministratorController.h"
#include <QFileDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidgetItem>
#include <string>
#include <QDebug>
#include <QHeaderView>
#include <QShortcut>

AdminGUI::AdminGUI(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Administrator");
    this->setMinimumSize(QSize(600,500));

    m_controller=new AdministratorController{};

    QWidget *centralWidget = createCentralWidget();
    this->setCentralWidget(centralWidget);
}
AdminGUI::~AdminGUI()
{
}


void AdminGUI::populateDatabase()
{
    try{
    m_repoTableWidget->clearContents();

    std::vector<Book> database = this->m_controller->returnAdminDatabase();
    m_repoTableWidget->setRowCount(database.size());

    int i=0;
    for(auto book: database){
        QIcon *icon=new QIcon(book.getCover().c_str());
        m_repoTableWidget->setItem(i,0,new QTableWidgetItem(*icon,book.getCover().c_str()));
        m_repoTableWidget->setItem(i,1,new QTableWidgetItem(book.getTitle().c_str()));
        m_repoTableWidget->setItem(i,2,new QTableWidgetItem(book.getAuthor().c_str()));
        m_repoTableWidget->setItem(i,3,new QTableWidgetItem(std::to_string(book.getPublicationYear()).c_str()));
        m_repoTableWidget->setItem(i,4,new QTableWidgetItem(book.getGenre().c_str()));
        m_repoTableWidget->setItem(i,5,new QTableWidgetItem(book.getDescription().c_str()));
        i++;
    }}
    catch(BaseException &e){
        std::cout<<e.what();
    }
}


void AdminGUI::addBook()
{
    try{
    std::string title, author, genre, description, cover;
    int publication_year;
    title=m_title->text().toStdString();
    author=m_author->text().toStdString();
    genre=m_genre->text().toStdString();
    description=m_description->text().toStdString();
    publication_year=m_publication_year->text().toInt();
    cover=m_cover->text().toStdString();

    m_controller->addAdmin(title, author, genre, description, publication_year, cover);
    populateDatabase();

    m_title->clear();
    m_author->clear();
    m_publication_year->clear();
    m_genre->clear();
    m_description->clear();
    m_cover->clear();

    std::string s = m_persistenceFileName->text().toStdString();
    std::string ok = m_controller->persistenceSave(s);
    }
    catch(BaseException &e){
        std::cout<<e.what();
    }
}


void AdminGUI::deleteBook()
{
    try{
    std::string title, author;
    title=m_title->text().toStdString();
    author=m_author->text().toStdString();

    m_controller->deleteAdmin(title, author);
    populateDatabase();

    m_title->clear();
    m_author->clear();
    m_publication_year->clear();
    m_genre->clear();
    m_description->clear();
    m_cover->clear();

    std::string s = m_persistenceFileName->text().toStdString();
    std::string ok = m_controller->persistenceSave(s);}
    catch(BaseException &e){
        std::cout<<e.what();
    }
}


void AdminGUI::updateBook()
{
    try{
    std::string title, author, genre, description, cover;
    int publication_year;
    title=m_title->text().toStdString();
    author=m_author->text().toStdString();
    genre=m_genre->text().toStdString();
    description=m_description->text().toStdString();
    publication_year=m_publication_year->text().toInt();
    cover=m_cover->text().toStdString();

    m_controller->updateAdmin(title, author, genre, description, publication_year, cover);
    populateDatabase();

    m_title->clear();
    m_author->clear();
    m_publication_year->clear();
    m_genre->clear();
    m_description->clear();
    m_cover->clear();

    std::string s = m_persistenceFileName->text().toStdString();
    std::string ok = m_controller->persistenceSave(s);
    }
    catch(BaseException &e){
        std::cout<<e.what();
    }
}

void AdminGUI::cellClicked(int row)
{
    m_title->insert(m_repoTableWidget->item(row,1)->text());
    m_author->insert(m_repoTableWidget->item(row,2)->text());
}

void AdminGUI::undo()
{
   bool ok= m_controller->undoOperation();
   populateDatabase();

   std::string s = m_persistenceFileName->text().toStdString();
   std::string okP = m_controller->persistenceSave(s);
}

void AdminGUI::redo()
{
    bool ok= m_controller->redoOperation();
    populateDatabase();

    std::string s = m_persistenceFileName->text().toStdString();
    std::string okP = m_controller->persistenceSave(s);
}

void AdminGUI::createTableWidget()
{
    m_repoTableWidget=new QTableWidget(this);
    m_repoTableWidget->setColumnCount(6);
    m_repoTableWidget->setSortingEnabled(true);
    m_repoTableWidget->setStyleSheet("color:#144017");
    m_repoTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_repoTableWidget->verticalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_repoTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Cover"));
    m_repoTableWidget->horizontalHeader()->setMinimumSectionSize(200);
    m_repoTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Title"));
    m_repoTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Author"));
    m_repoTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Publication year"));
    m_repoTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Genre"));
    m_repoTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Description"));

    connect(m_repoTableWidget->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &AdminGUI:: cellClicked);
}


void AdminGUI::searchPersistenceFile()
{
    QString path;
    path = QFileDialog:: getOpenFileName(this, "Select persistence file", "", "(*.json *.txt)");
    m_persistenceFileName->setText(path);
}
void AdminGUI::populateDatabaseFromFile()
{
    try{
    m_repoTableWidget->clearContents();
    std::string s = m_persistenceFileName->text().toStdString();
    m_controller->persistenceLoad(s);
    populateDatabase();
    }
    catch(BaseException &e){
        std::cout<<e.what();
    }
}
QWidget *AdminGUI::createPersistenceWidget()
{
    QLabel *label = new QLabel("Persistence file name:", this);
    m_persistenceFileName = new QLineEdit(this);

    QPushButton *buttonBrowse = new QPushButton("&Browse",this);
    QPushButton *buttonPopulate = new QPushButton("&Populate database",this);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(label,0,0);
    grid->addWidget(m_persistenceFileName,0,1);
    grid->addWidget(buttonBrowse,0,2);
    grid->addWidget(buttonPopulate,0,3);

    connect(buttonBrowse, &QPushButton:: pressed, this, &AdminGUI:: searchPersistenceFile );
    connect(buttonPopulate, &QPushButton:: pressed, this, &AdminGUI:: populateDatabaseFromFile );

    QWidget *widget=new QWidget(this);
    widget->setLayout(grid);

    return widget;
}


QWidget *AdminGUI::createDataAboutBookWidget()
{
    QLabel *labelTitle = new QLabel("Title:", this);
    m_title = new QLineEdit(this);
    QLabel *labelAuthor = new QLabel("Author:", this);
    m_author = new QLineEdit(this);
    QLabel *labelPublicationYear = new QLabel("Publication year:", this);
    m_publication_year = new QLineEdit(this);
    QLabel *labelGenre = new QLabel("Genre:", this);
    m_genre = new QLineEdit(this);
    QLabel *labelDescription = new QLabel("Description:", this);
    m_description = new QLineEdit(this);
    QLabel *labelCover = new QLabel("Cover:", this);
    m_cover = new QLineEdit(this);

    QLabel *help=new QLabel(this);
    help->setText("\nAdd a new book: to add a new book fill in the above fields with the corresponding data, then click on the 'Add' button.\nUpdate a book: to update a book, double-click on that book (book number), then fill in the above fields with the corresponding data, finally click on the 'Update' button.\nDelete a book: to delete a book, double-click on that book (book number), then click on the 'Delete' button.\nUse: 'CTRL+X' - for undo, 'CTRL+Z' - for redo.");

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(labelTitle,0,0);
    grid->addWidget(m_title,0,1);
    grid->addWidget(labelAuthor,1,0);
    grid->addWidget(m_author,1,1);
    grid->addWidget(labelPublicationYear,2,0);
    grid->addWidget(m_publication_year,2,1);
    grid->addWidget(labelGenre,3,0);
    grid->addWidget(m_genre,3,1);
    grid->addWidget(labelDescription,4,0);
    grid->addWidget(m_description,4,1);
    grid->addWidget(labelCover,5,0);
    grid->addWidget(m_cover,5,1);
    grid->addWidget(help,6,0,1,2);

    QWidget* widget = new QWidget(this);
    widget->setLayout(grid);

    return widget;
}


QWidget *AdminGUI::createButtonsWidget()
{
    QPushButton *buttonAdd = new QPushButton("&Add",this);
    QPushButton *buttonUpdate = new QPushButton("&Update",this);
    QPushButton *buttonDelete = new QPushButton("&Delete",this);

    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(buttonAdd);
    hBoxLayout->addWidget(buttonUpdate);
    hBoxLayout->addWidget(buttonDelete);

    connect(buttonAdd, &QPushButton:: pressed, this, &AdminGUI:: addBook );
    connect(buttonUpdate, &QPushButton:: pressed, this, &AdminGUI:: updateBook );
    connect(buttonDelete, &QPushButton:: pressed, this, &AdminGUI:: deleteBook );

    QWidget* widget=new QWidget(this);
    widget->setLayout(hBoxLayout);

    return widget;
}


QWidget *AdminGUI::createCentralWidget()
{
    try{
    QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this);
    connect(undoShortcut, &QShortcut::activated, this, &AdminGUI:: undo);
    QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    connect(redoShortcut, &QShortcut::activated, this, &AdminGUI:: redo);

    QWidget* persistenceWidget = createPersistenceWidget();
    createTableWidget();
    QWidget* bookDataWidget = createDataAboutBookWidget();
    QWidget* buttonsWidget = createButtonsWidget();

    QFrame* line =  new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(persistenceWidget);
    vBoxLayout->addWidget(line);
    vBoxLayout->addWidget(m_repoTableWidget);
    vBoxLayout->addWidget(bookDataWidget);
    vBoxLayout->addWidget(buttonsWidget);

    QWidget* widget=new QWidget(this);
    widget->setLayout(vBoxLayout);

    return widget;}
    catch(...)
    {qDebug()<<"dsadas";}
}


