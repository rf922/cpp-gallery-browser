/*
 * File : DirectorySelector.h
 *
 */


#ifndef DIRECTORYSELECTOR_H
#define DIRECTORYSELECTOR_H




#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <algorithm>

class DirectorySelector : public QDialog {
    Q_OBJECT

public:
    explicit DirectorySelector(QWidget *parent = nullptr);
    QString getSelectedDirectory() const;
    QStringList getSubdirectories() const;

    void updateSubdirectories(const QString &parentDir) {
        populateSubdirectories(parentDir);
    }

private slots:
    void browseForDirectory();
    void populateSubdirectories(const QString &parentDir);
    void confirmSelection();

private:
    int extractNumber(const QString& name);
    bool customSort(const QString& a, const QString& b);
    //void populateSubdirectories(const QString &parentDir);

    QLineEdit *parentDirectoryEdit;
    QListWidget *subdirectoryList;
    QPushButton *browseButton;
    QPushButton *confirmButton;
    QPushButton *cancelButton;

    QStringList subdirectories;
    QString selectedDirectory;
};

#endif // DIRECTORYSELECTOR_H
