#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filefind.h"
#include "fileinsert.h"
#include "fileupdate.h"
#include "filedelete.h"

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
    if (QFile::exists(tempFilePath))
        QFile::remove(tempFilePath);
    delete ui;
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
            {
                QMessageBox::critical(this, "FileLoad", "File opened, but failed to create temp file.");
            }
        }
        else
        {
            QMessageBox::critical(this, "FileLoad", "File load failed.");
        }
    }
    else
    {
        QMessageBox::critical(this, "FileLoad", "File load failed.");
    }
}

void MainWindow::on_btn_FIlePrint_clicked()
{
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "FilePrint", "File is not loaded yet.");
        return;
    }

    //로딩창 열기
    QDialog* loadingDialog = new QDialog(this);
    loadingDialog->setWindowTitle("FilePrint");
    loadingDialog->resize(100, 70);
    loadingDialog->setWindowModality(Qt::ApplicationModal);
    loadingDialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* loadingLayout = new QVBoxLayout(loadingDialog); //layout->dialog연결
    loadingDialog->setLayout(loadingLayout); //dialog->layout 연결
    loadingLayout->addWidget(new QLabel("loading...", loadingDialog), 0, Qt::AlignCenter); //layout에 widget하나를 추가

    loadingDialog->show();
    QApplication::processEvents();

    //파일 읽기
    QTextStream in(&file);
    QString content = in.readAll();
    //QTextStream[readAll, readLine, read, <<, >> setCodec, setRealNumberPrecision]
    file.close();

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("PrintFile");
    dialog->resize(500,550);

    QTextEdit* contentbox = new QTextEdit(dialog);
    contentbox->setReadOnly(true);
    contentbox->setText(content);

    QHBoxLayout* layout = new QHBoxLayout(dialog);
    layout->addWidget(contentbox);
    dialog->setLayout(layout);

    //로딩창 닫기
    loadingDialog->close();
    dialog->exec();
}

void MainWindow::on_btn_FileFind_clicked()
{
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "FilePrint", "File is not loaded yet.");
        return;
    }

    QDialog* loadingDialog = new QDialog(this);
    loadingDialog->setWindowTitle("FilePrint");
    loadingDialog->resize(100, 70);
    loadingDialog->setWindowModality(Qt::ApplicationModal);
    loadingDialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* loadingLayout = new QVBoxLayout(loadingDialog); //layout->dialog연결
    loadingDialog->setLayout(loadingLayout); //dialog->layout 연결
    loadingLayout->addWidget(new QLabel("loading...", loadingDialog), 0, Qt::AlignCenter); //layout에 widget하나를 추가

    loadingDialog->show();
    QApplication::processEvents();

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileFind dialog(this);
    dialog.setFileContent(content);

    loadingDialog->close();
    dialog.exec();
}

void MainWindow::on_btn_FileInsert_clicked()
{
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "FileInsert", "Failed to open file.");
        return;
    }

    //로딩창 열기
    QDialog* loadingDialog = new QDialog(this);
    loadingDialog->setWindowTitle("FilePrint");
    loadingDialog->resize(100, 70);
    loadingDialog->setWindowModality(Qt::ApplicationModal);
    loadingDialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* loadingLayout = new QVBoxLayout(loadingDialog); //layout->dialog연결
    loadingDialog->setLayout(loadingLayout); //dialog->layout 연결
    loadingLayout->addWidget(new QLabel("loading...", loadingDialog), 0, Qt::AlignCenter); //layout에 widget하나를 추가

    loadingDialog->show();
    QApplication::processEvents();

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileInsert dialog(this);
    dialog.setFileContent(content);

    loadingDialog->close();
    dialog.exec();
}

void MainWindow::on_btn_FileUpdate_clicked()
{
    QFile file(tempFilePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "FileUpdate", "Failed to open file.");
        return;
    }

    //로딩창 열기
    QDialog* loadingDialog = new QDialog(this);
    loadingDialog->setWindowTitle("FilePrint");
    loadingDialog->resize(100, 70);
    loadingDialog->setWindowModality(Qt::ApplicationModal);
    loadingDialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* loadingLayout = new QVBoxLayout(loadingDialog); //layout->dialog연결
    loadingDialog->setLayout(loadingLayout); //dialog->layout 연결
    loadingLayout->addWidget(new QLabel("loading...", loadingDialog), 0, Qt::AlignCenter); //layout에 widget하나를 추가

    loadingDialog->show();
    QApplication::processEvents();

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileUpdate dialog(this);
    dialog.setFileContent(content);

    loadingDialog->close();
    dialog.exec();
}


void MainWindow::on_btn_FileDelele_clicked()
{
    QFile file(tempFilePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "FileUpdate", "Failed to open file.");
        return;
    }

    //로딩창 열기
    QDialog* loadingDialog = new QDialog(this);
    loadingDialog->setWindowTitle("FilePrint");
    loadingDialog->resize(100, 70);
    loadingDialog->setWindowModality(Qt::ApplicationModal);
    loadingDialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* loadingLayout = new QVBoxLayout(loadingDialog); //layout->dialog연결
    loadingDialog->setLayout(loadingLayout); //dialog->layout 연결
    loadingLayout->addWidget(new QLabel("loading...", loadingDialog), 0, Qt::AlignCenter); //layout에 widget하나를 추가

    loadingDialog->show();
    QApplication::processEvents();

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    FileDelete dialog(this);
    dialog.setFileContent(content);

    loadingDialog->close();
    dialog.exec();
}

void MainWindow::on_btn_FileSave_clicked()
{
    if (originalFilePath.isEmpty()) {
        QMessageBox::critical(this, "FileSave", "File is not loaded yet.");
        return;
    }

    if (!QFile::exists(tempFilePath)) {
        QMessageBox::critical(this, "FileSave", "Temp file missing.");
        return;
    }

    if (QFile::exists(originalFilePath)) {
        QFile::remove(originalFilePath);
    }

    if (QFile::copy(tempFilePath, originalFilePath)) {
        save = true;
        QMessageBox::information(this, "Save", "File saved successfully.");
    } else {
        QMessageBox::critical(this, "Save", "Failed to save file.");
    }
}

void MainWindow::on_btn_Exit_clicked()
{
    if (save == false)
    {
        int answer = QMessageBox::warning(this, "Exit", "File is not saved. Quit anyway?", QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::No)
            return;
    }
    this->close();
}
