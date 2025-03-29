#ifndef FILEINSERT_H
#define FILEINSERT_H

#include <QDialog>

extern QString defaultPath;
extern QString originalFilePath;
extern QString tempFilePath;
extern bool save;

namespace Ui {
class FileInsert;
}

class FileInsert : public QDialog
{
    Q_OBJECT

public:
    explicit FileInsert(QWidget *parent = nullptr);
    ~FileInsert();
    void setFileContent(const QString &content);
    void updateMarkerPreview();

private:
    Ui::FileInsert *ui;
    QString currentContent;

private slots:
    void on_edit_line_textChanged(const QString &);
    void on_edit_column_textChanged(const QString &);
    void on_btn_insert_clicked();
};

#endif // FILEINSERT_H
