#pragma once
#include "mainwindow.h"
#include "QPushButton"
#include "admingui.h"
#include "usergui.h"
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    this->setWindowTitle("Home");
    this->setFixedSize(QSize(300,150));

    QWidget *centralWidget = createMainCentralWidget();
    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{}

void MainWindow::admin()
{
    auto admin = new AdminGUI;
    admin->show();
    this->close();
}

void MainWindow::user()
{
    auto user = new UserGUI;
    user->show();
    this->close();
}

QWidget *MainWindow::createMainCentralWidget()
{

    QPushButton *adminButton = new QPushButton("&ADMINISTRATOR", this);
    QPushButton *userButton = new QPushButton("&USER", this);

    connect(adminButton, &QPushButton:: clicked, this, &MainWindow:: admin );
    connect(userButton, &QPushButton:: pressed, this, &MainWindow:: user );


    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(adminButton);
    vBoxLayout->addWidget(userButton);

    QWidget* widget=new QWidget(this);
    widget->setLayout(vBoxLayout);

    return widget;
}


