#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QTableWidget>

class AdministratorController;

class AdminGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminGUI(QWidget *parent = nullptr);
    ~AdminGUI();

signals:
public slots:
    void searchPersistenceFile();
    void populateDatabaseFromFile();
    void populateDatabase();
    void addBook();
    void deleteBook();
    void updateBook();
    void cellClicked(int);
    void undo();
    void redo();

private:
    AdministratorController* m_controller;

    QLineEdit* m_persistenceFileName;
    QLineEdit* m_title;
    QLineEdit* m_author;
    QLineEdit* m_genre;
    QLineEdit* m_description;
    QLineEdit* m_publication_year;
    QLineEdit* m_cover;

    QTableWidget* m_repoTableWidget;
    void createTableWidget();
    QWidget* createCentralWidget();
    QWidget* createPersistenceWidget();
    QWidget* createDataAboutBookWidget();
    QWidget* createButtonsWidget();
};

#endif // ADMINGUI_H
