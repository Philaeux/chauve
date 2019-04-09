#ifndef REPLAYWIDGET_H
#define REPLAYWIDGET_H

#include <QWidget>

#include "ui_replaywidget.h"
#include "replay.h"

class ReplayWidget : public QWidget, public Ui::ReplayWidget
{
    // Widget managing the replay tools

    Q_OBJECT

public:
    ReplayWidget(QWidget *parent = nullptr);
    void ScanReplay(const QString &replay);

public slots:
    void ScanReplayFolder();
    void ChangeSelectedReplay(QListWidgetItem *selected_replay);

private:
	void HideReplayInfoSection();
	void ReplayWidget::DisplayReplayInfoSection(Replay *replay);
};

#endif // REPLAYWIDGET_H
