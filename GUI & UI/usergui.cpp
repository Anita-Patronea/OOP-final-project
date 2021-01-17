#pragma once
#include "usergui.h"
#include <QHeaderView>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>


UserGUI::UserGUI(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("User");
    this->setMinimumSize(QSize(1600,600));

    AdministratorController *admin=new AdministratorController{};
    std::string file="C:\\Users\\Annie\\Desktop\\Audible\\JSONDatabase.json";
    admin->persistenceLoad(file);
    std::vector<Book> database=admin->returnAdminDatabase();
    m_controller=new UserController{database};

    QWidget *centralWidget = createCentralWidget();
    this->setCentralWidget(centralWidget);
}

void UserGUI::populateDatabase()
{
    try{
    m_repoTableWidget->clearContents();

    std::vector<Book> database = this->m_controller->filterByGenre(m_genreForFilter->text().toStdString());
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

void UserGUI::populateToListen()
{
    try{
    m_toListenTableWidget->clearContents();

    std::vector<Book> toListen = this->m_controller->returnToListen();
    m_toListenTableWidget->setRowCount(toListen.size());

    int i=0;
    for(auto book: toListen){
        QIcon *icon=new QIcon(book.getCover().c_str());
        m_toListenTableWidget->setItem(i,0,new QTableWidgetItem(*icon,book.getCover().c_str()));
        m_toListenTableWidget->setItem(i,1,new QTableWidgetItem(book.getTitle().c_str()));
        m_toListenTableWidget->setItem(i,2,new QTableWidgetItem(book.getAuthor().c_str()));
        m_toListenTableWidget->setItem(i,3,new QTableWidgetItem(std::to_string(book.getPublicationYear()).c_str()));
        m_toListenTableWidget->setItem(i,4,new QTableWidgetItem(book.getGenre().c_str()));
        m_toListenTableWidget->setItem(i,5,new QTableWidgetItem(book.getDescription().c_str()));
        i++;
    }}
    catch(BaseException &e){
        std::cout<<e.what();
    }
}

void UserGUI::addBookButtonPressed()
{
    int selectedRow = m_repoTableWidget->currentRow();
    if(selectedRow < 0){
        return;}
    std::vector<Book> database = this->m_controller->filterByGenre(m_genreForFilter->text().toStdString());
    Book book=database[selectedRow];
    m_controller->addUser(book);

    populateToListen();
}

void UserGUI::deleteBookButtonPressed()
{
    int selectedRow = m_toListenTableWidget->currentRow();
    if(selectedRow < 0){
        return;}
    std::vector<Book> database = this->m_controller->returnToListen();
    Book book=database[selectedRow];
    m_controller->deleteUser(book.getTitle(),book.getAuthor());

    populateToListen();
}

void UserGUI::deleteBook(int row)
{
    m_controller->deleteUser(m_toListenTableWidget->item(row,1)->text().toStdString(), m_toListenTableWidget->item(row,2)->text().toStdString());
    populateToListen();
}

void UserGUI::addBook(int row)
{
//    Book book={};
//    book.setTitle(m_repoTableWidget->item(row,1)->text().toStdString());
//    book.setAuthor(m_repoTableWidget->item(row,2)->text().toStdString());
//    book.setGenre(m_repoTableWidget->item(row,4)->text().toStdString());
//    book.setDescription(m_repoTableWidget->item(row,5)->text().toStdString());
//    book.setPublicationYear(m_repoTableWidget->item(row,3)->text().toInt());
//    book.setCover(m_repoTableWidget->item(row,0)->text().toStdString());
    std::vector<Book> database = this->m_controller->filterByGenre(m_genreForFilter->text().toStdString());
    Book book=database[row];
    m_controller->addUser(book);

    populateToListen();
}

void UserGUI::createToListenTableWidget()
{
    m_toListenTableWidget=new QTableWidget(this);
    m_toListenTableWidget->setColumnCount(6);
    m_toListenTableWidget->setSortingEnabled(true);
    m_toListenTableWidget->setStyleSheet("color:#144017");
    m_toListenTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_toListenTableWidget->verticalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_toListenTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Cover"));
    m_toListenTableWidget->horizontalHeader()->setMinimumSectionSize(160);
    m_toListenTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Title"));
    m_toListenTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Author"));
    m_toListenTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Publication year"));
    m_toListenTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Genre"));
    m_toListenTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Description"));

    connect(m_toListenTableWidget->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &UserGUI:: deleteBook);
}

void UserGUI::createRepoTableWidget()
{
    m_repoTableWidget=new QTableWidget(this);
    m_repoTableWidget->setColumnCount(6);
    m_repoTableWidget->setSortingEnabled(true);
    m_repoTableWidget->setStyleSheet("color:#144017");
    m_repoTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_repoTableWidget->verticalHeader()->setStyleSheet("QHeaderView::section { background-color:#b3b3b3; color:#0a7311}");
    m_repoTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Cover"));
    m_repoTableWidget->horizontalHeader()->setMinimumSectionSize(160);
    m_repoTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Title"));
    m_repoTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Author"));
    m_repoTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Publication year"));
    m_repoTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Genre"));
    m_repoTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Description"));

    connect(m_repoTableWidget->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, &UserGUI:: addBook);
}

QWidget *UserGUI::createFilterByGenreWidget()
{
    QLabel *label = new QLabel("Search by genre:", this);
    m_genreForFilter = new QLineEdit(this);
    QPushButton *buttonSearch = new QPushButton("Search",this);

    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(label,0,0);
    grid->addWidget(m_genreForFilter,0,1);
    grid->addWidget(buttonSearch,0,2);

    connect(buttonSearch, &QPushButton:: pressed, this, &UserGUI:: populateDatabase );

    QWidget *widget=new QWidget(this);
    widget->setLayout(grid);

    return widget;
}

QWidget *UserGUI::createDatabaseToListenWidget()
{
    createRepoTableWidget();
    createToListenTableWidget();
    QLabel *repo = new QLabel("Book repository:", this);
    QLabel *toListen = new QLabel("To listen list:", this);
    QPushButton* buttonAdd = new QPushButton("Add",this);
    QPushButton *buttonDelete = new QPushButton("Delete",this);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(repo,0,0);
    gridLayout->addWidget(toListen,0,2);
    gridLayout->addWidget(m_repoTableWidget,1,0);
    gridLayout->addWidget(m_toListenTableWidget,1,2);
    gridLayout->addWidget( buttonAdd,2,0);
    gridLayout->addWidget(buttonDelete,2,2);

    QWidget* widget=new QWidget(this);
    widget->setLayout(gridLayout);

    connect(buttonAdd, &QPushButton:: pressed, this, &UserGUI:: addBookButtonPressed );
    connect(buttonDelete, &QPushButton:: pressed, this, &UserGUI:: deleteBookButtonPressed );

    return widget;
}

QWidget *UserGUI::createCentralWidget()
{
    QWidget* filterByGenreWidget = createFilterByGenreWidget();
    QWidget* databaseAndToListenWidget = createDatabaseToListenWidget();

    QFrame* line =  new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(filterByGenreWidget);
    vBoxLayout->addWidget(line);
    vBoxLayout->addWidget(databaseAndToListenWidget);

    QWidget* widget=new QWidget(this);
    widget->setLayout(vBoxLayout);

    return widget;
}
