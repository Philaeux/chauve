#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

#include "mainwindow.h"
#include "settingsmanager.h"
#include "replaymanager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Splashscreen loading of the application

    QSplashScreen *splash = new QSplashScreen;
    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->setPixmap(QPixmap(":/images/application/splash.png"));
    splash->show();


    splash->showMessage(QObject::tr("Setting up the main window..."),
                        topRight, Qt::white);
    MainWindow window;

    splash->showMessage(QObject::tr("Loading additional modules..."),
                        topRight, Qt::white);
    SettingsManager::Instance();
    ReplayManager::Instance();

    splash->showMessage(QObject::tr("Loading database..."),
                        topRight, Qt::white);
    //TODO import database information into the window/modules

    window.show();
    splash->finish(&window);
    delete splash;
    return app.exec();
}
