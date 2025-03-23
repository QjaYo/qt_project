#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QinputDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>

struct textfile
{
    QDialog* text;
    bool save = false;
};

QString defaultpath = "../../";
QString filepath = "";
textfile loadedfile;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void initprogram()
{
    QString filepath = defaultpath + "temp.txt";
    QFile file(filepath); //저장용 temp.txt임시파일 생성 보장
}

void MainWindow::on_btn_FileLoad_clicked()
{
    QString filename = QInputDialog::getText(this, "Fileload", "Enter file name.");

    if (!filename.isEmpty())
    {
        filepath = defaultpath + filename;
        QFile file(filepath);
        if (file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, "FileLoad", "File opened successfully.");
            file.close();
        }
        else
        {
            QMessageBox::warning(this, "FileLoad", "File load failed.");
        }
    }
    else
    {
        QMessageBox::warning(this, "FileLoad", "File load failed.");
    }
}

void MainWindow::on_btn_FIlePrint_clicked()
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "FilePrint", "Failed to open file.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("PrintFile");
    dialog->resize(400,400);

    QTextEdit* edit = new QTextEdit(dialog);
    edit->setReadOnly(true);
    edit->setText(content);

    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(edit);
    dialog->setLayout(layout);
    dialog->exec();
}

