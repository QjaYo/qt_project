#include "mainwindow.h"

#include <QApplication>

QString defaultPath = "../../";
QString originalFilePath = "";
QString tempFilePath = "";
QString marker = "★";
bool save = true;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
