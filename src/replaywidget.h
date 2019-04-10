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
	void UpdateGameList();
	void ReplayCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	void UpdateRowAt(int row);

private:
	QTableWidgetItem* FactoryTableItem(const QString& text);
	void ClearReplayInfoSection();
	void PopulateReplayInfoSection(Replay *replay);
};

#endif // REPLAYWIDGET_H
