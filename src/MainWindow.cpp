/*
 * File : MainWindow.cpp
 */


#include "MainWindow.h"
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentIndex(0) {
    // Create UI components
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(800, 600); 

    nextButton = new QPushButton("Next", this);
    prevButton = new QPushButton("Previous", this);

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

    QFile file(":/styles/styles.qss");  
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);

    // Load images and display the first one
    loadImages();
    displayImage();

    // Connect buttons to slots
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::showNextImage);
    connect(prevButton, &QPushButton::clicked, this, &MainWindow::showPreviousImage);
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setDirectoryPath(const QString &path){
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

void MainWindow::showNextImage() {
    if (imageFiles.isEmpty()) return;

    currentIndex = (currentIndex + 1) % imageFiles.size();
    displayImage();
}

void MainWindow::showPreviousImage() {
    if (imageFiles.isEmpty()) return;

    currentIndex = (currentIndex - 1 + imageFiles.size()) % imageFiles.size();
    displayImage();
}
