#include <QApplication>
#include <QDialog>

#include "sortdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SortDialog *dialog = new SortDialog;
    dialog->setColumnRange('C', 'F');
    dialog->show();

    return app.exec();
}
