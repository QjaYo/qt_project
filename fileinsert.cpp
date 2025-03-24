#include "fileinsert.h"
#include "ui_fileinsert.h"

#include <QMessageBox>
#include <QFile>

extern QString marker;

FileInsert::FileInsert(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FileInsert)
{
    ui->setupUi(this);
}

FileInsert::~FileInsert()
{
    delete ui;
}

void FileInsert::setFileContent(const QString &content)
{
    currentContent = content;
    ui->fileContent->setPlainText(content);
}

void FileInsert::updateMarkerPreview()
{
    if (!ui || !ui->fileContent)
        return;

    QString lineStr = ui->edit_line->text();
    QString colStr = ui->label_column->text();
    if (lineStr.isEmpty() || colStr.isEmpty()) {
        ui->fileContent->setPlainText(currentContent);
        return;
    }

    int line = ui->edit_line->text().toInt();
    int col = ui->edit_column->text().toInt();

    QStringList lines = currentContent.split('\n');

    if (line < 1 || line > lines.size())
    {
        ui->fileContent->setPlainText(currentContent);
        return;
    }

    QString targetLine = lines[line - 1];
    if (col < 0 || col > targetLine.length())
    {
        ui->fileContent->setPlainText(currentContent);
        return;
    }

    QStringList previewLines = lines;
    previewLines[line - 1].insert(col, marker);

    ui->fileContent->setPlainText(previewLines.join('\n'));

    QTextCursor cursor(ui->fileContent->document());
    cursor.movePosition(QTextCursor::Start);

    QTextCharFormat fmt;
    fmt.setForeground(Qt::red);
    fmt.setBackground(Qt::yellow);
    fmt.setFontWeight(QFont::Bold);

    while(true)
    {
        cursor = ui->fileContent->document()->find(marker, cursor);
        if (!cursor.isNull())
        {
            cursor.mergeCharFormat(fmt);
            break;
        }
        else
            break;
    }
}

void FileInsert::on_edit_line_textChanged(const QString &)
{
    updateMarkerPreview();
}

void FileInsert::on_edit_column_textChanged(const QString &)
{
    updateMarkerPreview();
}

void FileInsert::on_btn_insert_clicked()
{
    int line = ui->edit_line->text().toInt();
    int col = ui->edit_column->text().toInt();

    QString input = ui->edit_insert->text();

    QStringList lines = currentContent.split('\n');
    if (line < 1 || line > lines.size())
    {
        QMessageBox::warning(this, "Insert", "Invalid line number.");
        return;
    }

    QString targetLine = lines[line - 1];
    if (col < 0 || col > targetLine.length())
    {
        QMessageBox::warning(this, "Insert", "Invalid column number.");
        return;
    }

    int confirm = QMessageBox::question(this, "Insert", QString("Insert \"%1\" at line %2, column %3?").arg(input).arg(line).arg(col));

    if (confirm != QMessageBox::Yes)
        return;

    lines[line - 1].insert(col, input);
    currentContent = lines.join('\n');

    QFile file(tempFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << currentContent;
        file.close();
        QMessageBox::information(this, "Insert", "Word inserted successfully.");
        save = false;
    }
    else
    {
        QMessageBox::warning(this, "Insert", "Failed to write to temp.txt.");
    }

    ui->fileContent->setPlainText(currentContent);
}

