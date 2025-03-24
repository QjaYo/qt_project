#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

extern QString defaultPath;
extern QString originalFilePath;
extern QString tempFilePath;
extern bool save;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_FileLoad_clicked();

    void on_btn_FIlePrint_clicked();

    void on_btn_FileFind_clicked();

    void on_btn_Exit_clicked();

    void on_btn_FileInsert_clicked();

    void on_btn_FileSave_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
