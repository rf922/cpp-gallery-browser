/*
 * File : DirectorySelector.cpp
 *
 */

#include <QDebug>
#include "DirectorySelector.h"

DirectorySelector::DirectorySelector(QWidget *parent) : QDialog(parent), selectedDirectory("") {
    setWindowTitle("Select Directory");

    parentDirectoryEdit = new QLineEdit(this);
    browseButton = new QPushButton("Browse...", this);
    subdirectoryList = new QListWidget(this);
    confirmButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(parentDirectoryEdit);
    topLayout->addWidget(browseButton);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(subdirectoryList);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(browseButton, &QPushButton::clicked, this, &DirectorySelector::browseForDirectory);
    connect(confirmButton, &QPushButton::clicked, this, &DirectorySelector::confirmSelection);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
//    connect(parentDirectoryEdit, &QLineEdit::textChanged, this, &DirectorySelector::populateSubdirectories);
}

QString DirectorySelector::getSelectedDirectory() const {    
    return selectedDirectory;
}

QStringList DirectorySelector::getSubdirectories() const {
    return subdirectories; 
}

void DirectorySelector::browseForDirectory() {
    qDebug() << "[ DirectorySelector::broseForDirectory ] : Browsing for Directory ...";
    QString directory = QFileDialog::getExistingDirectory(this, "Select Parent Directory");
    if (!directory.isEmpty()) {
        parentDirectoryEdit->setText(directory);
        qDebug() << "[ DirectorySelector::broseForDirectory ] : Selected :" << directory;
	    populateSubdirectories(directory);
        qDebug() << "[ DirectorySelector::broseForDirectory ] : Subdirectories Populated :" << subdirectories;
    }
}

void DirectorySelector::populateSubdirectories(const QString &parentDir) {
    //QString parentDir = parentDirectoryEdit->text();
    qDebug() << "[ DirectorySelector::populateSubdirectories ] : Populating subdirectories ...";
    qDebug() << "[ DirectorySelector::populateSubdirectories ] : Parent Directory : " << parentDir;
    QDir dir(parentDir);

    if (!dir.exists() || parentDir == selectedDirectory) return;

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    subdirectoryList->clear();

    subdirectories = dir.entryList();
    qDebug() << "[ DirectorySelector::populateSubdirectories ] : Subdirectories found: " << subdirectories;

    std::sort(subdirectories.begin(), subdirectories.end(), [](const QString &a, const QString &b) {
        return a.localeAwareCompare(b) < 0;
    });


    for (const QString &subdir : subdirectories) {
        subdirectoryList->addItem(subdir);
    }
    qDebug() << "[ DirectorySelector::populateSubdirectories ] : Subdirectories after sort: " << subdirectories;

}

void DirectorySelector::confirmSelection() {
    QListWidgetItem *selectedItem = subdirectoryList->currentItem();
    if (selectedItem) {
        selectedDirectory = QDir(parentDirectoryEdit->text()).filePath(selectedItem->text());
        accept();
    }
}

