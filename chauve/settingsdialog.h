#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "ui_settingsdialog.h"

class SettingsDialog: public QDialog, public Ui::SettingsDialog
{
    // Dialog window to change application settings.
    // Uses settingsdialog.ui

    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);

};

#endif // SETTINGSDIALOG_H
