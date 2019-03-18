#include <QtGui>
#include <QAction>

#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"


MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
}

void MainWindow::closeEvent(QCloseEvent *event) {

}


void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::createToolBars()
{

}

void MainWindow::createStatusBar()
{

}

void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}
