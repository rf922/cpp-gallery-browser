/*
 * File : main.cpp
 *
 */


#include "MainWindow.h"
#include "DirectorySelector.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DirectorySelector directorySelector;

    if(directorySelector.exec()){
    	QString selectedDirectory = directorySelector.getSelectedDirectory();

  	MainWindow mainWindow;
	mainWindow.setDirectoryPath(selectedDirectory);
      	mainWindow.show();

	return app.exec();
    }

    return 0; // Exit on No directory selected
}

