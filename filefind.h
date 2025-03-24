#ifndef FILEFIND_H
#define FILEFIND_H

#include <QDialog>

extern QString defaultPath;
extern QString originalFilePath;
extern QString tempFilePath;

namespace Ui {
class FileFind;
}

class FileFind : public QDialog
{
    Q_OBJECT

public:
    explicit FileFind(QWidget *parent = nullptr);
    ~FileFind();
    void setFileContent(const QString &content);

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileFind *ui;
};

#endif // FILEFIND_H
