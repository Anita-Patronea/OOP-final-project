#pragma once
#include "AdministratorUI.h"
#include "UserUI.h"
#include "Tests.h"
#include "MainMenuUI.h"
#include "mainwindow.h"
#include "admingui.h"
#include "usergui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    runAllTests();
    //runMainMenu();

    MainWindow w;
    w.show();

    return a.exec();
}
