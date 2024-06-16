#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style/style.qss");
    file.open(QFile::ReadOnly);

    a.setStyleSheet(file.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
