#ifndef USERGUI_H
#define USERGUI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <UserController.h>
#include <AdministratorController.h>
#include <QLineEdit>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class UserGUI : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserGUI(QWidget *parent = nullptr);

signals:

public slots:
    void populateDatabase();
    void populateToListen();

    void addBookButtonPressed();
    void deleteBookButtonPressed();


    void addBook(int);
    void deleteBook(int);

private:
    UserController* m_controller;

    QLineEdit* m_genreForFilter;

    QTableWidget* m_repoTableWidget;
    QTableWidget* m_toListenTableWidget;

    void createRepoTableWidget();
    void createToListenTableWidget();
    QWidget* createFilterByGenreWidget();
    QWidget* createDatabaseToListenWidget();
    QWidget* createCentralWidget();
};

#endif // USERGUI_H
