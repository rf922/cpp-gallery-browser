/*
 * File : MainWindow.cpp
 */


#include "mainwindow.h"
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentIndex(0) {
    // Create UI components
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);

    nextButton = new QPushButton("Next", this);
    prevButton = new QPushButton("Previous", this);

    // Layout setup
    layout = new QVBoxLayout();
    layout->addWidget(imageLabel);
    layout->addWidget(nextButton);
    layout->addWidget(prevButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Load images and display the first one
    loadImages();
    displayImage();

    // Connect buttons to slots
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::showNextImage);
    connect(prevButton, &QPushButton::clicked, this, &MainWindow::showPreviousImage);
}

MainWindow::~MainWindow() {}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_N) {
        showNextImage();
    } else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_P) {
        showPreviousImage();
    }
}

void MainWindow::loadImages() {
    QDir dir(directoryPath);
    QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    imageFiles = dir.entryList(filters, QDir::Files);

    if (imageFiles.isEmpty()) {
        QMessageBox::warning(this, "No Images", "No images found in the directory.");
        close();
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
