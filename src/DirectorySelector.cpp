/*
 * File : DirectorySelector.cpp
 *
 */

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
    connect(parentDirectoryEdit, &QLineEdit::textChanged, this, &DirectorySelector::populateSubdirectories);
}

QString DirectorySelector::getSelectedDirectory() const {
    return selectedDirectory;
}

void DirectorySelector::browseForDirectory() {
    QString directory = QFileDialog::getExistingDirectory(this, "Select Parent Directory");
    if (!directory.isEmpty()) {
        parentDirectoryEdit->setText(directory);
    }
}

void DirectorySelector::populateSubdirectories() {
    QString parentDir = parentDirectoryEdit->text();
    QDir dir(parentDir);

    if (!dir.exists()) return;

    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    subdirectoryList->clear();

    QStringList subdirs = dir.entryList();

    std::sort(subdirs.begin(), subdirs.end(), [](const QString &a, const QString &b) {
        return a.localeAwareCompare(b) < 0;
    });


    for (const QString &subdir : subdirs) {
        subdirectoryList->addItem(subdir);
    }
}

void DirectorySelector::confirmSelection() {
    QListWidgetItem *selectedItem = subdirectoryList->currentItem();
    if (selectedItem) {
        selectedDirectory = QDir(parentDirectoryEdit->text()).filePath(selectedItem->text());
        accept();
    }
}

