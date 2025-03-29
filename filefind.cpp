#include "filefind.h"
#include "ui_filefind.h"
#include <QString>
#include <QMessageBox>

FileFind::FileFind(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileFind)
{
    ui->setupUi(this);
    this->setWindowTitle("FileFind");
}

FileFind::~FileFind()
{
    delete ui;
}

void FileFind::setFileContent(const QString &content)
{
    FileFind::ui->fileContent->setPlainText(content);
}

void FileFind::on_btn_find_clicked()
{
    QString target = ui->lineEdit_find->text();

    if (target.isEmpty())
    {
        QMessageBox::information(this, "FileFind", "No match found.");
        return;
    }

    QTextCharFormat defaultFormat;
    defaultFormat.setBackground(Qt::white);

    QTextCursor cursor(ui->fileContent->document());
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(defaultFormat);

    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(Qt::yellow);

    int count = 0;
    cursor = QTextCursor(ui->fileContent->document());

    while (true)
    {
        cursor = ui->fileContent->document()->find(target, cursor, QTextDocument::FindCaseSensitively);
        if (cursor.isNull())
            break;

        cursor.mergeCharFormat(highlightFormat);
        count++;
    }

    if (count > 0)
    {
        QMessageBox::information(this, "FileFind", QString("\"%1\" %2 found.").arg(target).arg(count));
    }
    else
    {
        QMessageBox::information(this, "FileFind", "No match found");
    }
}

