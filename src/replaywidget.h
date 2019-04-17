#ifndef REPLAYWIDGET_H
#define REPLAYWIDGET_H

#include <QWidget>

#include "ui_replaywidget.h"
#include "game.h"

class ReplayWidget : public QWidget, public Ui::ReplayWidget
{
  // Widget managing the replay tools

  Q_OBJECT

public:
  ReplayWidget(QWidget *parent = nullptr);

public slots:
  void ScanReplayFolder();
  void UpdateGameList();
  void SelectedCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
  void CellDataChanged(int row, int column);
  void UpdateRowAt(int row);

private:
  QTableWidgetItem* FactoryTableItem(const QString& text, QColor text_color, bool editable = false);
  void ClearGameInfoSection();
  void PopulateGameInfoSection(std::shared_ptr<Game> game);
};

#endif // REPLAYWIDGET_H
