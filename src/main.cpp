#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

#include "games_manager.h"
#include "database_manager.h"
#include "mainwindow.h"
#include "settingsmanager.h"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // Splashscreen loading of the application

  QSplashScreen *splash = new QSplashScreen;
  Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
  splash->setPixmap(QPixmap(":/images/application/splash.png"));
  splash->show();

  splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);
  MainWindow window;

  splash->showMessage(QObject::tr("Loading additional modules..."), topRight, Qt::white);
  SettingsManager::Instance();
  GamesManager::Instance();
  DatabaseManager::Instance();

  splash->showMessage(QObject::tr("Loading database..."), topRight, Qt::white);
  DatabaseManager::Instance().LoadDatabase();
  window.GetReplayWidget()->UpdateGameList();

  window.show();
  splash->finish(&window);
  delete splash;
  return app.exec();
}
