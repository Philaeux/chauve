#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "replaywidget.h"
#include "settingsdialog.h"


class MainWindow : public QMainWindow
{
  // Main window with all the widgets, menus, actions...
  // Uses mainwindow.ui
  // - replay_widget_ widget containing the replay tools
  // - settings_dialog_ dialog to change the settings of the application

  Q_OBJECT

public:
  MainWindow();
  ReplayWidget* GetReplayWidget() { return replay_widget_; };

protected:
  void closeEvent(QCloseEvent *event);

private:
  // Setup UI
  void CreateActions();
  void CreateMenus();
  void CreateStatusBar();
  void CreateToolsBar();
  // Settings
  void ReadSettings();
  void WriteSettings();

  // Menus
  QMenu *file_menu_;
  QMenu *tools_menu_;
  // ToolsBars
  QToolBar *replay_toolbar_;
  // Actions
  QAction *settings_action_;
  QAction *exit_action_;
  QAction *replay_action_;
  QAction *scan_replay_folder_;
  QAction *save_game_action_;
  QAction *delete_action_;
  QAction *soft_delete_action_;

  // Widgets and Dialogs
  SettingsDialog *settings_dialog_;
  ReplayWidget *replay_widget_;

private slots:
  void Settings();
  void SettingsFolderSelect();
  void Replay();
  void Save();
};

#endif // MAINWINDOW_H
