/*
 * File : main.cpp
 *
 */


#include "MainWindow.h"
#include "DirectorySelector.h"
#include <QMainWindow>
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    }

    QIcon appIcon(":/icons/icon.png");
    app.setWindowIcon(appIcon);

    DirectorySelector directorySelector;

    if (directorySelector.exec()) {
        QString selectedDirectory = directorySelector.getSelectedDirectory();

        MainWindow mainWindow;
        mainWindow.setDirectoryPath(selectedDirectory);
        mainWindow.show();

        return app.exec();
    }

    return 0; // Exit on No directory selected
}

