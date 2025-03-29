#include "filedelete.h"
#include "ui_filedelete.h"

#include <QMessageBox>

FileDelete::FileDelete(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileDelete)
{
    ui->setupUi(this);

    defaultFormat.setBackground(Qt::white);
    highlightFormat.setBackground(Qt::yellow);
    superHighlightFormat.setBackground(Qt::red);
}

FileDelete::~FileDelete()
{
    delete ui;
}

void FileDelete::setFileContent(const QString &content)
{
    currentContent = content;
    ui->fileContent->setPlainText(content);
}

void FileDelete::on_btn_find_clicked()
{
    target = ui->lineEdit_find->text();

    if (target.isEmpty())
    {
        QMessageBox::information(this, "FileDelete", "Nothing entered.");
        return;
    }

    cursor = QTextCursor(ui->fileContent->document());
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(defaultFormat);

    count = 0;
    cursor = QTextCursor(ui->fileContent->document());

    while (true)
    {
        cursor = ui->fileContent->document()->find(target, cursor, QTextDocument::FindCaseSensitively);
        if (cursor.isNull())
            break;

        cursor.mergeCharFormat(highlightFormat);

        count++;
    }

    cursor = QTextCursor(ui->fileContent->document());
    cursor = ui->fileContent->document()->find(target, cursor, QTextDocument::FindCaseSensitively);
    cursor.mergeCharFormat(superHighlightFormat);

    if (count > 0)
    {
        QMessageBox::information(this, "FileDelete", QString("\"%1\" %2 found.").arg(target).arg(count));
    }
    else
    {
        QMessageBox::information(this, "FileDelete", "No match found");
    }
}


void FileDelete::on_btn_update_clicked()
{
    cursor = QTextCursor(ui->fileContent->document());
    cursor_next = ui->fileContent->document()->find(target, cursor, QTextDocument::FindCaseSensitively);

    cursor = cursor_next;
    if (cursor.isNull())
        return;

    //update
    cursor.mergeCharFormat(defaultFormat);

    cursor_next = ui->fileContent->document()->find(target, cursor, QTextDocument::FindCaseSensitively);
    cursor_next.mergeCharFormat(superHighlightFormat);
}

