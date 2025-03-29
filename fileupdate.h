#ifndef FILEUPDATE_H
#define FILEUPDATE_H

#include <QTextFormat>
#include <QDialog>
#include <QTextCursor>

namespace Ui {
class FileUpdate;
}

class FileUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit FileUpdate(QWidget *parent = nullptr);
    void setFileContent(const QString &content);
    ~FileUpdate();

private slots:
    void on_btn_find_clicked();

    void on_btn_update_clicked();

private:
    Ui::FileUpdate *ui;

    QString currentContent;
    int count;
    QString target;
    QTextCursor cursor;
    QTextCursor cursor_next;
    QTextCharFormat defaultFormat;
    QTextCharFormat highlightFormat;
    QTextCharFormat superHighlightFormat;
};

#endif // FILEUPDATE_H
