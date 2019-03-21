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

protected:
    void closeEvent(QCloseEvent *event);

private:
    // Setup UI
    void CreateActions();
    void CreateMenus();
    void CreateStatusBar();
    // Settings
    void ReadSettings();
    void WriteSettings();

    // Menus
    QMenu *file_menu_;
    QMenu *tools_menu_;
    // Actions
    QAction *settings_action_;
    QAction *exit_action_;
    QAction *replay_action_;

    // Widgets and Dialogs
    SettingsDialog *settings_dialog_;
    ReplayWidget *replay_widget_;

private slots:
    // Settings slots
    void Settings();
    void SettingsFolderSelect();
};

#endif // MAINWINDOW_H
