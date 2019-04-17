#include "mainwindow.h"

#include <iostream>
#include <QtGui>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QToolbar>

#include "database_manager.h"
#include "settingsmanager.h"
#include "settingsdialog.h"

MainWindow::MainWindow()
{
  replay_widget_ = new ReplayWidget{ };
  setCentralWidget(replay_widget_);

  CreateActions();
  CreateMenus();
  CreateToolsBar();
  CreateStatusBar();

  settings_dialog_ = nullptr;

  ReadSettings();
  setWindowIcon(QIcon(":/images/application/icon.png"));
  setWindowTitle(tr("Chauve v0.0.4 - Dota Coaching Tools"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  WriteSettings();
  event->accept();
}

// Setup UI
void MainWindow::CreateActions()
{
  settings_action_ = new QAction(tr("Settin&gs"), this);
  settings_action_->setToolTip(tr("Setup application settings"));
  connect(settings_action_, SIGNAL(triggered()), this, SLOT(Settings()));

  exit_action_ = new QAction(tr("E&xit"), this);
  exit_action_->setShortcut(tr("Ctrl+Q"));
  exit_action_->setToolTip(tr("Exit the application"));
  connect(exit_action_, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

  replay_action_ = new QAction(tr("&Replays"), this);
  replay_action_->setShortcut(tr("Shift+1"));
  replay_action_->setToolTip(tr("Replay managing tools"));
  connect(replay_action_, SIGNAL(triggered()), this, SLOT(Replay()));

  const QIcon save_replay_folder_icon = QIcon(":/images/application/refresh.png");
  scan_replay_folder_ = new QAction(save_replay_folder_icon, tr("Scan Replay Folder"), this);
  scan_replay_folder_->setShortcut(tr("F5"));
  scan_replay_folder_->setToolTip(tr("F5 - Scan replay folder for new dem files"));
  connect(scan_replay_folder_, SIGNAL(triggered()), replay_widget_, SLOT(ScanReplayFolder()));

  const QIcon save_game_icon = QIcon(":/images/application/save.png");
  save_game_action_ = new QAction(save_game_icon, tr("Save"), this);
  save_game_action_->setShortcut(tr("F1"));
  save_game_action_->setToolTip(tr("F1 - Save the games into the database"));
  connect(save_game_action_, SIGNAL(triggered()), this, SLOT(Save()));
}

void MainWindow::CreateMenus()
{
  file_menu_ = menuBar()->addMenu(tr("&File"));
  file_menu_->addAction(settings_action_);
  file_menu_->addSeparator();
  file_menu_->addAction(exit_action_);

  tools_menu_ = menuBar()->addMenu(tr("&Tools"));
  tools_menu_->addAction(replay_action_);
}

void MainWindow::CreateStatusBar()
{
}

void MainWindow::CreateToolsBar()
{
  replay_toolbar_ = addToolBar(tr("Replays"));
  replay_toolbar_->addAction(save_game_action_);
  replay_toolbar_->addAction(scan_replay_folder_);
}

// Settings
void MainWindow::ReadSettings()
{
  QSettings settings("The Cluster", "Chauve");

  QRect rect = settings.value("geometry", QRect(200, 200, 400, 400)).toRect();
  move(rect.topLeft());
  resize(rect.size());
  SettingsManager::Instance().SetSteamReplayPath(
    settings.value("steam_replay_path", QString("")).toString());
}

void MainWindow::WriteSettings()
{
  QSettings settings("The Cluster", "Chauve");

  settings.setValue("geometry", geometry());
  settings.setValue("steam_replay_path", SettingsManager::Instance().GetSteamReplayPath());
}

// Slots
void MainWindow::Settings() {
  if (settings_dialog_ == nullptr) {
    settings_dialog_ = new SettingsDialog(this);
    connect(settings_dialog_->selectFolderButton, SIGNAL(clicked()),
      this, SLOT(SettingsFolderSelect()));
  }

  settings_dialog_->lineEdit->setText(SettingsManager::Instance().GetSteamReplayPath());
  if (settings_dialog_->exec()) {
    SettingsManager::Instance().SetSteamReplayPath(settings_dialog_->lineEdit->text());
  }
}

void MainWindow::SettingsFolderSelect() {
  QString dir = QFileDialog::getExistingDirectory(settings_dialog_, tr("Open Directory"), "",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  settings_dialog_->lineEdit->setText(dir);
}

void MainWindow::Replay() {

}

void MainWindow::Save() {
  DatabaseManager::Instance().SaveToDatabase();
}
