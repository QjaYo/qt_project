#ifndef FILEDELETE_H
#define FILEDELETE_H

#include "qtextcursor.h"
#include <QDialog>
#include <QTextFormat>
#include <QTextCursor>

namespace Ui {
class FileDelete;
}

class FileDelete : public QDialog
{
    Q_OBJECT

public:
    explicit FileDelete(QWidget *parent = nullptr);
    ~FileDelete();
    void setFileContent(const QString &content);

private slots:
    void on_btn_find_clicked();

    void on_btn_update_clicked();

private:
    Ui::FileDelete *ui;

    QString currentContent;
    int count;
    QString target;
    QTextCursor cursor;
    QTextCursor cursor_next;
    QTextCharFormat defaultFormat;
    QTextCharFormat highlightFormat;
    QTextCharFormat superHighlightFormat;
};

#endif // FILEDELETE_H
