/*
 * File : MainWindow.cpp
 */


#include "MainWindow.h"
#include "DirectorySelector.h"
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMouseEvent>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentIndex(0) {
    // Create UI components
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(800, 600); 
    imageLabel->setAttribute(Qt::WA_Hover);


    nextButton = new QPushButton("Next", this);
    prevButton = new QPushButton("Previous", this);

    nextButton->setVisible(false);
    prevButton->setVisible(false);

    // Button layout - Horizontal
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);

    // Layout setup
    layout = new QVBoxLayout();
    layout->addWidget(imageLabel);
    layout->addLayout(buttonLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    menuBar = new QMenuBar(this);
    fileMenu = menuBar->addMenu("File");
    viewMenu = menuBar->addMenu("View");

    toggleButtonsAction = new QAction("Show Navigation Buttons", this);
    toggleButtonsAction->setCheckable(true);
    toggleButtonsAction->setChecked(false);
    viewMenu->addAction(toggleButtonsAction);

    toggleFullScreenAction = new QAction("Full Screen", this);
    toggleFullScreenAction->setCheckable(true);
    toggleFullScreenAction->setChecked(false);
    viewMenu->addAction(toggleFullScreenAction);


    openDirAction = new QAction("Open Directory", this);
    fileMenu->addAction(openDirAction);

    
    connect(toggleButtonsAction, &QAction::toggled, this, &MainWindow::toggleNavigationButtons);
    connect(openDirAction, &QAction::triggered, this, &MainWindow::openDirectorySelector);
    setMenuBar(menuBar);
    connect(toggleFullScreenAction, &QAction::triggered, this, &MainWindow::toggleFullScreen);


    // Load images and display the first one
    loadImages();
    displayImage();

    this->setFocusPolicy(Qt::StrongFocus);

    // Connect buttons to slots
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::showNextImage);
    connect(prevButton, &QPushButton::clicked, this, &MainWindow::showPreviousImage);
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::toggleFullScreen(){
    if(isFullScreen()){
        showNormal();
	menuBar->show();
	nextButton->show();
	prevButton->show();
	toggleFullScreenAction->setChecked(false);
    } else {
        showFullScreen();
	menuBar->hide();
	nextButton->hide();
	prevButton->hide();
	toggleFullScreenAction->setChecked(true);
    }
}

void MainWindow::toggleNavigationButtons(bool visible){
    nextButton->setVisible(visible);
    prevButton->setVisible(visible);
}

void MainWindow::setDirectoryPath(const QString &path){
    if(parentDirectory.isEmpty()){
        parentDirectory = path;
    }
    directoryPath=path;
    loadImages();
    displayImage();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_N) {
        showNextImage();
    } else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_P) {
        showPreviousImage();
    }
}

void MainWindow::loadImages() {
    if(directoryPath.isEmpty()){
        qDebug() << "Directory path is empty";
	return;
    }
    qDebug() << "Directory Path: " << directoryPath;
    
    QDir dir(directoryPath);
    QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    imageFiles = dir.entryList(filters, QDir::Files);

    if (imageFiles.isEmpty()) {
        QMessageBox::warning(this, "No Images", "No images found in the directory: " + directoryPath);
        imageFiles.clear();
    } else {
        currentIndex=0;
    }
}


void MainWindow::displayImage() {
    if (imageFiles.isEmpty()) return;

    QString filePath = directoryPath + "/" + imageFiles.at(currentIndex);
    QPixmap pixmap(filePath);

    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "Unable to load image: " + filePath);
        return;
    }

    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    displayImage();
}

void MainWindow::showNextImage() {
    if (imageFiles.isEmpty()) return;

    if(currentIndex == imageFiles.size() -1){
        QMessageBox::StandardButton reply = QMessageBox::question(
	    this, "End Of Directory", "Move to next Subdirectory?",QMessageBox::Yes | QMessageBox::No);
	if(reply == QMessageBox::Yes){
	    QString nextSubdirectory = getNextSubdirectory();
	    if(!nextSubdirectory.isEmpty()){
	        setDirectoryPath(nextSubdirectory);
		return;
	    } else {
	        QMessageBox::information(this, "No More Subdirectories", "There are no more subdirectories.");
		QMessageBox::StandardButton restartReply = QMessageBox::question(this, "Restart from top directory ?","Start browsing from top directory ?",  QMessageBox::Yes | QMessageBox::No);
		if(restartReply == QMessageBox::Yes){
		    setDirectoryPath(parentDirectory);
		}
                return;
	    }
	
	}

    }


    currentIndex = (currentIndex + 1) % imageFiles.size();
    displayImage();
}


void MainWindow::showPreviousImage() {
    if (imageFiles.isEmpty()) return;

    currentIndex = (currentIndex - 1 + imageFiles.size()) % imageFiles.size();
    displayImage();
}

void MainWindow::openDirectorySelector(){
    DirectorySelector directorySelector(this);

    if(directorySelector.exec() == QDialog::Accepted){
        QString selectedDirectory = directorySelector.getSelectedDirectory();
	setDirectoryPath(selectedDirectory);
    }

}

QString MainWindow::getNextSubdirectory() {
    QDir dir(directoryPath);
    dir.cdUp(); 

    QStringList subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    int currentDirIndex = subdirs.indexOf(QFileInfo(directoryPath).fileName());

    if (currentDirIndex != -1 && currentDirIndex + 1 < subdirs.size()) {
        return dir.filePath(subdirs.at(currentDirIndex + 1));
    }

    return "";
}

