/*
 * File : mainWindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDir>
#include <QKeyEvent>
#include <QPixmap>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void showNextImage();
    void showPreviousImage();

private:
    void loadImages();
    void displayImage();

    QLabel *imageLabel;
    QPushButton *nextButton;
    QPushButton *prevButton;
    QVBoxLayout *layout;

    QStringList imageFiles;
    int currentIndex;
    const QString directoryPath = "/path/to/your/images"; // Change this to your directory
};

#endif // MAINWINDOW_H

