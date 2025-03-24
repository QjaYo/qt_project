#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filefind.h"
#include "fileinsert.h"

#include <QinputDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include <QTextEdit>
#include <QVBoxLayout>

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
    QString filePath = defaultPath + "temp.txt";
    QFile file(filePath);
}

void MainWindow::on_btn_FileLoad_clicked()
{
    QString filename = QInputDialog::getText(this, "Fileload", "Enter file name.");

    if (!filename.isEmpty())
    {
        originalFilePath = defaultPath + filename;
        QFile originalFile(originalFilePath);

        if (originalFile.exists())
        {
            tempFilePath = defaultPath + "temp.txt";
            if (QFile::exists(tempFilePath))
                QFile::remove(tempFilePath);

            if (QFile::copy(originalFilePath, tempFilePath))
            {
                QMessageBox::information(this, "FileLoad", "File opened successfully.");
                save = true;
            }
            else
                QMessageBox::warning(this, "FileLoad", "File opened, but failed to create temp file.");
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
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "FilePrint", "File is not loaded yet.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("PrintFile");
    dialog->resize(500,550);

    QTextEdit* edit = new QTextEdit(dialog);
    edit->setReadOnly(true);
    //QMessageBox::information(this, "FilePrint", "file loading... Please wait");
    edit->setText(content);


    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(edit);
    dialog->setLayout(layout);
    dialog->exec();
}

void MainWindow::on_btn_FileFind_clicked()
{
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "FilePrint", "File is not loaded yet.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileFind dialog(this);
    dialog.setFileContent(content);
    dialog.exec();
}


void MainWindow::on_btn_Exit_clicked()
{
    if (save == false)
    {
        int answer = QMessageBox::question(this, "Exit", "File is not saved. Quit anyway?", QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::No)
            return;
    }

    if (QFile::exists(tempFilePath))
    {
        if (QFile::remove(tempFilePath))
            qDebug() << "temp file successfully deleted.";
        else
            QMessageBox::warning(this, "Exit", "Failed to delete temp file.");
    }
    close();
}


void MainWindow::on_btn_FileInsert_clicked()
{
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "FileInsert", "Failed to open file.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileInsert dialog(this);
    dialog.setFileContent(content);
    dialog.exec();
}
void MainWindow::on_btn_FileSave_clicked()
{
    if (originalFilePath.isEmpty()) {
        QMessageBox::warning(this, "FileSave", "File is not loaded yet.");
        return;
    }

    if (!QFile::exists(tempFilePath)) {
        QMessageBox::warning(this, "FileSave", "Temp file missing.");
        return;
    }

    if (QFile::exists(originalFilePath)) {
        QFile::remove(originalFilePath);
    }

    if (QFile::copy(tempFilePath, originalFilePath)) {
        save = true;
        QMessageBox::information(this, "Save", "File saved successfully.");
    } else {
        QMessageBox::warning(this, "Save", "Failed to save file.");
    }
}

