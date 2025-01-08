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


class DirectorySelector : public QDialog {
    Q_OBJECT

public:
    explicit DirectorySelector(QWidget *parent = nullptr);
    QString getSelectedDirectory() const;
    QStringList getSubdirectories() const;
    void populateSubdirectories(const QString &parentDir);

private slots:
    void browseForDirectory();
//    void populateSubdirectories();
    void confirmSelection();

private:
    QLineEdit *parentDirectoryEdit;
    QListWidget *subdirectoryList;
    QPushButton *browseButton;
    QPushButton *confirmButton;
    QPushButton *cancelButton;

    QStringList subdirectories;
    QString selectedDirectory;
};

#endif // DIRECTORYSELECTOR_H
